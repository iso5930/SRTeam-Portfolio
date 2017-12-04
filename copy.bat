//! copy.bat�� �Ϻ��� ��ü�ڴ� ����?
// ����� ��Ʃ����� ����� �����Ǿ�, �ڵ����� ������ �� �ִٸ�..
// ���� ���� : dll ���� - .h, .lib, .dll ���� - Ŭ�� ����
// ������ dll���� ���Ӽ��� �����(reference���� �ٸ� dll�� lib ������ �� �����) �� ��ŭ ���带 �� ����� ��..


// headers�� �ѹ� ���� ī���Ѵ�..
del /q .\Reference\Headers\*.*

// ��ɾ�	�ɼ�	ī���� ���									ī�ǹ��� ���
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
