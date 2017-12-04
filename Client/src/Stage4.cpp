#include "stdafx.h"
#include "Stage4.h"

#include "Export_Function.h"
#include "SceneSelector.h"

#include "Terrain.h"
#include "Layer.h"
#include "StaticCamera.h"
#include "CharacterGroup.h"
#include "Character.h"
#include "etcGroup.h"
#include "Wall.h"
#include "Treasurechest4-1.h"
#include "Treasurechest4-2.h"

#include "Transform.h"
#include "GameEvent.h"
#include "Col_Event_Functors.h"
#include "Event_Concrete_Functors.h"
#include "EmptyObject.h"
#include "SealObject.h"
#include "SwitchObject.h"

CStage4::CStage4(void)
{

}

CStage4::~CStage4(void)
{
	Release();
}

CStage4* CStage4::Create(CScene* _pScene /*= NULL*/)
{
	CStage4* pInstance = new CStage4;
	HRESULT hr = pInstance->Initialize(_pScene);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CStage4::Update(void)
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

void CStage4::Render(void)
{
	ENGINE::CScene::Render();
}

HRESULT CStage4::LoadDynamicResources(void)
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


	hr = ENGINE::GetResourceManager()->AddTexture(RESOURCE_TYPE_DYNAMIC, TEXTURE_TYPE_NORMAL, L"Seal", L"../bin/Resources/Texture/floor4/seal.png", 1); if FAILED(hr) return hr;
	hr = ENGINE::GetResourceManager()->AddTexture(RESOURCE_TYPE_DYNAMIC, TEXTURE_TYPE_NORMAL, L"Switch", L"../bin/Resources/Texture/floor4/switch.png", 1); if FAILED(hr) return hr;

	return S_OK;
}

HRESULT CStage4::CreateDynamicObjects(void)
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

void CStage4::ResetEvent()
{
	ENGINE::GetEventManager()->SwitchOn(L"FadeinAtStage4");

	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_SIZZ)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_MARIA)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_ELLUARD)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_TENZI)->GetMemento()->clear();
}

HRESULT CStage4::Initialize(CScene* _pScene /*= NULL*/)
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
	// fadein
	ENGINE::CGameObject* pPlane = NULL;
	pPlane = m_LayerMap[LAYER_ID_UI]->GetGameObject(L"AAfull_overlap");
	ENGINE::CGameEvent* pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeinAtStage4(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeinAtStage4");
	AddEvent(pEvent);

	// 씬 넘어가는 것들..
	// to stage 3..
	pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeoutAtStage4ToStage3(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeoutAtStage4ToStage3");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_SceneChangeAtStage4ToStage3(SCENE_ID_STAGE_3), false);
	pEvent->AddCondition(L"SceneChangeAtStage4ToStage3");
	AddEvent(pEvent);

	// to stage 5..
	pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeoutAtStage4ToStage5(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeoutAtStage4ToStage5");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_SceneChangeAtStage4ToStage5(SCENE_ID_STAGE_5), false);
	pEvent->AddCondition(L"SceneChangeAtStage4ToStage5");
	AddEvent(pEvent);


	//scene4로 긁어가야 할..
	CTalkbox* pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"talk_91"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Talk_91(pTalk));
	pEvent->AddCondition(L"stage4_talk_91");
	AddEvent(pEvent);

	ENGINE::CCharacter* pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_SIZZ);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Move_91(pChar, D3DXVECTOR3(3.f, 0.f, 26.f)));
	pEvent->AddCondition(L"stage4_move_91");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"talk_92"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Talk_92(pTalk));
	pEvent->AddCondition(L"stage4_talk_92");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"talk_93"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Talk_93(pTalk));
	pEvent->AddCondition(L"stage4_talk_93");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"talk_94"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Talk_94(pTalk));
	pEvent->AddCondition(L"stage4_talk_94");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_Unseal());
	pEvent->AddCondition(L"Stage4Switch1on");
	pEvent->AddCondition(L"Stage4Switch2on");
	pEvent->AddCondition(L"Stage4Switch3on");
	AddEvent(pEvent);

	ENGINE::GetEventManager()->CreateSwitch(L"Stage4Unseal");

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage4_talk_11"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage4_Talk_11(pTalk));
	pEvent->AddCondition(L"stage4_talk_11");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage4_talk_12"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage4_Talk_12(pTalk));
	pEvent->AddCondition(L"stage4_talk_12");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage4_talk_21"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage4_Talk_21(pTalk));
	pEvent->AddCondition(L"stage4_talk_21");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage4_talk_22"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage4_Talk_22(pTalk));
	pEvent->AddCondition(L"stage4_talk_22");
	AddEvent(pEvent);

	ENGINE::GetEventManager()->CreateSwitch(L"stage4_box_b_open");
	ENGINE::GetEventManager()->CreateSwitch(L"stage4_box_a_open");


	ENGINE::GetEventManager()->SwitchOn(L"FadeinAtStage4");

	ENGINE::GetSoundManager()->PlayBGM(L"BGMDungeon.mp3");

	//! 과연.. 효과있다?
	ENGINE::GetTimeManager()->SetTime();
	return S_OK;
}

HRESULT CStage4::AddEnvironmentLayerObject(void)
{	
	ENGINE::CGameObject* pObject = NULL;

	pObject = CTerrain::Create(OBJECT_TYPE_DYNAMIC, L"../bin/Data/Stage4_32_32.dat", L"Terrain_Stage4");
	if (pObject == NULL)
		return E_FAIL;
	m_LayerMap[LAYER_ID_ENVIRONMENT]->AddObject(L"Terrain", pObject);

	ENGINE::Cetc*	petc = NULL;
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(4.f + float(i), 0.f, 0.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(7.f, 0.f, 1.f + float(i)), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 13; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(8.f + float(i), 0.f, 2.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 8; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(20.f, 0.f, 3.f + float(i)), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 7; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(19.f - float(j), 0.f, 10.f - float(i)), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(14.f - float(i), 0.f, 7.f - float(j)), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 6; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(12.f - float(i), 0.f, 6.f - float(j)), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 6; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(21.f + float(i), 0.f, 3.f + float(j)), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(23.f + float(i), 0.f, 7.f + float(j)), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 5; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(23.f + float(i), 0.f, 2.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(28.f, 0.f, 3.f + float(i)), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 5; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(27.f, 0.f, 7.f + float(i)), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
	petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(28.f, 0.f, 12), 1, 90.f);
	((ENGINE::CetcGroup*)pObject)->Addetc(petc);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(29.f + i, 0.f, 13), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 12; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(31.f, 0.f, 14.f + i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(26.f + float(i), 0.f, 18.f + float(j)), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 11; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(23.f + float(i), 0.f, 22.f - float(j)), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
	petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(26.f, 0.f, 13.f), 0, 90.f);
	((ENGINE::CetcGroup*)pObject)->Addetc(petc);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(23.f + i, 0.f, 11.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 5; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(30.f - i, 0.f, 26.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(25.f - float(i), 0.f, 26.f - float(j)), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(24.f, 0.f, 27.f + i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 6; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(23.f - i, 0.f, 31.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(17.f, 0.f, 30.f - i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 7; ++i)
	{
		for(int j = 0; j < 6; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(14.f + float(i), 0.f, 26.f - float(j)), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(13.f, 0.f, 22.f - i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(16.f - float(i), 0.f, 28.f - float(j)), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 7; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(11.f - i, 0.f, 29.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(5.f, 0.f, 30.f + i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(4.f - i, 0.f, 32.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 5; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(2.f, 0.f, 31.f - i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 7; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(3.f + float(i), 0.f, 26.f - float(j)), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 4; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(3.f, 0.f, 24.f - i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 3; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(2.f, 0.f, 20.f - i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 6; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(3.f + float(i), 0.f, 17.f - float(j)), 2, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 14; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(9.f + float(i), 0.f, 22.f - float(j)), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(6.f + float(i), 0.f, 21.f + float(j)), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(7.f + float(i), 0.f, 9.f + float(j)), 0, 90.f);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 3; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(2.f, 0.f, 14.f - i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(3.f + i, 0.f, 11.f), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 10; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CWall::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(4.f, 0.f, 10.f - i), 1, 90.f);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CTreasurechest4A::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(28.f, (float(i) / 3.33f) + 0.5f, 23.f), i);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}

	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CTreasurechest4B::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(17.f, (float(i) / 3.33f) + 0.5f, 5.f), i);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}



	return S_OK;
}

HRESULT CStage4::AddIngameLayerObject(void)
{
	ENGINE::CGameObject* pObject = NULL;


	// for event
	CEmptyObject* pEmptyObj = CEmptyObject::Create(OBJECT_TYPE_DYNAMIC, new CColSwitchOn(L"FadeoutAtStage4ToStage3"), 0.8f, 1.f, 0.4f);
	pEmptyObj->SetPos(5.f, 0.5f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"ToStage3", pEmptyObj);

	pEmptyObj = CEmptyObject::Create(OBJECT_TYPE_DYNAMIC, new CColSwitchOn(L"FadeoutAtStage4ToStage5"), 0.8f, 1.f, 0.4f);
	pEmptyObj->SetPos(3.f, 30.5f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"ToStage5", pEmptyObj);


	// 봉인
	CSealObject* pObj = CSealObject::Create(OBJECT_TYPE_DYNAMIC, L"Seal");
	pObj->SetPos(3.f, 28.f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"Seal", pObj);

	// 스위치
	CSwitchObject* pObjj = CSwitchObject::Create(OBJECT_TYPE_DYNAMIC, L"Switch", new CColSwitchOn(L"stage4_talk_92"));
	pObjj->SetPos(20.f, 28.f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"Switch1", pObjj);

	pObjj = CSwitchObject::Create(OBJECT_TYPE_DYNAMIC, L"Switch", new CColSwitchOn(L"stage4_talk_93"));
	pObjj->SetPos(27.5f, 15.f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"Switch2", pObjj);

	pObjj = CSwitchObject::Create(OBJECT_TYPE_DYNAMIC, L"Switch", new CColSwitchOn(L"stage4_talk_94"));
	pObjj->SetPos(5.f, 12.f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"Switch3", pObjj);

	return S_OK;
}

HRESULT CStage4::AddUIAndCursorLayerObject(void)
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


	// scene 4로,.,.
	ENGINE::SMART_TEXT text = ENGINE::SMART_TEXT(L"강력한 결계가 쳐져 있어 지나갈 수 없다.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"talk_91", pObject);

	text = ENGINE::SMART_TEXT(L"마법진에 가까이 다가가자 빛이 반짝하고 빛나다, 이윽고 사라진다.\n던젼 출구의 결계가 약해지는 것이 느껴진다.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"talk_92", pObject);

	text = ENGINE::SMART_TEXT(L"마법진에 가까이 다가가자 빛이 반짝하고 빛나다, 이윽고 사라진다.\n던젼 출구의 결계가 약해지는 것이 느껴진다.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"talk_93", pObject);

	text = ENGINE::SMART_TEXT(L"마법진에 가까이 다가가자 빛이 반짝하고 빛나다, 이윽고 사라진다.\n던젼 출구의 결계가 약해지는 것이 느껴진다.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"talk_94", pObject);

	// 보물상자..
	text = ENGINE::SMART_TEXT(L"건빵을 얻었다.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage4_talk_11", pObject);

	text = ENGINE::SMART_TEXT(L"비었다.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage4_talk_12", pObject);

	// 보물상자..
	text = ENGINE::SMART_TEXT(L"건빵을 얻었다.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage4_talk_21", pObject);

	text = ENGINE::SMART_TEXT(L"비었다.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage4_talk_22", pObject);

	return S_OK;
}

void CStage4::Release(void)
{
	ENGINE::CInfoSubject::DestroyInstance(); //! subject의 구조상 문제 때문에, 그냥 넘기면 뻑이 남.. 걍 지웠다 다시 만들자..
}
