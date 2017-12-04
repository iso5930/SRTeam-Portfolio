#include "stdafx.h"
#include "MainMenuScene.h"

#include "Export_Function.h"
#include "Layer.h"
#include "PlaneObject.h"
#include "SceneSelector.h"
#include "GameEvent.h"
#include "Event_Concrete_Functors.h"

CMainMenuScene::CMainMenuScene(void)
{

}

CMainMenuScene::~CMainMenuScene(void)
{
	Release();
}

CMainMenuScene* CMainMenuScene::Create(CScene* _pScene /*= NULL*/)
{
	CMainMenuScene* pInstance = new CMainMenuScene;
	HRESULT hr = pInstance->Initialize(_pScene);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CMainMenuScene::Update(void)
{
	// 메뉴 생기기 전까지 임시로,
	if (ENGINE::GetInputManager()->IsEventProgressKeyDownNow())
	{
		ENGINE::GetEventManager()->SwitchOn(L"GetEventProgressKey");
	}

	ENGINE::CScene::Update();

	return 0;
}

void CMainMenuScene::Render(void)
{
	ENGINE::CScene::Render();
}

HRESULT CMainMenuScene::LoadDynamicResources(void)
{
	HRESULT hr = NULL;

	// test code
	hr = ENGINE::GetResourceManager()->AddSprite(
		RESOURCE_TYPE_DYNAMIC,
		L"MainMenu_back",
		L"../bin/Resources/Texture/LogoBack/LogoBack.png",
		1);
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CMainMenuScene::CreateDynamicObjects(void)
{
	HRESULT hr = NULL;

	hr = AddObject();
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CMainMenuScene::Initialize(CScene* _pScene /*= NULL*/)
{
	HRESULT hr = NULL;

	// 2. 이 씬에서 사용하는 리소스들은 이 함수 안으로..
	hr = LoadDynamicResources();
	if FAILED(hr)
		return hr;

	// 3. 각 레이어에 오브젝트들 생성해서 넣어줌..
	hr = CreateDynamicObjects();
	if FAILED(hr)
		return hr;


	// Add Events
	ENGINE::CGameObject* pPlane = m_LayerMap[LAYER_ID_BACK]->GetGameObject(L"Logo_Back");
	ENGINE::CGameEvent* pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeinAtMainmenu(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeinAtMainmenu");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeoutAtMainmenu(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeoutAtMainmenu");
	pEvent->AddCondition(L"GetEventProgressKey");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_ShowMainmenu, false);
	pEvent->AddCondition(L"ShowMainmenu");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_SceneChangeAtMainmenuToStage1(SCENE_ID_STAGE_1), false);
	pEvent->AddCondition(L"SceneChangeAtMainmenuToStage1");
	AddEvent(pEvent);

	ENGINE::GetEventManager()->SwitchOn(L"FadeinAtMainmenu");


	//! 과연.. 효과있다?
	ENGINE::GetTimeManager()->SetTime();
	return S_OK;
}

HRESULT CMainMenuScene::AddObject(void)
{
	// 1. add obj to back layer
	ENGINE::CLayer* pLayer = ENGINE::CLayer::Create();
	if (pLayer == NULL)
		return E_FAIL;
	m_LayerMap.insert(LAYER_MAP::value_type(LAYER_ID_BACK, pLayer));

	ENGINE::CGameObject* pObject = NULL;

	pObject = CPlaneObject::Create(OBJECT_TYPE_DYNAMIC, L"MainMenu_back", true);
	if (pObject == NULL)
		return E_FAIL;
	static_cast<CPlaneObject*>(pObject)->SetPos(WINCX / 2.f, WINCY / 2.f);
	pLayer->AddObject(L"Logo_Back", pObject);


	// 2. add obj to back layer
	pLayer = ENGINE::CLayer::Create();
	if (pLayer == NULL)
		return E_FAIL;
	m_LayerMap.insert(LAYER_MAP::value_type(LAYER_ID_UI, pLayer));


	// 3. add obj to back layer
	pLayer = ENGINE::CLayer::Create();
	if (pLayer == NULL)
		return E_FAIL;
	m_LayerMap.insert(LAYER_MAP::value_type(LAYER_ID_CURSOR, pLayer));


	return S_OK;
}

void CMainMenuScene::Release(void)
{

}

void CMainMenuScene::ResetEvent(void)
{
	ENGINE::GetEventManager()->SwitchOn(L"FadeinAtMainmenu");
}
