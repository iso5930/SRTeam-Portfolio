#include "stdafx.h"
#include "MainApp.h"
#include "Export_Function.h"
#include "SceneSelector.h"

CMainApp::CMainApp(void)
{
	//AllocConsole(); 
	//freopen( "CONOUT$",  "wt", stdout);
	//SetConsoleTitleA("Debug");
}

CMainApp::~CMainApp(void)
{
	//FreeConsole();
	Release();
}

CMainApp* CMainApp::Create(void)
{
	CMainApp* pInstance = new CMainApp;
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CMainApp::Update(void)
{
	ENGINE::GetInputManager()->SetKeyState(g_hWnd, g_bKeyDisable);

	// alt + f4
	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_LALT) && ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_F4))
		PostQuitMessage(0);
	if (ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_F11))
	{
		ENGINE::GetInputManager()->SetDrawBoundingBox();
	}

	ENGINE::GetTimeManager()->SetTime();

	ENGINE::GetManagement()->Update();

	return 0;
}

void CMainApp::Render(void)
{
	ENGINE::GetManagement()->Render();
}

HRESULT CMainApp::Initialize(void)
{
	srand(unsigned(time(NULL)));

	HRESULT hr = NULL;
	
	hr = ENGINE::GetDeviceManager()->InitDevice(
		ENGINE::CGraphicDevice::WINDOWED_FALSE,
		g_hWnd,
		WINCX,
		WINCY);
	if FAILED(hr)
		return hr;

	hr = ENGINE::GetDeviceManager()->InitFont(L"¸¼Àº °íµñ", 0, 0, FW_NORMAL);
	if FAILED(hr)
		return hr;

	ENGINE::GetSoundManager()->LoadSoundFile();

	hr = ENGINE::GetManagement()->InitManagement();
	if FAILED(hr)
		return hr;

	hr = ENGINE::GetManagement()->ChangeScene(SCENE_ID_LOGO, CSceneSelector(SCENE_ID_LOGO));
	if FAILED(hr)
		return hr;

	ENGINE::GetTimeManager()->InitTime();

	return S_OK;
}

void CMainApp::Release(void)
{
	ENGINE::CInfoSubject::DestroyInstance();
	ENGINE::CInputManager::DestroyInstance();
	ENGINE::CManagement::DestroyInstance();
	ENGINE::CResourceManager::DestroyInstance();
	ENGINE::CGraphicDevice::DestroyInstance();
	ENGINE::CTimeManager::DestroyInstance();
	ENGINE::CEventManager::DestroyInstance();
}
