# Unreal MCP 연결

- 플러그인: https://github.com/DandyDay/UnrealMCP
- 고정 소스 커밋: `06f8bc48919ca6f2f8495230035a6db15d298709`
- 라이선스: `Plugins/N1UnrealMCP/LICENSE` (MIT)
- 검증 엔진: Unreal Engine 5.7.4 / Windows / Development Editor
- 연결: Codex stdio → Python bridge → `127.0.0.1:55558` → Unreal Editor
- Codex 등록 이름: `unreal-stealthexit`

원본 플러그인의 Python 의존성에 `mcp<2` 상한을 추가했다. 원본은
`mcp.server.fastmcp`를 사용하므로 MCP SDK 2.x와 호환되지 않는다.
설치된 SDK는 1.30.0이며 전체 환경 버전은 `requirements-lock.txt`에 기록했다.
게임 C++와 에셋은 이 설치에서 수정하지 않았다.

## 사용

이 프로젝트를 Unreal Editor에서 열고 Codex 확장/대화를 다시 시작한다.
MCP 도구는 에디터가 실행 중일 때 동작한다. 다른 프로젝트에서 같은
포트를 사용하는 MCP 플러그인을 동시에 실행하지 않는다.
현재 등록은 사용자 전역 `~/.codex/config.toml`에 있으며 이 프로젝트의
절대 경로를 참조한다. 프로젝트를 이동하면 등록 경로도 갱신해야 한다.

읽기 전용 연결 검증 (프로젝트 루트 PowerShell):

```powershell
& ./Saved/MCPSetup/venv/Scripts/python.exe Tools/UnrealMCP/check_connection.py
```

정상 결과: 서버 `N1UnrealMCP`, 도구 104개, `pong: N1UnrealMCP`.
이 검증은 에셋을 생성하거나 저장하지 않는다.

## Python 환경 복구

`Saved`는 Git에 포함되지 않는다. 삭제하거나 새로 체크아웃한 경우:

```powershell
& 'C:/Program Files/Epic Games/UE_5.7/Engine/Binaries/ThirdParty/Python3/Win64/python.exe' -m venv Saved/MCPSetup/venv
& ./Saved/MCPSetup/venv/Scripts/python.exe -m pip install -r Tools/UnrealMCP/requirements-lock.txt
```

`run_bridge.py`는 저장소의 플러그인 Python 소스를 직접 불러온다.
별도로 브리지 패키지를 설치할 필요는 없다.

## 연결 해제

`codex.cmd mcp remove unreal-stealthexit`로 Codex 등록을 해제하고,
에디터의 Plugins에서 N1 Unreal MCP를 비활성화한 후 재시작한다.
