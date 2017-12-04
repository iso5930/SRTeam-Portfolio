#include "stdafx.h"
#include "Stage5.h"

#include "Export_Function.h"
#include "SceneSelector.h"

#include "Terrain.h"
#include "Layer.h"
#include "StaticCamera.h"
#include "CharacterGroup.h"
#include "Character.h"
#include "etcGroup.h"
#include "Wall.h"

#include "Transform.h"
#include "GameEvent.h"
#include "Event_Concrete_Functors.h"
#include "Col_Event_Functors.h"
#include "EmptyObject.h"

#include "Skeleton.h"
#include "Akhenaton.h"

CStage5::CStage5(void)
{

}

CStage5::~CStage5(void)
{
	Release();
}

CStage5* CStage5::Create(CScene* _pScene /*= NULL*/)
{
	CStage5* pInstance = new CStage5;
	HRESULT hr = pInstance->Initialize(_pScene);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CStage5::Update(void)
{
	//! 실제로는 나갈 것인지 yes, no로 묻는 화면이 떠야겠지만..
	if (ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_ESCAPE))
	{
		HRESULT hr = ENGINE::GetManagement()->ChangeScene(SCENE_ID_MAIN_MENU, CSceneSelector(SCENE_ID_MAIN_MENU));
		if FAILED(hr)
			return 1;
		else /*if SUCCEEDED(hr)*/
			return 0;
	}

	ENGINE::CScene::Update();

	return 0;
}

void CStage5::Render(void)
{
	ENGINE::CScene::Render();
}

HRESULT CStage5::LoadDynamicResources(void)
{
	HRESULT hr = NULL;

	hr = ENGINE::GetResourceManager()->AddTexture(
		RESOURCE_TYPE_DYNAMIC,
		TEXTURE_TYPE_NORMAL,
		L"Tile",
		L"../bin/Resources/Texture/Tile/%d.bmp",
		109);
	if FAILED(hr)
		return hr;

	hr = ENGINE::GetResourceManager()->AddTexture(
		RESOURCE_TYPE_DYNAMIC,
		TEXTURE_TYPE_CUBE,
		L"Texture_Wall",
		L"../bin/Resources/Texture/etc/DDS/Wall%d.dds",
		5);
	if FAILED(hr)
		return hr;

	/*hr = ENGINE::GetResourceManager()->AddTexture(
		RESOURCE_TYPE_DYNAMIC,
		TEXTURE_TYPE_NORMAL,
		L"Texture_Monster",
		L"../bin/Resources/Texture/Monster%d.png",
		2);
	if FAILED(hr)
		return hr;

	hr = ENGINE::GetResourceManager()->AddTexture(
		RESOURCE_TYPE_DYNAMIC,
		TEXTURE_TYPE_CUBE,
		L"Texture_Cube",
		L"../bin/Resources/Texture/Cube%d.dds",
		1);
	if FAILED(hr)
		return hr;*/

	return S_OK;
}

HRESULT CStage5::CreateDynamicObjects(void)
{
	HRESULT hr = NULL;

	hr = AddEnvironmentLayerObject();
	if FAILED(hr)
		return hr;

	hr = AddIngameLayerObject();
	if FAILED(hr)
		return hr;

	hr = AddUIAndCursorLayerObject();
	if FAILED(hr)
		return hr;

	return S_OK;
}

void CStage5::ResetEvent()
{
	ENGINE::GetEventManager()->SwitchOn(L"FadeinAtStage5");

	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_SIZZ)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_MARIA)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_ELLUARD)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_TENZI)->GetMemento()->clear();
}

HRESULT CStage5::Initialize(CScene* _pScene /*= NULL*/)
{
	HRESULT hr = NULL;

	m_wstrBgmKey = L"BGMDungeon.mp3";

	// 1. static resource, object 생성 시도..
	// 만약 생성했다면 내부적으로 두번 생성을 막아주므로 무조건 써도 된다..
	hr = CStage::AddStatics(_pScene);
	if FAILED(hr)
		return hr;

	// 2. 이 씬에서 사용하는 리소스들은 이 함수 안으로..
	hr = LoadDynamicResources();
	if FAILED(hr)
		return hr;

	// 3. 각 레이어에 다이나믹 오브젝트들 생성해서 넣어줌..
	hr = CreateDynamicObjects();
	if FAILED(hr)
		return hr;


	// add events
	ENGINE::CGameObject* pPlane = NULL;
	pPlane = m_LayerMap[LAYER_ID_UI]->GetGameObject(L"AAfull_overlap");
	ENGINE::CGameEvent* pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeinAtStage5(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeinAtStage5");
	AddEvent(pEvent);

	// 씬 넘어가는 것들..
	pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeoutAtStage5ToStage4(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeoutAtStage5ToStage4");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_SceneChangeAtStage5ToStage4(SCENE_ID_STAGE_4), false);
	pEvent->AddCondition(L"SceneChangeAtStage5ToStage4");
	AddEvent(pEvent);

	ENGINE::GetEventManager()->SwitchOn(L"FadeinAtStage5");

	ENGINE::GetSoundManager()->PlayBGM(L"BGMDungeon.mp3");

	//! 과연.. 효과있다?
	ENGINE::GetTimeManager()->SetTime();
	return S_OK;
}

HRESULT CStage5::AddEnvironmentLayerObject(void)
{	
	ENGINE::CGameObject* pObject = NULL;

	pObject = CTerrain::Create(OBJECT_TYPE_DYNAMIC, L"../bin/Data/Stage5_40_40.dat", L"Terrain_Stage5");
	if (pObject == NULL)
		return E_FAIL;
	m_LayerMap[LAYER_ID_ENVIRONMENT]->AddObject(L"Terrain", pObject);

	ENGINE::Cetc*	petc = NULL;

	for(int i = 0; i < 5; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(5.f, 0.f, 3.f + i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(4.f, 0.f, 8.f + i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(5.f, 0.f, 12.f + i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(6.f + j, 0.f, 16.f + i), 1, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 3; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(14.f, 0.f, 16.f + i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(15.f + j, 0.f, 17.f + i), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(18.f + i, 0.f, 16.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
	petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(19.f, 0.f, 15.f), 2, 90.f);
	((ENGINE::CetcGroup*)pObject)->Addetc(petc);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(20.f + i, 0.f, 15.f + j), 1, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 3; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(22.f, 0.f, 14.f - i), 0, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(23.f + i, 0.f, 15.f - j), 1, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 10; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(23.f + i, 0.f, 13.f - j), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 17; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(9.f + i, 0.f, 11.f - j), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 7; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(8.f + i, 0.f, 13.f - j), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(5.f, 0.f, 18.f + i), 0, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
	petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(6.f, 0.f, 22.f), 1, 90.f);
	((ENGINE::CetcGroup*)pObject)->Addetc(petc);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	for(int i = 0; i < 11; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(5.f, 0.f, 23.f + i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(6.f + i, 0.f, 34.f), 2, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(10.f + i, 0.f, 33.f), 0, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(11.f, 0.f, 34.f + i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 6; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(12.f + i, 0.f, 38.f), 2, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(18.f + i, 0.f, 37.f - j), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 7; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(20.f + i, 0.f, 37.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 11; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(27.f + i, 0.f, 38.f), 2, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 11; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(38.f, 0.f, 37.f - i), 2, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 14; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(37.f - i, 0.f, 26.f - j), 1, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(24.f + i, 0.f, 27.f + j), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(22.f + i, 0.f, 31.f + j), 1, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 6; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(16.f + i, 0.f, 31.f + j), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(10.f + i, 0.f, 29.f + j), 1, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 6; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(8.f + i, 0.f, 24.f + j), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(10.f + i, 0.f, 21.f + j), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(9.f, 0.f, 22.f + i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(10.f + i, 0.f, 20.f), 2, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(14.f + i, 0.f, 21.f + j), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(18.f + i, 0.f, 24.f - j), 1, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 5; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(22.f - i, 0.f, 22.f), 0, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(19.f - i, 0.f, 21.f), 0, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 11; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(38.f, 0.f, 37.f - i), 0, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 5; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(37, 0.f, 24.f - i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 13; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(24.f + i, 0.f, 18.f + j), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 6; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(24.f + i, 0.f, 20.f), 2, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 7; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(37.f, 0.f, 21.f - i), 0, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(33.f - i, 0.f, 15.f - j), 1, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(28.f + i, 0.f, 6.f + j), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 20; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(8.f + i, 0.f, 6.f + j), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(8.f + i, 0.f, 5.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 3; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(18.f + i, 0.f, 5.f), 2, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 6; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(37.f, 0.f, 5.f - i), 0, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
	petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(36.f, 0.f, 0.f), 1, 90.f);
	((ENGINE::CetcGroup*)pObject)->Addetc(petc);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	for(int i = 0; i < 3; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(35.f, 0.f, 1.f + i), 0, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
	petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(34.f, 0.f, 3.f), 2, 90.f);
	((ENGINE::CetcGroup*)pObject)->Addetc(petc);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	for(int i = 0; i < 6; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(33.f - i, 0.f, 3.f), 0, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 5; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(27.f - i, 0.f, 3.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 17; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(22.f - i, 0.f, 2.f), 2, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 6; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(37.f, 0.f, 9.f + i), 0, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 3; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(36.f - i, 0.f, 10.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}

	return S_OK;
}

HRESULT CStage5::AddIngameLayerObject(void)
{
	ENGINE::CGameObject* pObject = NULL;

	pObject = ENGINE::CMonsterGroup::Create(OBJECT_TYPE_DYNAMIC);
	ENGINE::CMonster* pMonster = CAkhenaton::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(31.f, 0.f, 32.f)); if(pMonster == NULL)	return E_FAIL;
	pMonster->SetOwner(static_cast<ENGINE::CMonsterGroup*>(pObject));
	((ENGINE::CMonsterGroup*)pObject)->AddMonster(pMonster);

	pMonster = CSkeleton::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(30.f, 0.f, 31.f)); if(pMonster == NULL)	return E_FAIL;
	pMonster->SetOwner(static_cast<ENGINE::CMonsterGroup*>(pObject));
	((ENGINE::CMonsterGroup*)pObject)->AddMonster(pMonster);

	pMonster = CSkeleton::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(29.f, 0.f, 30.f)); if(pMonster == NULL)	return E_FAIL;
	pMonster->SetOwner(static_cast<ENGINE::CMonsterGroup*>(pObject));
	((ENGINE::CMonsterGroup*)pObject)->AddMonster(pMonster);

	pMonster = CSkeleton::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(28.f, 0.f, 29.f)); if(pMonster == NULL)	return E_FAIL;
	pMonster->SetOwner(static_cast<ENGINE::CMonsterGroup*>(pObject));
	((ENGINE::CMonsterGroup*)pObject)->AddMonster(pMonster);

	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"MonsterGroup1", pObject);

	// for event
	CEmptyObject* pEmptyObj = CEmptyObject::Create(OBJECT_TYPE_DYNAMIC, new CColSwitchOn(L"FadeoutAtStage5ToStage4"), 0.4f, 1.f, 0.4f);
	pEmptyObj->SetPos(35.5f, 0.5f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"ToStage4", pEmptyObj);

	return S_OK;
}

HRESULT CStage5::AddUIAndCursorLayerObject(void)
{
	ENGINE::CGameObject* pObject = NULL;

	pObject = CStaticCamera::Create(OBJECT_TYPE_DYNAMIC,
		static_cast<CTerrain*>(m_LayerMap[LAYER_ID_ENVIRONMENT]->GetGameObject(L"Terrain"))->GetTerrainInfo());
	if (pObject == NULL)
		return E_FAIL;
	m_LayerMap[LAYER_ID_UI]->AddObject(L"Camera", pObject);
	// scene이 init하는 중이라, 일일이, 캐릭터 그룹 찾아서 달아줘야 하는 불상사..
	ENGINE::CGameObject* pObj = m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup");
	pObj = static_cast<ENGINE::CCharacterGroup*>(pObj)->GetLeaderCharacter();
	pObj->PrepareFind();
	ENGINE::CComponent* pComponent = pObj->GetComponent(L"Transform");
	static_cast<CStaticCamera*>(pObject)->SetTargetInfo(static_cast<ENGINE::CTransform*>(pComponent));

	return S_OK;
}

void CStage5::Release(void)
{
	ENGINE::CInfoSubject::DestroyInstance(); //! subject의 구조상 문제 때문에, 그냥 넘기면 뻑이 남.. 걍 지웠다 다시 만들자..
}
