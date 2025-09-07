from datetime import datetime, timezone
from typing import Any, Dict, List, Optional
import httpx
from fastapi import APIRouter, HTTPException
from pydantic import BaseModel
from ..settings import (
    NEON_API_BASE, NEON_API_KEY, NEON_ORG_ID, NEON_PROJECT_ID,
    NEON_LIMIT_CU_HOURS, NEON_LIMIT_STORAGE_GB
)

router = APIRouter(tags=["billing"])

class UsageOut(BaseModel):
    from_iso: str
    to_iso: str
    source: str
    cu_hours: float
    storage_gb: Optional[float] = None
    limits: Dict[str, float]
    percent: Dict[str, float]
    near_limit: Dict[str, bool]
    note: Optional[str] = None

def _iso_month_bounds() -> tuple[str, str]:
    now = datetime.now(timezone.utc)
    start = now.replace(day=1, hour=0, minute=0, second=0, microsecond=0)
    return start.isoformat(), now.isoformat()

async def _fetch(client: httpx.AsyncClient, url: str, params: dict) -> dict:
    r = await client.get(url, params=params, headers={"Authorization": f"Bearer {NEON_API_KEY}", "Accept": "application/json"})
    if r.status_code == 429:
        raise HTTPException(429, "Neon API rate limited")
    if r.status_code >= 400:
        return {"__error__": True, "status": r.status_code, "detail": r.text}
    return r.json()

def _sum_metric_periods(periods: List[dict], key: str) -> float:
    total = 0.0
    latest_storage = None
    for p in periods or []:
        for c in p.get("consumption", []):
            total += float(c.get(key, 0) or 0)
            if "synthetic_storage_size_bytes" in c:
                latest_storage = c["synthetic_storage_size_bytes"]
    return total, (None if latest_storage is None else float(latest_storage) / (1024**3))

@router.get("/billing/usage", response_model=UsageOut)
async def billing_usage() -> UsageOut:
    if not (NEON_API_KEY and NEON_ORG_ID):
        raise HTTPException(500, "NEON_API_KEY and NEON_ORG_ID must be set")

    start_iso, now_iso = _iso_month_bounds()
    params = {"from": start_iso, "to": now_iso, "granularity": "daily", "org_id": NEON_ORG_ID}

    async with httpx.AsyncClient(timeout=15) as client:
        acc = await _fetch(client, f"{NEON_API_BASE}/consumption_history/account", params)
        source = "account"
        note = None

        if "__error__" in acc:
            proj = await _fetch(client, f"{NEON_API_BASE}/consumption_history/projects", params)
            if "__error__" in proj:
                raise HTTPException(502, f"Neon consumption metrics unavailable: account={acc.get('status')} project={proj.get('status')}")
            source = "projects"
            total_compute = 0.0
            latest_storage_gb = None
            for proj_entry in proj.get("projects", []):
                compute, storage_gb = _sum_metric_periods(proj_entry.get("periods", []), "compute_time_seconds")
                total_compute += compute
                if storage_gb is not None:
                    latest_storage_gb = storage_gb if latest_storage_gb is None else max(latest_storage_gb, storage_gb)
        else:
            total_compute, latest_storage_gb = _sum_metric_periods(acc.get("periods", []), "compute_time_seconds")

    cu_hours = total_compute / 3600.0
    storage_gb = latest_storage_gb

    pct_cu = (cu_hours / NEON_LIMIT_CU_HOURS * 100.0) if NEON_LIMIT_CU_HOURS > 0 else 0.0
    pct_storage = (storage_gb / NEON_LIMIT_STORAGE_GB * 100.0) if (storage_gb is not None and NEON_LIMIT_STORAGE_GB > 0) else 0.0
    near_cu = pct_cu >= 80.0
    near_storage = pct_storage >= 80.0 if storage_gb is not None else False

    if source == "projects":
        note = "Using project-level aggregation; account-level metrics not available for this plan."

    return UsageOut(
        from_iso=start_iso,
        to_iso=now_iso,
        source=source,
        cu_hours=round(cu_hours, 3),
        storage_gb=(None if storage_gb is None else round(storage_gb, 3)),
        limits={"cu_hours": NEON_LIMIT_CU_HOURS, "storage_gb": NEON_LIMIT_STORAGE_GB},
        percent={"cu_hours": round(pct_cu, 1), "storage_gb": round(pct_storage, 1) if storage_gb is not None else 0.0},
        near_limit={"cu_hours": near_cu, "storage_gb": near_storage},
        note=note,
    )
