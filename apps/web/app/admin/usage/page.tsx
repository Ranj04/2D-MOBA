"use client";
import { useEffect, useState } from "react";

type Usage = {
  from_iso: string; to_iso: string; source: string;
  cu_hours: number; storage_gb?: number | null;
  limits: { cu_hours: number; storage_gb: number };
  percent: { cu_hours: number; storage_gb: number };
  near_limit: { cu_hours: boolean; storage_gb: boolean };
  note?: string | null;
};

export default function UsagePage() {
  const [data, setData] = useState<Usage | null>(null);
  const [err, setErr] = useState<string>("");
  useEffect(() => {
    // Use NEXT_PUBLIC_API_BASE if set, else relative path
  const base = process.env.NEXT_PUBLIC_API_BASE ?? "";
    fetch(`${base}/billing/usage`).then(async r => {
      if (!r.ok) throw new Error(await r.text());
      return r.json();
    }).then(setData).catch(e => setErr(String(e)));
  }, []);
  if (err) return <pre style={{color:"crimson"}}>{err}</pre>;
  if (!data) return <p>Loading…</p>;
  const bar = (pct:number)=>(
    <div style={{border:"1px solid #ccc", width:300}}>
      <div style={{height:10, width:`${Math.min(pct,100)}%`, background: pct>=90?"#e11":"#0a7"}}/>
    </div>
  );
  return (
    <div style={{fontFamily:"ui-sans-serif", padding:24}}>
      <h1>Neon Usage</h1>
      <p><b>Window:</b> {new Date(data.from_iso).toLocaleString()} → {new Date(data.to_iso).toLocaleString()}</p>
      <p><b>Source:</b> {data.source} {data.note ? `— ${data.note}` : ""}</p>
      <h3>CU-hours: {data.cu_hours} / {data.limits.cu_hours} ({data.percent.cu_hours}%)</h3>
      {bar(data.percent.cu_hours)}
      {data.storage_gb != null && (
        <>
          <h3 style={{marginTop:16}}>Storage: {data.storage_gb} GB / {data.limits.storage_gb} GB ({data.percent.storage_gb}%)</h3>
          {bar(data.percent.storage_gb)}
        </>
      )}
    </div>
  );
}
