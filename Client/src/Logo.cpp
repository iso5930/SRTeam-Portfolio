#include "stdafx.h"
#include "Logo.h"

#include "Export_Function.h"
#include "Layer.h"
#include "PlaneObject.h"
#include "GameEvent.h"
#include "Event_Concrete_Functors.h"

CLogo::CLogo(void)
{

}

CLogo::~CLogo(void)
{
	Release();
}

CLogo* CLogo::Create(CScene* _pScene /*= NULL*/)
{
	CLogo* pInstance = new CLogo;
	HRESULT hr = pInstance->Initialize(_pScene);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

//! 타이머 사용한 이벤트.. 씬 새로 들어올 때 타이머 리셋 안하면 문제 생기겠지..
int CLogo::Update(void)
{
	// 1. 로고를 재생하다가..
	// 2. 키 입력을 받으면?
	// 3. 화면 전환한다.

	if(ENGINE::GetTimer(L"LogoSceneTimer")->GetLapCount() == 1/*5*/)
	{
		ENGINE::GetEventManager()->SwitchOn(L"LogoFadeout_00");
	}
	if(ENGINE::GetTimer(L"LogoSceneTimer")->GetLapCount() == 2/*8*/)
	{
		ENGINE::GetEventManager()->SwitchOn(L"LogoFadeout_01");
	}
	if(ENGINE::GetTimer(L"LogoSceneTimer")->GetLapCount() == 3/*11*/)
	{
		ENGINE::GetEventManager()->SwitchOn(L"LogoFadeout_02");
	}

	ENGINE::CScene::Update();

	return 0;
}

void CLogo::Render(void)
{
	ENGINE::CScene::Render();

}

HRESULT CLogo::LoadDynamicResources(void)
{
	HRESULT hr = NULL;

	hr = ENGINE::GetResourceManager()->AddSprite(
		RESOURCE_TYPE_DYNAMIC,
		L"01logo_gravity",
		L"../bin/Resources/Texture/LogoBack/gravity.bmp",
		1);
	if FAILED(hr)
		return hr;

	hr = ENGINE::GetResourceManager()->AddSprite(
		RESOURCE_TYPE_DYNAMIC,
		L"00logo_sonnori",
		L"../bin/Resources/Texture/LogoBack/sonnori.bmp",
		1);
	if FAILED(hr)
		return hr;

	hr = ENGINE::GetResourceManager()->AddSprite(
		RESOURCE_TYPE_DYNAMIC,
		L"02logo_wizard",
		L"../bin/Resources/Texture/LogoBack/wizard.bmp",
		1);
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CLogo::CreateDynamicObjects(void)
{
	HRESULT hr = NULL;

	hr = AddObject();
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CLogo::Initialize(CScene* _pScene /*= NULL*/)
{
	HRESULT hr = NULL;

	// 1. 게임 시작부터 로드되어야 하는 리소스들은 여기에!
	hr = ENGINE::GetResourceManager()->AddBuffers();
	if FAILED(hr)
		return hr;

	// 2. 이 씬에서 사용하는 리소스들은 이 함수 안으로..
	hr = LoadDynamicResources();
	if FAILED(hr)
		return hr;

	// 3. 각 레이어에 오브젝트들 생성해서 넣어줌..
	hr = CreateDynamicObjects();
	if FAILED(hr)
		return hr;


	// Add Events
	ENGINE::CGameEvent* pEvent = ENGINE::CGameEvent::Create(new CEvn_SceneChangeAtLogoToMainmenu(SCENE_ID_MAIN_MENU), false);
	pEvent->AddCondition(L"SceneChangeAtLogoToMainmenu");
	AddEvent(pEvent);

	ENGINE::CGameObject* pPlane = m_LayerMap[LAYER_ID_LOGO]->GetGameObject(L"02logo_wizard");
	pEvent = ENGINE::CGameEvent::Create(new CEvn_LogoFadeout(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"LogoFadeout_00");
	AddEvent(pEvent);

	pPlane = m_LayerMap[LAYER_ID_LOGO]->GetGameObject(L"01logo_gravity");
	pEvent = ENGINE::CGameEvent::Create(new CEvn_LogoFadeout_01(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"LogoFadeout_01");
	AddEvent(pEvent);

	pPlane = m_LayerMap[LAYER_ID_LOGO]->GetGameObject(L"00logo_sonnori");
	pEvent = ENGINE::CGameEvent::Create(new CEvn_LogoFadeout_02(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"LogoFadeout_02");
	AddEvent(pEvent);

	ENGINE::GetTimeManager()->CreateTimer(L"LogoSceneTimer", 1.f);


	ENGINE::GetSoundManager()->PlayBGM(L"BGMLogo.mp3");

	//! 과연.. 효과있다?
	ENGINE::GetTimeManager()->SetTime();
	return S_OK;
}

HRESULT CLogo::AddObject(void)
{
	ENGINE::CLayer* pLayer = ENGINE::CLayer::Create();
	if (pLayer == NULL)
		return E_FAIL;
	m_LayerMap.insert(LAYER_MAP::value_type(LAYER_ID_LOGO, pLayer));

	// add obj to layer
	CPlaneObject* pObject = CPlaneObject::Create(OBJECT_TYPE_DYNAMIC, L"02logo_wizard", true);
	if (pObject == NULL)
		return E_FAIL;
	pObject->SetPos(WINCX / 2.f, WINCY / 2.f);
	pLayer->AddObject(L"02logo_wizard", pObject);

	pObject = CPlaneObject::Create(OBJECT_TYPE_DYNAMIC, L"01logo_gravity", true);
	if (pObject == NULL)
		return E_FAIL;
	pObject->SetPos(WINCX / 2.f, WINCY / 2.f);
	pLayer->AddObject(L"01logo_gravity", pObject);

	pObject = CPlaneObject::Create(OBJECT_TYPE_DYNAMIC, L"00logo_sonnori", true);
	if (pObject == NULL)
		return E_FAIL;
	pObject->SetPos(WINCX / 2.f, WINCY / 2.f);
	pLayer->AddObject(L"00logo_sonnori", pObject);

	return S_OK;
}

void CLogo::Release(void)
{
	ENGINE::GetTimeManager()->ReleaseTimer(L"LogoSceneTimer");
}
