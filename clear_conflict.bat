// svn�� commit �ϱ� ����,
// ���ʿ��� ���ϵ�(������ �ʿ䰡 ���� ���ϵ�)�� ������ ���ƾ� ���� �Ȼ���..
// �׷� ���ϵ��� �����ϴ� ��ġ ����.
// �ҽ� �������� ���ø�Ʈ�� �ߴ� �� ���⼭ �ذ��� �� �����ϴ�.

// ���� ���� �� ������ �ʹ� ���� ������.. ���� ����� �ٷ� �����ֽñ� �ٶ�.
// ��ɾ�	�ɼ�	���

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
