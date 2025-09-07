from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
try:
    from .routers import usage  # type: ignore
except Exception:
    usage = None

app = FastAPI(title="Aether API", version="0.1.0")
app.add_middleware(CORSMiddleware, allow_origins=["*"], allow_credentials=True, allow_methods=["*"], allow_headers=["*"])

if usage:
    app.include_router(usage.router)

@app.get("/")
def root(): return {"ok": True}
