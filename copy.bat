//! copy.bat의 완벽한 대체자는 없나?
// 비쥬얼 스튜디오의 빌드와 연동되어, 자동으로 실행할 수 있다면..
// 빌드 순서 : dll 빌드 - .h, .lib, .dll 복사 - 클라 빌드
// 문제는 dll끼리 종속성이 생기면(reference에서 다른 dll의 lib 참조할 일 생기면) 그 만큼 빌드를 더 해줘야 함..


// headers를 한번 비우고 카피한다..
del /q .\Reference\Headers\*.*

// 명령어	옵션	카피할 경로									카피받을 경로
xcopy		/y		.\Engine\engine_include\*.h					.\Reference\Headers\
xcopy		/y		.\Engine\engine_include\*.hpp				.\Reference\Headers\
xcopy		/y		.\Engine\Export\*.*							.\Reference\Headers\

xcopy		/y		.\Engine\System\src\*.h						.\Reference\Headers\
xcopy		/y		.\Engine\System\bin\System.lib				.\Reference\Libraries\
xcopy		/y		.\Engine\System\bin\System.dll				.\Client\bin\
xcopy		/y		.\Engine\System\bin\System.dll				.\Tools\Tool_Terrain_Object\bin\
xcopy		/y		.\Engine\System\bin\System.dll				.\Tools\Tool_Object\bin\

xcopy		/y		.\Engine\Utility\src\*.h					.\Reference\Headers\
xcopy		/y		.\Engine\Utility\bin\Utility.lib			.\Reference\Libraries\
xcopy		/y		.\Engine\Utility\bin\Utility.dll			.\Client\bin\
xcopy		/y		.\Engine\Utility\bin\Utility.dll			.\Tools\Tool_Terrain_Object\bin\
xcopy		/y		.\Engine\Utility\bin\Utility.dll			.\Tools\Tool_Object\bin\

xcopy		/y		.\Engine\Resources\src\*.h					.\Reference\Headers\
xcopy		/y		.\Engine\Resources\bin\Resources.lib		.\Reference\Libraries\
xcopy		/y		.\Engine\Resources\bin\Resources.dll		.\Client\bin\
xcopy		/y		.\Engine\Resources\bin\Resources.dll		.\Tools\Tool_Terrain_Object\bin\
xcopy		/y		.\Engine\Resources\bin\Resources.dll		.\Tools\Tool_Object\bin\
