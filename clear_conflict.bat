// svn에 commit 하기 전에,
// 불필요한 파일들(공유할 필요가 없는 파일들)을 정리해 놓아야 문제 안생김..
// 그런 파일들을 정리하는 배치 파일.
// 소스 레벨에서 컨플릭트가 뜨는 건 여기서 해결할 수 없습니다.

// 버그 있을 수 있으니 너무 믿진 마세요.. 문제 생기면 바로 말해주시길 바람.
// 명령어	옵션	경로

rmdir		/q /s	.\Client\home\Debug
rmdir		/q /s	.\Client\home\Release

rmdir		/q /s	.\Engine\System\home\Debug
rmdir		/q /s	.\Engine\System\home\Release
rmdir		/q /s	.\Engine\Utility\home\Debug
rmdir		/q /s	.\Engine\Utility\home\Release
rmdir		/q /s	.\Engine\Resources\home\Debug
rmdir		/q /s	.\Engine\Resources\home\Release

rmdir		/q /s	.\Tools\Tool_Terrain_Object\home\Debug
rmdir		/q /s	.\Tools\Tool_Terrain_Object\home\Release

rmdir		/q /s	.\Tools\Tool_Object\home\Debug
rmdir		/q /s	.\Tools\Tool_Object\home\Release


del /s *.user
del SRTeam1.ncb
del SRTeam1.suo


for /l %%i in (0, 1, 99) do for /r %%d in (*.r%%i) do del /s "%%d"
