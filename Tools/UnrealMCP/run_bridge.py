"""Launch the vendored Unreal MCP bridge independently of the caller's cwd."""
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "Plugins" / "N1UnrealMCP" / "Bridge"))

from src.server import main

if __name__ == "__main__":
    main()
