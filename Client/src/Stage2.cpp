#include "stdafx.h"
#include "Stage2.h"

#include "Export_Function.h"
#include "SceneSelector.h"

#include "Terrain.h"
#include "Layer.h"
#include "StaticCamera.h"
#include "CharacterGroup.h"
#include "Character.h"

#include "Transform.h"
#include "Event_Concrete_Functors.h"
#include "PlaneObject.h"
#include "EmptyObject.h"
#include "Col_Event_Functors.h"
#include "etcGroup.h"
#include "Treasurechest.h"
#include "BillboardObject.h"
#include "WildBoar.h"

CStage2::CStage2(void)
{

}

CStage2::~CStage2(void)
{
	Release();
}

CStage2* CStage2::Create(CScene* _pScene /*= NULL*/)
{
	CStage2* pInstance = new CStage2;
	HRESULT hr = pInstance->Initialize(_pScene);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CStage2::Update(void)
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

void CStage2::Render(void)
{
	ENGINE::CScene::Render();
}

HRESULT CStage2::LoadDynamicResources(void)
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

	return S_OK;
}

HRESULT CStage2::CreateDynamicObjects(void)
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

void CStage2::ResetEvent()
{
	ENGINE::GetEventManager()->SwitchOn(L"FadeinAtStage2");

	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_SIZZ)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_MARIA)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_ELLUARD)->GetMemento()->clear();
	static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_TENZI)->GetMemento()->clear();
}

HRESULT CStage2::Initialize(CScene* _pScene /*= NULL*/)
{
	HRESULT hr = NULL;

	m_wstrBgmKey = L"BGMField.mp3";

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
	ENGINE::CGameEvent* pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeinAtStage2(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeinAtStage2");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeoutAtStage2ToStage1(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeoutAtStage2ToStage1");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_SceneChangeAtStage2ToStage1(SCENE_ID_STAGE_1), false);
	pEvent->AddCondition(L"SceneChangeAtStage2ToStage1");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_FadeoutAtStage2ToStage3(static_cast<CPlaneObject*>(pPlane)), false);
	pEvent->AddCondition(L"FadeoutAtStage2ToStage3");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_SceneChangeAtStage2ToStage3(SCENE_ID_STAGE_3), false);
	pEvent->AddCondition(L"SceneChangeAtStage2ToStage3");
	AddEvent(pEvent);

	// 미니 전투 이벤트..
	CTalkbox* pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_00"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_00(pTalk));
	pEvent->AddCondition(L"stage2_talk_00");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_01"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_01(pTalk));
	pEvent->AddCondition(L"stage2_talk_01");
	AddEvent(pEvent);

	// 미니 전투 지역을 향해 달려감..
	ENGINE::CCharacter* pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_SIZZ);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Move_00(pChar, D3DXVECTOR3(25.5f, 0.f, 13.15f)));
	pEvent->AddCondition(L"stage2_move_00");
	AddEvent(pEvent);

	pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_MARIA);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Move_01(pChar, D3DXVECTOR3(26.5f, 0.f, 13.f)));
	pEvent->AddCondition(L"stage2_move_01");
	AddEvent(pEvent);

	pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_ELLUARD);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Move_02(pChar, D3DXVECTOR3(27.f, 0.f, 13.75f)));
	pEvent->AddCondition(L"stage2_move_02");
	AddEvent(pEvent);

	pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_TENZI);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Move_03(pChar, D3DXVECTOR3(25.25f, 0.f, 13.75f)));
	pEvent->AddCondition(L"stage2_move_03");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Wait_00(), false);
	pEvent->AddCondition(L"stage2_move_00_finish");
	pEvent->AddCondition(L"stage2_move_01_finish");
	pEvent->AddCondition(L"stage2_move_02_finish");
	pEvent->AddCondition(L"stage2_move_03_finish");
	AddEvent(pEvent);

	// 미니 전투 직전 대화..
	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_02"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_02(pTalk));
	pEvent->AddCondition(L"stage2_talk_02");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_03"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_03(pTalk));
	pEvent->AddCondition(L"stage2_talk_03");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_04"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_04(pTalk));
	pEvent->AddCondition(L"stage2_talk_04");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_05"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_05(pTalk));
	pEvent->AddCondition(L"stage2_talk_05");
	AddEvent(pEvent);


	// 던젼 들어가기 직전..
	pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_SIZZ);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Move_04(pChar, D3DXVECTOR3(8.5f, 0.f, 22.5f)));
	pEvent->AddCondition(L"stage2_move_04");
	AddEvent(pEvent);

	pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_MARIA);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Move_05(pChar, D3DXVECTOR3(8.25f, 0.f, 21.5f)));
	pEvent->AddCondition(L"stage2_move_05");
	AddEvent(pEvent);

	pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_ELLUARD);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Move_06(pChar, D3DXVECTOR3(9.5f, 0.f, 22.5f)));
	pEvent->AddCondition(L"stage2_move_06");
	AddEvent(pEvent);

	pChar = static_cast<ENGINE::CCharacterGroup*>(m_LayerMap[LAYER_ID_INGAME]->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_TENZI);
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Move_07(pChar, D3DXVECTOR3(9.25f, 0.f, 21.5f)));
	pEvent->AddCondition(L"stage2_move_07");
	AddEvent(pEvent);
	// 던젼 입장 전 대화..
	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_06"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_06(pTalk));
	pEvent->AddCondition(L"stage2_talk_06");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_07"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_07(pTalk));
	pEvent->AddCondition(L"stage2_talk_07");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_08"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_08(pTalk));
	pEvent->AddCondition(L"stage2_talk_08");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_09"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_09(pTalk));
	pEvent->AddCondition(L"stage2_talk_09");
	AddEvent(pEvent);

	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Wait_01(), false);
	pEvent->AddCondition(L"stage2_move_04_finish");
	pEvent->AddCondition(L"stage2_move_05_finish");
	pEvent->AddCondition(L"stage2_move_06_finish");
	pEvent->AddCondition(L"stage2_move_07_finish");
	AddEvent(pEvent);

	// npc 구해주는 이벤트..
	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_11"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_11(pTalk));
	pEvent->AddCondition(L"stage2_talk_11");
	AddEvent(pEvent);
	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_12"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_12(pTalk));
	pEvent->AddCondition(L"stage2_talk_12");
	AddEvent(pEvent);
	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_13"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_13(pTalk));
	pEvent->AddCondition(L"stage2_talk_13");
	AddEvent(pEvent);
	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_14"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_14(pTalk));
	pEvent->AddCondition(L"stage2_talk_14");
	AddEvent(pEvent);
	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_15"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_15(pTalk));
	pEvent->AddCondition(L"stage2_talk_15");
	AddEvent(pEvent);

	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_21"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_21(pTalk));
	pEvent->AddCondition(L"stage2_talk_21");
	AddEvent(pEvent);
	pTalk = static_cast<CTalkbox*>(m_LayerMap[LAYER_ID_UI]->GetGameObject(L"stage2_talk_22"));
	pEvent = ENGINE::CGameEvent::Create(new CEvn_Stage2_Talk_22(pTalk));
	pEvent->AddCondition(L"stage2_talk_22");
	AddEvent(pEvent);

	ENGINE::GetEventManager()->CreateSwitch(L"stage2_npctalk_finish");
	ENGINE::GetEventManager()->CreateSwitch(L"stage2_box_open");

	ENGINE::GetEventManager()->SwitchOn(L"FadeinAtStage2");

	ENGINE::GetSoundManager()->PlayBGM(L"BGMField.mp3");

	//! 과연.. 효과있다?
	ENGINE::GetTimeManager()->SetTime();
	return S_OK;
}

HRESULT CStage2::AddEnvironmentLayerObject(void)
{	
	ENGINE::CGameObject* pObject = NULL;

	pObject = CTerrain::Create(OBJECT_TYPE_DYNAMIC, L"../bin/Data/Stage2_32_32.dat", L"Terrain_Stage2");
	if (pObject == NULL)
		return E_FAIL;
	m_LayerMap[LAYER_ID_ENVIRONMENT]->AddObject(L"Terrain", pObject);

	return S_OK;
}

HRESULT CStage2::AddIngameLayerObject(void)
{
	ENGINE::CGameObject* pObject = NULL;

	CEmptyObject* pEmptyObj = CEmptyObject::Create(OBJECT_TYPE_DYNAMIC, new CColSwitchOn(L"FadeoutAtStage2ToStage1"), 1.f, 1.f, 0.75f);
	pEmptyObj->SetPos(27.5f, 0.5f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"ToStage1", pEmptyObj);

	pEmptyObj = CEmptyObject::Create(OBJECT_TYPE_DYNAMIC, new CColSwitchOn(L"FadeoutAtStage2ToStage3"), 0.3f, 0.3f, 0.2f);
	pEmptyObj->SetPos(9.5f, 22.75f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"ToStage3", pEmptyObj);

	pEmptyObj = CEmptyObject::Create(OBJECT_TYPE_DYNAMIC, new CColSwitchOn(L"stage2_talk_00"), 1.5f, 1.f, 0.5f);
	pEmptyObj->SetPos(25.f, 7.f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"Help", pEmptyObj);

	pEmptyObj = CEmptyObject::Create(OBJECT_TYPE_DYNAMIC, new CColSwitchOn(L"stage2_move_00"), 0.75f, 1.f, 0.75f);
	pEmptyObj->SetPos(25.5f, 11.5f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"MiniBattle", pEmptyObj);

	pEmptyObj = CEmptyObject::Create(OBJECT_TYPE_DYNAMIC, new CColSwitchOn(L"stage2_move_04"), 1.5f, 1.f, 1.25f);
	pEmptyObj->SetPos(9.5f, 22.5f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"BeforeEnterDungeon", pEmptyObj);

	// npc
	CBillboardObject* pBill = CBillboardObject::Create(OBJECT_TYPE_DYNAMIC, L"NPC1_STAND");
	pBill->SetPos(26.5f, 15.f);
	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"NPC", pBill);


	// monster..
	pObject = ENGINE::CMonsterGroup::Create(OBJECT_TYPE_DYNAMIC);
	ENGINE::CMonster* pMonster = CWildBoar::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(26.f, 0.f, 13.5f)); if(pMonster == NULL)	return E_FAIL;
	pMonster->SetOwner(static_cast<ENGINE::CMonsterGroup*>(pObject));
	((ENGINE::CMonsterGroup*)pObject)->AddMonster(pMonster);

	pMonster = CWildBoar::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(28.f, 0.f, 14.5f)); if(pMonster == NULL)	return E_FAIL;
	pMonster->SetOwner(static_cast<ENGINE::CMonsterGroup*>(pObject));
	((ENGINE::CMonsterGroup*)pObject)->AddMonster(pMonster);

	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"MonsterGroup1", pObject);

	// 보물상자..
	for(int i = 0; i < 2; ++i)
	{
		pObject = ENGINE::CetcGroup::Create(OBJECT_TYPE_DYNAMIC);
		ENGINE::Cetc* petc = CTreasurechest::Create(OBJECT_TYPE_DYNAMIC, D3DXVECTOR3(20.f, (float(i) / 3.3f) + 1.7f, 22.5f), i);
		((ENGINE::CetcGroup*)pObject)->Addetc(petc);
		m_LayerMap[LAYER_ID_INGAME]->AddObject(L"tresurebox1", pObject);
	}


	return S_OK;
}

HRESULT CStage2::AddUIAndCursorLayerObject(void)
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


	// event용 대화상자..
	ENGINE::SMART_TEXT text(L"[비명 소리]\n도와주세요!!!");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_00", pObject);

	text = ENGINE::SMART_TEXT(L"[엘류어드]\n누군가 도움을 요청하고 있다! 구하러 가야 한다!");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pElluardTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_01", pObject);

	text = ENGINE::SMART_TEXT(L"[비명 소리의 주인]\n도와주세요!!!");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_02", pObject);

	text = ENGINE::SMART_TEXT(L"[몬스터]\n꾸욱 꾸욱");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_03", pObject);

	text = ENGINE::SMART_TEXT(L"[엘류어드]\n내가 구해드리겠소!");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pElluardTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_04", pObject);

	text = ENGINE::SMART_TEXT(L"[텐지]\n다들 조심해!");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pTenziTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_05", pObject);

	// 여기서부터 4개는 던젼 입장 전 대화임..
	text = ENGINE::SMART_TEXT(L"[시즈]\n너무 어두운 것 같아..");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pSizzTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_06", pObject);

	text = ENGINE::SMART_TEXT(L"[마리아]\n악당이 있을 만한 곳이군.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pMariaTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_07", pObject);

	text = ENGINE::SMART_TEXT(L"[엘류어드]\n달란트가 있을까?");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pElluardTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_08", pObject);

	text = ENGINE::SMART_TEXT(L"[텐지]\n......");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pTenziTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_09", pObject);

	// npc 구해주는 이벤트..
	text = ENGINE::SMART_TEXT(L"[마을 주민]\n구해주셔서 감사합니다.. 흑흑..");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_11", pObject);

	text = ENGINE::SMART_TEXT(L"[엘류어드]\n무사해서 다행이오.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, m_pElluardTalk);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_12", pObject);

	text = ENGINE::SMART_TEXT(L"[마을 주민]\n약소하지만 제 감사의 마음입니다. 받아주세요.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_13", pObject);

	text = ENGINE::SMART_TEXT(L"건빵(5)을 얻었다.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_14", pObject);

	text = ENGINE::SMART_TEXT(L"[마을 주민]\n정말 감사합니다. 당신들은 제 생명의 은인이세요.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_15", pObject);

	// 보물상자..
	text = ENGINE::SMART_TEXT(L"포도주를 얻었다.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_21", pObject);

	text = ENGINE::SMART_TEXT(L"비었다.");
	pObject = CTalkbox::Create(OBJECT_TYPE_DYNAMIC, text, m_pTalkbox, NULL);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"stage2_talk_22", pObject);

	return S_OK;
}

void CStage2::Release(void)
{
	ENGINE::CInfoSubject::DestroyInstance(); //! subject의 구조상 문제 때문에, 그냥 넘기면 뻑이 남.. 걍 지웠다 다시 만들자..
}
