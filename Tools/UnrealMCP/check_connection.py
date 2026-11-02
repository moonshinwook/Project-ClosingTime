"""Read-only MCP handshake, tool discovery, and Unreal Editor ping."""
import asyncio
import json
from pathlib import Path
import sys

from mcp import ClientSession, StdioServerParameters
from mcp.client.stdio import stdio_client


async def check():
    params = StdioServerParameters(
        command=sys.executable,
        args=[str(Path(__file__).with_name("run_bridge.py"))],
        env={"PYTHONUTF8": "1"},
    )
    async with stdio_client(params) as (reader, writer):
        async with ClientSession(reader, writer) as session:
            result = await session.initialize()
            tools = await session.list_tools()
            print(f"Server: {result.serverInfo.name}; tools: {len(tools.tools)}")
            ping = await session.call_tool("ping", {})
            if ping.isError:
                raise RuntimeError(ping)
            payloads = [json.loads(c.text) for c in ping.content if c.type == "text"]
            print(json.dumps(payloads, ensure_ascii=False))
            if not payloads or payloads[0].get("pong") != "N1UnrealMCP":
                raise RuntimeError("Unreal Editor ping failed")


if __name__ == "__main__":
    asyncio.run(check())
