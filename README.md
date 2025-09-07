
# Aether Arena Monorepo

Production-ready full-stack monorepo for a 5v5 MOBA with lobbies, matchmaking, bots, and real-time play.

## Features
- Next.js 14 frontend (Vercel-ready)
- FastAPI backend (Render/Heroku/DO-ready)
- Postgres (Neon), Redis (Upstash)
- JWT auth, profanity-checked usernames, secure cookies
- Lobby system, quickplay queue, bots auto-fill
- 17 archetypes, 3 weapons + 1 ultimate each (data-driven)

## Quickstart

1. Copy `.env.example` to `.env` and fill in secrets.
2. `docker-compose -f docker-compose.dev.yml up` (starts Postgres, Redis, API)
3. In another terminal: `pnpm i --filter ./apps/web && pnpm --filter ./apps/web dev`
4. Open http://localhost:3000

## Deploy
- Deploy API to Render (see `render.yaml`)
- Deploy web to Vercel (set `NEXT_PUBLIC_API_BASE`)
- Use Neon for Postgres, Upstash for Redis

See below for full instructions and environment variables.

## Neon usage meter
API endpoint: GET /billing/usage
- Requires env: NEON_API_KEY, NEON_ORG_ID (and optionally NEON_PROJECT_ID)
- Soft limits (defaults): NEON_LIMIT_CU_HOURS=50, NEON_LIMIT_STORAGE_GB=0.5
- For Free plans, account-level metrics may be unavailable. The API falls back to project-level aggregation.
Web viewer (optional): /admin/usage in Next.js (uses NEXT_PUBLIC_API_BASE)

