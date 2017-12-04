#include "stdafx.h"
#include "Stage1.h"

#include "Export_Function.h"
#include "SceneSelector.h"

#include "Terrain.h"
#include "Layer.h"
#include "StaticCamera.h"
#include "CharacterGroup.h"
#include "Character.h"
#include "Transform.h"
#include "WildBoar.h"
#include "Hedgehog.h"
#include "Chimera.h"
#include "PoisonSpider.h"
#include "PoisonJelly.h"
#include "Skeleton.h"
#include "MonsterGroup.h"
#include "etcGroup.h"
#include "Water.h"
#include "Akhenaton.h"
#include "Treasurechest.h"

#include "PlaneObject.h"
#include "GameEvent.h"
#include "Event_Concrete_Functors.h"
#include "EmptyObject.h"
#include "SmartText.h"
#include "Talkbox.h"
#include "Col_Event_Functors.h"
#include "BillboardObject.h"
#include "SealObject.h"
#include "SwitchObject.h"

CStage1::CStage1(void)
{

}

CStage1::~CStage1(void)
{
	Release();
}

CStage1* CStage1::Create(CScene* _pScene /*= NULL*/)
{
	CStage1* pInstance = new CStage1;
	HRESULT hr = pInstance->Initialize(_pScene);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CStage1::Update(void)
{
	//! �����δ� ���� ������ yes, no�� ���� ȭ���� ���߰�����..
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

void CStage1::Render(void)
{
	ENGINE::CScene::Render();
}

HRESULT CStage1::LoadDynamicResources(void)
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
		TEXTURE_TYPE_NORMAL,
		L"Texture_Water",
		L"../bin/Resources/Texture/etc/Water/water%d.png",
		32);
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CStage1::CreateDynamicObjects(void)
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

HRESULT CStage1::Initialize(CScene* _pScene /*= NULL*/)
{
	HRESULT hr = NULL;
	
	m_wstrBgmKey = L"BGMField.mp3";

	// 1. static resource, object ���� �õ�..
	// ���� �����ߴٸ� ���������� �ι� ������ �����ֹǷ� ������ �ᵵ �ȴ�..
	hr = CStage::AddStatics(_pScene);
	if FAILED(hr)
		return hr;

	// 2. �� ������ ����ϴ� ���ҽ����� �� �Լ� ������..
	hr = LoadDynamicResources();
	if FAILED(hr)
		return hr;

	// 3. �� ���̾ ���̳��� ������Ʈ�� �����ؼ� �־���..
	hr = CreateDynamicObjects();
	if FAILED(hr)
		return hr;


	// Add Events
	CTalkbox* pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"talk_00"));
	ENGINE::CGameEvent* pEvent = ENGINE::CGameEvent::Create(new CEvn_Talk_00(pTalk));
	pEvent->AddCondition(L"stage1_talk_00");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"talk_01"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Talk_01(pTalk));
	pEvent->AddCondition(L"stage1_talk_01");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"talk_02"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Talk_02(pTalk));
	pEvent->AddCondition(L"stage1_talk_02");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"talk_03"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Talk_03(pTalk));
	pEvent->AddCondition(L"stage1_talk_03");
	AddEvent(pEvent);



	// �������ڸ���..
	ENGINE::CCharacter* pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_SIZZ);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Move_00(pChar, D3DXVECTOR3(4.f, 0.f, 1.1f + 4.5f)));
	pEvent->AddCondition(L"stage1_move_00");
	AddEvent(pEvent);

	pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_MARIA);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Move_01(pChar, D3DXVECTOR3(4.8f, 0.f, 0.9f + 4.5f)));
	pEvent->AddCondition(L"stage1_move_01");
	AddEvent(pEvent);

	pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_ELLUARD);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Move_02(pChar, D3DXVECTOR3(5.f, 0.f, 1.6f + 4.5f)));
	pEvent->AddCondition(L"stage1_move_02");
	AddEvent(pEvent);

	pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_TENZI);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Move_03(pChar, D3DXVECTOR3(4.2f, 0.f, 2.1f + 4.5f)));
	pEvent->AddCondition(L"stage1_move_03");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_Wait_00(), false);
	pEvent->AddCondition(L"stage1_move_00_finish");
	pEvent->AddCondition(L"stage1_move_01_finish");
	pEvent->AddCondition(L"stage1_move_02_finish");
	pEvent->AddCondition(L"stage1_move_03_finish");
	AddEvent(pEvent);

	// ���� �Ա��� ���̹޾��� �� ó��..
	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"talk_04"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Talk_04(pTalk));
	pEvent->AddCondition(L"stage1_talk_04");
	AddEvent(pEvent);

	pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_SIZZ);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Move_04(pChar, D3DXVECTOR3(2.5f, 0.f, 2.f)));
	pEvent->AddCondition(L"stage1_move_04");
	AddEvent(pEvent);


	ENGINE::CGameObject* pPlane = NULL;
	pPlane = m_LayerMap[LAYER_ID_UI]->GetGameObject(L"AAfull_overlap");
	pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeinAtStage1(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeinAtStage1");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeoutAtStage1(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeoutAtStage1");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_SceneChangeAtStage1ToStage2(SCENE_ID_STAGE_2), false);
	pEvent->AddCondition(L"SceneChangeAtMainmenuToStage2");
	AddEvent(pEvent);


	ENGINE::GetEventManager()->SwitchOn(L"FadeinAtStage1");

	ENGINE::GetSoundManager()->PlayBGM(L"BGMField.mp3");

	//! ����.. ȿ���ִ�?
	ENGINE::GetTimeManager()->SetTime();
	return S_OK;
}

HRESULT CStage1::AddEnvironmentLayerObject(void)
{
	ENGINE::CGameObject* pObject = NULL;

	pObject = CTerrain::Create(OBJECT_TYPE_DYNAMIC, L"../bin/Data/Stage1_32_32.dat", L"Terrain_Stage1");
	if (pObject == NULL)
		return E_FAIL;
	m_LayerMap[LAYER_ID_ENVIRONMENT]->AddObject(L"Terrain", pObject);


	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 6; ++j)
		{
			float	fStart = 0.03f;
			if((i + j) % 2 == 1)
				fStart = -0.03f;
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			ENGINE::Cetc* petc = CWater::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(12.5f + (float(j) * 1.28f), -0.4f, 0.f + (float(i) * 1.28f)), fStart);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 7; ++j)
		{
			float	fStart = 0.03f;
			if((i + j) % 2 == 1)
				fStart = -0.03f;
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			ENGINE::Cetc* petc = CWater::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(15.06f + (float(j) * 1.28f), -0.4f, 2.56f + (float(i) * 1.28f)), fStart);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			float	fStart = 0.03f;
			if((i + j) % 2 == 1)
				fStart = -0.03f;
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			ENGINE::Cetc* petc = CWater::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(20.18f + (float(j) * 1.28f), -0.4f, 5.12f + (float(i) * 1.28f)), fStart);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			float	fStart = 0.03f;
			if((i + j) % 2 == 1)
				fStart = -0.03f;
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			ENGINE::Cetc* petc = CWater::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(21.46f + (float(j) * 1.28f), -0.4f, 7.68f + (float(i) * 1.28f)), fStart);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
	ENGINE::Cetc* petc = CWater::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(25.3f, -0.4f, 6.4f), false);
	((ENGINE::CetcGroup*)pObject)->Addetc(petc);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			float	fStart = 0.03f;
			if((i + j) % 2 == 1)
				fStart = -0.03f;
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			ENGINE::Cetc* petc = CWater::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(22.74f + (float(j) * 1.28f), -0.4f, 10.24f + (float(i) * 1.28f)), fStart);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			float	fStart = 0.03f;
			if((i + j) % 2 == 1)
				fStart = -0.03f;
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			ENGINE::Cetc* petc = CWater::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(22.74f + (float(j) * 1.28f), -0.4f, 12.8f + (float(i) * 1.28f)), fStart);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 1; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			float	fStart = 0.03f;
			if((i + j) % 2 == 1)
				fStart = -0.03f;
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			ENGINE::Cetc* petc = CWater::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(22.74f + (float(j) * 1.28f), -0.4f, 15.36f + (float(i) * 1.28f)), fStart);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			float	fStart = 0.03f;
			if((i + j) % 2 == 1)
				fStart = -0.03f;
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			ENGINE::Cetc* petc = CWater::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(22.74f + (float(j) * 1.28f), -0.4f, 16.64f + (float(i) * 1.28f)), fStart);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			float	fStart = 0.03f;
			if((i + j) % 2 == 1)
				fStart = -0.03f;
			pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
			ENGINE::Cetc* petc = CWater::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(22.74f + (float(j) * 1.28f), -0.4f, 20.48f + (float(i) * 1.28f)), fStart);
			((ENGINE::CetcGroup*)pObject)->Addetc(petc);
			m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
		}
	}
	/*for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		petc = CTreasurechest::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(10.f, (float(i) / 3.33f) + 0.5f, 10.f), i);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"etcGroup1", pObject);
	}*/

	return S_OK;
}

HRESULT CStage1::AddIngameLayerObject(void)
{
	ENGINE::CGameObject* pObject = NULL;

	
	// for event
	CEmptyObject* pEmptyObj = CEmptyObject::Create(OBJECT_TYPE_DYNAMIC, new CColSwitchOn(L"stage1_talk_04"), 1.f, 1.f, 0.75f);
	pEmptyObj->SetPos(1.5f, 0.f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"ToVillageEvent", pEmptyObj);

	pEmptyObj = CEmptyObject::Create(OBJECT_TYPE_DYNAMIC, new CColSwitchOn(L"FadeoutAtStage1"), 1.f, 1.f, 0.75f);
	pEmptyObj->SetPos(21.5f, 30.5f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"ToStage2", pEmptyObj);


	return S_OK;
}

HRESULT CStage1::AddUIAndCursorLayerObject(void)
{
	ENGINE::CGameObject* pObject = NULL;


	pObject = CStaticCamera::Create(OBJECT_TYPE_DYNAMIC,
		static_cast<CTerrain*>(m_LayerMap[LAYER_ID_ENVIRONMENT]->GetGameObject(L"Terrain"))->GetTerrainInfo());
	if (pObject == NULL)
		return E_FAIL;
	m_LayerMap[LAYER_ID_UI]->AddObject(L"Camera", pObject);
	// scene�� init�ϴ� ���̶�, ������, ĳ���� �׷� ã�Ƽ� �޾���� �ϴ� �һ��..
	ENGINE::CGameObject* pObj = m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup");
	pObj = static_cast<ENGINE::CCharacterGroup*>(pObj)->GetLeaderCharacter();
	pObj->PrepareFind();
	ENGINE::CComponent* pComponent = pObj->GetComponent(L"Transform");
	static_cast<CStaticCamera*>(pObject)->SetTargetInfo(static_cast<ENGINE::CTransform*>(pComponent));


	// event�� ��ȭ����..
	ENGINE::SMART_TEXT text(L"[����]\n�� �̷��� ���߿� �̵��ؾ���?");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pSizzTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"talk_00", pObject);

	text = ENGINE::SMART_TEXT(L"[������]\n�ð��� ����.\n�ѽö� ���� �������� ��ġ�� ó����� ���ؾ� ��.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pMariaTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"talk_01", pObject);

	text = ENGINE::SMART_TEXT(L"[�������]\n���� ����. �޶�Ʈ�� �װ��� ���� ���� �𸥴�.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pElluardTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"talk_02", pObject);

	text = ENGINE::SMART_TEXT(L"[����]\n���� ��� ���� �ٴٸ� �� ���� �ɼ�.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pTenziTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"talk_03", pObject);

	text = ENGINE::SMART_TEXT(L"[�������]\n���� ������ ���ư� �� ����. �ؾ� �� ���� �����ִ�.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pElluardTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"talk_04", pObject);


	return S_OK;
}

void CStage1::Release(void)
{
	ENGINE::CInfoSubject::DestroyInstance(); //! subject�� ������ ���� ������, �׳� �ѱ�� ���� ��.. �� ������ �ٽ� ������..
}

void CStage1::ResetEvent(void)
{
	ENGINE::GetEventManager()->SwitchOn(L"FadeinAtStage1");

	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_SIZZ)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_MARIA)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_ELLUARD)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_TENZI)->GetMemento()->clear();
}
