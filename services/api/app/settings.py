import os
NEON_API_BASE = os.getenv("NEON_API_BASE", "https://console.neon.tech/api/v2")
NEON_API_KEY = os.getenv("NEON_API_KEY", "")
NEON_ORG_ID = os.getenv("NEON_ORG_ID", "")
NEON_PROJECT_ID = os.getenv("NEON_PROJECT_ID", "")  # optional
# Soft limits (defaults reflect typical Free-tier expectations)
NEON_LIMIT_CU_HOURS = float(os.getenv("NEON_LIMIT_CU_HOURS", "50"))
NEON_LIMIT_STORAGE_GB = float(os.getenv("NEON_LIMIT_STORAGE_GB", "0.5"))
