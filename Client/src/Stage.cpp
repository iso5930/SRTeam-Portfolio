#include "stdafx.h"
#include "Stage.h"

#include "Layer.h"
#include "CharacterGroup.h"
#include "Character_Sizz.h"
#include "Character_Maria.h"
#include "MainMenu.h"
#include "Inventory.h"
#include "Navi.h"
#include "Treasurechest.h"

#include "Export_Function.h"
#include "Character_Elluard.h"
#include "Character_Tenzi.h"
#include "MouseCursor.h"
#include "PlaneObject.h"

bool CStage::m_bStaticsLoaded = false;


CPlaneObject* CStage::m_pTalkbox = NULL;
CPlaneObject* CStage::m_pSizzTalk = NULL;
CPlaneObject* CStage::m_pMariaTalk = NULL;
CPlaneObject* CStage::m_pElluardTalk = NULL;
CPlaneObject* CStage::m_pTenziTalk = NULL;

CStage::CStage(void)
{

}

CStage::~CStage(void)
{

}

HRESULT CStage::AddStatics(CScene* _pScene /*= NULL*/)
{
	/*if (m_bStaticsLoaded)
		return S_OK;*/

	HRESULT hr = NULL;

	if (!m_bStaticsLoaded)
	{
		hr = LoadIngameStaticTextures();
		if FAILED(hr)
			return hr;

		hr = LoadIngameUIResources();
		if FAILED(hr)
			return hr;
	}

	hr = CreateLayers();
	if FAILED(hr)
		return hr;

	if (m_bStaticsLoaded)
	{
		hr = GetStaticObject(_pScene);
		if FAILED(hr)
			return hr;
	}
	else
	{
		hr = AddStaticObjects();
		if FAILED(hr)
			return hr;
	}

	m_bStaticsLoaded = true;
	return S_OK;
}

HRESULT CStage::CreateLayers(void)
{
	ENGINE::CLayer* pLayer = NULL;
	
	pLayer = ENGINE::CLayer::Create();
	if (pLayer == NULL)
		return E_FAIL;
	m_LayerMap.insert(LAYER_MAP::value_type(LAYER_ID_ENVIRONMENT, pLayer));

	pLayer = ENGINE::CLayer::Create();
	if (pLayer == NULL)
		return E_FAIL;
	m_LayerMap.insert(LAYER_MAP::value_type(LAYER_ID_INGAME, pLayer));

	pLayer = ENGINE::CLayer::Create();
	if (pLayer == NULL)
		return E_FAIL;
	m_LayerMap.insert(LAYER_MAP::value_type(LAYER_ID_UI, pLayer));

	pLayer = ENGINE::CLayer::Create();
	if (pLayer == NULL)
		return E_FAIL;
	m_LayerMap.insert(LAYER_MAP::value_type(LAYER_ID_CURSOR, pLayer));

	return S_OK;
}

HRESULT CStage::AddStaticObjects(void)
{
	ENGINE::CGameObject* pObject = NULL;

	//=== 캐릭터 그룹 추가
	pObject = ENGINE::CCharacterGroup::Create(OBJECT_TYPE_STATIC);

	ENGINE::CCharacter* pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);
	pCharacter->SetOwner((ENGINE::CCharacterGroup*)pObject);
	dynamic_cast<ENGINE::CCharacterGroup*>(pObject)->AddCharacter(CHARACTER_SIZZ, pCharacter);

	pCharacter = CCharacter_Maria::Create(OBJECT_TYPE_STATIC);
	pCharacter->SetOwner((ENGINE::CCharacterGroup*)pObject);
	dynamic_cast<ENGINE::CCharacterGroup*>(pObject)->AddCharacter(CHARACTER_MARIA, pCharacter);

	pCharacter = CCharacter_Elluard::Create(OBJECT_TYPE_STATIC);
	pCharacter->SetOwner((ENGINE::CCharacterGroup*)pObject);
	dynamic_cast<ENGINE::CCharacterGroup*>(pObject)->AddCharacter(CHARACTER_ELLUARD, pCharacter);
	
	pCharacter = CCharacter_Tenzi::Create(OBJECT_TYPE_STATIC);
	pCharacter->SetOwner((ENGINE::CCharacterGroup*)pObject);
	dynamic_cast<ENGINE::CCharacterGroup*>(pObject)->AddCharacter(CHARACTER_TENZI, pCharacter);



	//ENGINE::CCharacter* pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);


	/*ENGINE::CCharacter* pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);

	ENGINE::CCharacter* pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);


	pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);

	pCharacter->SetOwner((ENGINE::CCharacterGroup*)pObject);
	dynamic_cast<ENGINE::CCharacterGroup*>(pObject)->AddCharacter(CHARACTER_SIZZ, pCharacter);*/

	m_LayerMap[LAYER_ID_INGAME]->AddObject(L"CharacterGroup", pObject);
	//=== 캐릭터 그룹 추가.
//<<<<<<< .mine	
////	//ENGINE::CCharacter* pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);
////	//pCharacter->SetOwner((ENGINE::CCharacterGroup*)pObject);
////	//dynamic_cast<ENGINE::CCharacterGroup*>(pObject)->AddCharacter(CHARACTER_SIZZ, pCharacter);
////<<<<<<< .mine
////
////<<<<<<< .mine
////	//ENGINE::CCharacter* pCharacter = CCharacter_Tenzi::Create(OBJECT_TYPE_STATIC);
////	//pCharacter->SetOwner((ENGINE::CCharacterGroup*)pObject);
////	//dynamic_cast<ENGINE::CCharacterGroup*>(pObject)->AddCharacter(CHARACTER_TENZI, pCharacter);
////=======
////
////	/*ENGINE::CCharacter* pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);
////=======
////
////	ENGINE::CCharacter* pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);
////>>>>>>> .r297
////	pCharacter->SetOwner((ENGINE::CCharacterGroup*)pObject);
////	dynamic_cast<ENGINE::CCharacterGroup*>(pObject)->AddCharacter(CHARACTER_SIZZ, pCharacter);
////>>>>>>> .r302
//=======
//	//ENGINE::CCharacter* pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);
//	//pCharacter->SetOwner((ENGINE::CCharacterGroup*)pObject);
//	//dynamic_cast<ENGINE::CCharacterGroup*>(pObject)->AddCharacter(CHARACTER_SIZZ, pCharacter);
//
//
//<<<<<<< .mine
//>>>>>>> .r307
//	//ENGINE::CCharacter* pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);
//
//
//<<<<<<< .mine
//=======
//	/*ENGINE::CCharacter* pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);
//=======
//	ENGINE::CCharacter* pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);
//>>>>>>> .r305
//
//<<<<<<< .mine
//=======
//	pCharacter = CCharacter_Sizz::Create(OBJECT_TYPE_STATIC);
//>>>>>>> .r305
//	pCharacter->SetOwner((ENGINE::CCharacterGroup*)pObject);
//	dynamic_cast<ENGINE::CCharacterGroup*>(pObject)->AddCharacter(CHARACTER_SIZZ, pCharacter);*/
//
//
//>>>>>>> .r307


	//메인 UI 추가
	pObject = CMainMenu::Create(OBJECT_TYPE_STATIC);
	if(pObject == NULL)
		return E_FAIL;
	m_LayerMap[LAYER_ID_UI]->AddObject(L"ZZMainMenu", pObject);
	//메인 UI 추가

	//======= 인벤토리 추가
	pObject = ENGINE::CInventory::Create(OBJECT_TYPE_STATIC);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"Inventory", pObject);
	//======= 인벤토리 추가

	//======= Navi 추가
	pObject = CNavi::Create(OBJECT_TYPE_STATIC);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"Navi", pObject);
	//======= Navi 추가

	pObject = CPlaneObject::Create(OBJECT_TYPE_STATIC, L"ZZfull_overlap", true);
	static_cast<CPlaneObject*>(pObject)->SetPos(WINCX / 2.f, WINCY / 2.f);
	m_LayerMap[LAYER_ID_UI]->AddObject(L"AAfull_overlap", pObject);

	// 마우스 커서 추가
	pObject = ENGINE::CMouseCursor::Create(OBJECT_TYPE_STATIC);
	m_LayerMap[LAYER_ID_CURSOR]->AddObject(L"MouseCursor", pObject);

	// 대화상자 관련..
	m_pTalkbox = CPlaneObject::Create(OBJECT_TYPE_STATIC, L"talkbox", true);
	static_cast<CPlaneObject*>(m_pTalkbox)->SetPos(WINCX / 2.f, WINCY * 0.8f);

	m_pSizzTalk = CPlaneObject::Create(OBJECT_TYPE_STATIC, L"sizz_talk", true);
	static_cast<CPlaneObject*>(m_pSizzTalk)->SetPos(WINCX * 0.75f, WINCY * 0.5f);

	m_pMariaTalk = CPlaneObject::Create(OBJECT_TYPE_STATIC, L"maria_talk", true);
	static_cast<CPlaneObject*>(m_pMariaTalk)->SetPos(WINCX * 0.75f, WINCY * 0.5f);

	m_pElluardTalk = CPlaneObject::Create(OBJECT_TYPE_STATIC, L"elluard_talk", true);
	static_cast<CPlaneObject*>(m_pElluardTalk)->SetPos(WINCX * 0.75f, WINCY * 0.5f);

	m_pTenziTalk = CPlaneObject::Create(OBJECT_TYPE_STATIC, L"tenzi_talk", true);
	static_cast<CPlaneObject*>(m_pTenziTalk)->SetPos(WINCX * 0.75f, WINCY * 0.5f);

	return S_OK;
}

HRESULT CStage::LoadIngameUIResources(void)
{
	ENGINE::CResourceManager* pResourceManager = ENGINE::GetResourceManager();
	HRESULT hr = NULL;
	// load images
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"MainMenuBackGround", L"../bin/Resources/Texture/MainUI/MainMenu%d.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"CharStatePage", L"../bin/Resources/Texture/MainUI/CharState%d.png", 4); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"CharEquipPage", L"../bin/Resources/Texture/MainUI/CharEquip%d.png", 4); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"CharItemPage", L"../bin/Resources/Texture/MainUI/CharPage%d.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"LeftMenu", L"../bin/Resources/Texture/MainUI/LeftMenu%d.png", 3); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"TopMenu", L"../bin/Resources/Texture/MainUI/TopMenu%d.png", 5); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"DiaryItemPage", L"../bin/Resources/Texture/MainUI/DiaryItem%d.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"DiaryMonsterPage", L"../bin/Resources/Texture/MainUI/DiaryMonster%d.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"DiaryScrapPage", L"../bin/Resources/Texture/MainUI/DiaryScrap%d.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"TacticsPage", L"../bin/Resources/Texture/MainUI/TacticsPage%d.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"CharIconSubMenuDefault", L"../bin/Resources/Texture/MainUI/CharIcon%d.png", 4); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"CharIconSubMenuCur", L"../bin/Resources/Texture/MainUI/CharIconCur%d.png", 4); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"OKButton", L"../bin/Resources/Texture/MainUI/OK%d.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"ButtonIcon", L"../bin/Resources/Texture/MainUI/Button%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"Font", L"../bin/Resources/Texture/MainUI/Font/Font%d.png", 64, D3DCOLOR_ARGB(255, 0, 255, 0)); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"UIBar", L"../bin/Resources/Texture/MainUI/UIBar%d.png", 2); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"Scroll", L"../bin/Resources/Texture/MainUI/Scroll%d.png", 28, D3DCOLOR_ARGB(255, 151, 151, 195)); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"Item", L"../bin/Resources/Texture/Item/Test%d.png", 26, D3DCOLOR_ARGB(255, 255, 0, 255)); if FAILED(hr) return hr; //아이템 출력용 테스트, 쓰고 지움
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"Ability", L"../bin/Resources/Texture/MainUI/AbilityGauge%d.png", 3); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"AbilityFrame", L"../bin/Resources/Texture/MainUI/AbilityFrame%d.png", 1, D3DCOLOR_ARGB(255, 0, 255, 0)); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BarFrame", L"../bin/Resources/Texture/MainUI/BarFrame%d.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"Gauge", L"../bin/Resources/Texture/MainUI/Gauge%d.png", 2); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"FireMagicIcon", L"../bin/Resources/Texture/Magic/Icon/Fire%d.png", 4, D3DCOLOR_ARGB(255, 115, 67, 75)); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"IceMagicIcon", L"../bin/Resources/Texture/Magic/Icon/Ice%d.png", 4, D3DCOLOR_ARGB(255, 115, 67, 75)); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"WindMagicIcon", L"../bin/Resources/Texture/Magic/Icon/wind%d.png", 4, D3DCOLOR_ARGB(255, 115, 67, 75)); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"돌MagicIcon", L"../bin/Resources/Texture/Magic/Icon/돌%d.png", 4, D3DCOLOR_ARGB(255, 115, 67, 75)); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"MessageBox", L"../bin/Resources/Texture/MessageBox/MessageBox%d.png", 2); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"MessagePice", L"../bin/Resources/Texture/MessageBox/MessagePice%d.png", 79, D3DCOLOR_ARGB(255, 151, 151, 195)); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"AbilityType", L"../bin/Resources/Texture/AbilityType/AbilityType%d.png", 7, D3DCOLOR_ARGB(255, 0, 255, 0)); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"SlotCheak", L"../bin/Resources/Texture/MainUI/SlotCheak%d.png", 9, D3DCOLOR_ARGB(255, 183, 169, 111)); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"Navigation", L"../bin/Resources/Texture/Navi/Navi%d.png", 3, D3DCOLOR_ARGB(255, 252, 157, 110)); if FAILED(hr) return hr;

	//Battle UI
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleWindow", L"../bin/Resources/Texture/BattleUI/BattleIng/Window/BattleWindow%d.png", 2); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleFaceShape", L"../bin/Resources/Texture/BattleUI/BattleIng/Image/FaceShape.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleCharacterFace", L"../bin/Resources/Texture/BattleUI/BattleIng/Image/Face%d.bmp", 4); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleTurnShape", L"../bin/Resources/Texture/BattleUI/BattleIng/Image/TurnShape%d.png", 3); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"Ready", L"../bin/Resources/Texture/BattleUI/BattleIng/Text/Ready2.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"Action", L"../bin/Resources/Texture/BattleUI/BattleIng/Text/Action.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"RageCharacter", L"../bin/Resources/Texture/BattleUI/BattleIng/Image/RageCharacter%d.png", 4); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"RageText", L"../bin/Resources/Texture/BattleUI/BattleIng/Text/Rage%d.png", 2); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"RageGauge", L"../bin/Resources/Texture/BattleUI/BattleIng/StatusGauge/RageGauge.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"RageGaugeBar", L"../bin/Resources/Texture/BattleUI/BattleIng/StatusGauge/RageGaugeRed.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BP", L"../bin/Resources/Texture/BattleUI/BattleIng/StatusGauge/BP.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"HP", L"../bin/Resources/Texture/BattleUI/BattleIng/StatusGauge/HP.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"Bar", L"../bin/Resources/Texture/BattleUI/BattleIng/StatusGauge/Bar%d.png", 3); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"TextBP", L"../bin/Resources/Texture/BattleUI/BattleIng/Text/BP.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"TextHP", L"../bin/Resources/Texture/BattleUI/BattleIng/Text/HP.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"SPShape", L"../bin/Resources/Texture/BattleUI/BattleIng/StatusGauge/SpShape.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"SPGauge", L"../bin/Resources/Texture/BattleUI/BattleIng/StatusGauge/sp%d.png", 3); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"MagicName", L"../bin/Resources/Texture/BattleUI/BattleIng/Text/MagicName%d.png", 3); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"SkillName", L"../bin/Resources/Texture/BattleUI/BattleIng/Text/SkillName%d.png", 3); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"TurnBar", L"../bin/Resources/Texture/BattleUI/BattleIng/Image/TurnBar.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"NormalFont", L"../bin/Resources/Texture/BattleUI/BattleIng/NormalFont/%d.png", 10); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"MaxFont", L"../bin/Resources/Texture/BattleUI/BattleIng/MaxFont/%d.png", 10); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"PlayerTurnFace", L"../bin/Resources/Texture/BattleUI/BattleIng/Image/CharIcon%d.png", 4); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleCharName", L"../bin/Resources/Texture/BattleUI/BattleIng/Text/CharName%d.png", 4); if FAILED(hr)	return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleUIMonster", L"../bin/Resources/Texture/BattleUI/BattleIng/Image/BattleUIMonster%d.png", 7); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"TypeName", L"../bin/Resources/Texture/BattleUI/BattleIng/Text/TypeName%d.png", 4); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"MonsterTurnIcon", L"../bin/Resources/Texture/BattleUI/BattleIng/Image/TurnIcon%d.png", 7); if FAILED(hr) return hr;

	//Battle_End_UI
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleEndFont", L"../bin/Resources/Texture/BattleUI/BattleEnd/Font/%d.png", 10); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleEndWindow", L"../bin/Resources/Texture/BattleUI/BattleEnd/BattleEndWindow.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleResult", L"../bin/Resources/Texture/BattleUI/BattleEnd/BattleResult.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"ExpGet", L"../bin/Resources/Texture/BattleUI/BattleEnd/Get.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleLevel", L"../bin/Resources/Texture/BattleUI/BattleEnd/Level.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleLevelUp", L"../bin/Resources/Texture/BattleUI/BattleEnd/levelup.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"NextExp", L"../bin/Resources/Texture/BattleUI/BattleEnd/Next.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"TotalExp", L"../bin/Resources/Texture/BattleUI/BattleEnd/Total.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleShadow", L"../bin/Resources/Texture/BattleUI/BattleEnd/Shadow.png", 1); if FAILED(hr) return hr;
	hr = pResourceManager->AddSprite(RESOURCE_TYPE_STATIC, L"BattleCharacter", L"../bin/Resources/Texture/BattleUI/BattleEnd/Character/%d.png", 4); if FAILED(hr) return hr;
	
	//! 하하..
	hr = ENGINE::GetResourceManager()->AddSprite(RESOURCE_TYPE_DYNAMIC, L"ZZfull_overlap", L"../bin/Resources/Texture/full_overlap.png", 1); if FAILED(hr)	return hr;
	hr = ENGINE::GetResourceManager()->AddSprite(RESOURCE_TYPE_DYNAMIC, L"talkbox", L"../bin/Resources/Texture/MessageBox/ChatMessageBox.png", 1); if FAILED(hr)	return hr;
	hr = ENGINE::GetResourceManager()->AddSprite(RESOURCE_TYPE_DYNAMIC, L"sizz_talk", L"../bin/Resources/Texture/Character/sizz_talk.png", 1); if FAILED(hr)	return hr;
	hr = ENGINE::GetResourceManager()->AddSprite(RESOURCE_TYPE_DYNAMIC, L"maria_talk", L"../bin/Resources/Texture/Character/maria_talk.png", 1); if FAILED(hr)	return hr;
	hr = ENGINE::GetResourceManager()->AddSprite(RESOURCE_TYPE_DYNAMIC, L"elluard_talk", L"../bin/Resources/Texture/Character/elluard_talk.png", 1); if FAILED(hr)	return hr;
	hr = ENGINE::GetResourceManager()->AddSprite(RESOURCE_TYPE_DYNAMIC, L"tenzi_talk", L"../bin/Resources/Texture/Character/tenzi_talk.png", 1); if FAILED(hr)	return hr;

	//마우스 커서
	hr = ENGINE::GetResourceManager()->AddSprite(RESOURCE_TYPE_STATIC, L"Mouse_Cur", L"../bin/Resources/Texture/MouseCursor/Basic.png", 1); if FAILED(hr) return hr;

	return S_OK;
}

HRESULT CStage::LoadIngameStaticTextures(void)
{
	ENGINE::CResourceManager* pResourceManager = ENGINE::GetResourceManager();
	HRESULT hr = NULL;
	// load textures
	/*hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Sizz_Stand", L"../bin/Resources/Texture/Character/Sizz/Sizz_Stand/Sizz_Stand%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Sizz_Run", L"../bin/Resources/Texture/Character/Sizz/Sizz_Run/_Sizz_Run%d.png", 64); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Sizz_Att", L"../bin/Resources/Texture/Character/Sizz/Sizz_Att/Sizz_Att%d.png", 20); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Field_Stand", L"../bin/Resources/Texture/Character/Maria/Field/Stand/Maria_Field_Stand%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Field_Run", L"../bin/Resources/Texture/Character/Maria/Field/Run/Maria_Field_Run%d.png", 64); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Elluard_Stand", L"../bin/Resources/Texture/Character/Elluard/Elluard_Stand/Elluard_Stand%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Elluard_Run", L"../bin/Resources/Texture/Character/Elluard/Elluard_Run/Elluard_Run%d.png", 64); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tenzi_Stand", L"../bin/Resources/Texture/Character/Tenzi/Tenzi_Stand/Tenzi_Stand%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tenzi_Run", L"../bin/Resources/Texture/Character/Tenzi/Tenzi_Run/Tenzi_Run%d.png", 64); if FAILED(hr) return hr;*/
	//Sizz
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Sizz_Stand", L"../bin/Resources/Texture/Character/Sizz/Field/Stand/Sizz_Stand%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Sizz_Run", L"../bin/Resources/Texture/Character/Sizz/Field/Run/Sizz_Run%d.png", 64); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Sizz_Hit", L"../bin/Resources/Texture/Character/Sizz/Battle/Hit/Sizz_Hit%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Sizz_Battle_Stand", L"../bin/Resources/Texture/Character/Sizz/Battle/Stand/Sizz_Battle_Stand%d.png", 16); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Sizz_Battle_Run", L"../bin/Resources/Texture/Character/Sizz/Battle/Run/Sizz_Battle_Run%d.png", 32); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Sizz_Battle_Att", L"../bin/Resources/Texture/Character/Sizz/Battle/Att/Sizz_Battle_Att%d.png", 20); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Sizz_Battle_Magic", L"../bin/Resources/Texture/Character/Sizz/Battle/Magic/Sizz_Magic%d.png", 64); if FAILED(hr) return hr;
	
	//Maria
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Stand", L"../bin/Resources/Texture/Character/Maria/Field/Stand/Maria_Stand%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Run", L"../bin/Resources/Texture/Character/Maria/Field/Run/Maria_Run%d.png", 64); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Hit", L"../bin/Resources/Texture/Character/Maria/Battle/Hit/Maria_Hit%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Battle_Stand", L"../bin/Resources/Texture/Character/Maria/Battle/Stand/Maria_Battle_Stand%d.png", 16); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Battle_Run", L"../bin/Resources/Texture/Character/Maria/Battle/Run/Maria_Battle_Run%d.png", 32); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Battle_Att", L"../bin/Resources/Texture/Character/Maria/Battle/Att/Maria_Battle_Att%d.png", 24); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Skill1_Att", L"../bin/Resources/Texture/Character/Maria/Battle/Skill1/Att/Maria_Skill1_Att%d.png", 128); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Skill1_Run", L"../bin/Resources/Texture/Character/Maria/Battle/Skill1/Run/Maria_Skill1_Run%d.png", 16); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Skill2_Att", L"../bin/Resources/Texture/Character/Maria/Battle/Skill2/Att/Maria_Skill2_Att%d.png", 128); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Maria_Skill2_Run", L"../bin/Resources/Texture/Character/Maria/Battle/Skill2/Run/Maria_Skill2_Run%d.png", 16); if FAILED(hr) return hr;

	//Elluard
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Elluard_Stand", L"../bin/Resources/Texture/Character/Elluard/Field/Stand/Elluard_Stand%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Elluard_Run", L"../bin/Resources/Texture/Character/Elluard/Field/Run/Elluard_Run%d.png", 64); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Elluard_Hit", L"../bin/Resources/Texture/Character/Elluard/Battle/Hit/Elluard_Hit%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Elluard_Battle_Stand", L"../bin/Resources/Texture/Character/Elluard/Battle/Stand/Elluard_Battle_Stand%d.png", 16); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Elluard_Battle_Run", L"../bin/Resources/Texture/Character/Elluard/Battle/Run/Elluard_Battle_Run%d.png", 32); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Elluard_Battle_Att", L"../bin/Resources/Texture/Character/Elluard/Battle/Att/Elluard_Battle_Att%d.png", 28); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Elluard_Skill1_Att", L"../bin/Resources/Texture/Character/Elluard/Battle/Skill1/Elluard_Skill1_Att%d.png", 60); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Elluard_Skill2_Att", L"../bin/Resources/Texture/Character/Elluard/Battle/Skill2/Elluard_Skill2_Att%d.png", 70); if FAILED(hr) return hr;

	//Tenzi
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tenzi_Stand", L"../bin/Resources/Texture/Character/Tenzi/Field/Stand/Tenzi_Stand%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tenzi_Run", L"../bin/Resources/Texture/Character/Tenzi/Field/Run/Tenzi_Run%d.png", 64); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tenzi_Hit", L"../bin/Resources/Texture/Character/Tenzi/Battle/Hit/Tenzi_Hit%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tenzi_Battle_Stand", L"../bin/Resources/Texture/Character/Tenzi/Battle/Stand/Tenzi_Battle_Stand%d.png", 16); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tenzi_Battle_Run", L"../bin/Resources/Texture/Character/Tenzi/Battle/Run/Tenzi_Battle_Run%d.png", 32); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tenzi_Battle_Att", L"../bin/Resources/Texture/Character/Tenzi/Battle/Att/Tenzi_Battle_Att%d.png", 36); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tenzi_Skill1_Att", L"../bin/Resources/Texture/Character/Tenzi/Battle/Skill1/Tenzi_Skill1_Att%d.png", 28); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tenzi_Skill2_Att", L"../bin/Resources/Texture/Character/Tenzi/Battle/Skill2/Tenzi_Skill2_Att%d.png", 48); if FAILED(hr) return hr;

	//Monster - WildBoar
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"WildBoar_Stand", L"../bin/Resources/Texture/Monster/WildBoar/Stand/Boar_Stand%d.png", 44); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"WildBoar_Move", L"../bin/Resources/Texture/Monster/WildBoar/Move/Boar_Move%d.png", 24); if FAILED(hr)	return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"WildBoar_Att", L"../bin/Resources/Texture/Monster/WildBoar/Att/Boar_Att%d.png", 8); if FAILED(hr)		return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"WildBoar_AttMove", L"../bin/Resources/Texture/Monster/WildBoar/AttMove/Boar_AttMove%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"WildBoar_Hit", L"../bin/Resources/Texture/Monster/WildBoar/Hit/Boar_Hit%d.png", 28); if FAILED(hr)	return hr;
	
	//Monster - Hedgehog
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Hedgehog_Stand", L"../bin/Resources/Texture/Monster/Hedgehog/Stand/Hedgehog_Stand%d.png", 44); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Hedgehog_Move", L"../bin/Resources/Texture/Monster/Hedgehog/Move/Hedgehog_Move%d.png", 32); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Hedgehog_Att", L"../bin/Resources/Texture/Monster/Hedgehog/Att/Hedgehog_Att%d.png", 20); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Hedgehog_AttMove", L"../bin/Resources/Texture/Monster/Hedgehog/AttMove/Hedgehog_AttMove%d.png", 20); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Hedgehog_Hit", L"../bin/Resources/Texture/Monster/Hedgehog/Hit/Hedgehog_Hit%d.png", 28); if FAILED(hr) return hr;

	//Monster - Chimera
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Chimera_Stand", L"../bin/Resources/Texture/Monster/Chimera/Stand/Chimera_Stand%d.png", 24); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Chimera_Move", L"../bin/Resources/Texture/Monster/Chimera/Move/Chimera_Move%d.png", 24); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Chimera_Att", L"../bin/Resources/Texture/Monster/Chimera/Att/Chimera_Att%d.png", 24); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Chimera_Hit", L"../bin/Resources/Texture/Monster/Chimera/Hit/Chimera_Hit%d.png", 8); if FAILED(hr) return hr;

	//Monster - PoisonSpider
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"PoisonSpider_Stand", L"../bin/Resources/Texture/Monster/PoisonSpider/Stand/PoisonSpider_Stand%d.png", 36); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"PoisonSpider_Move", L"../bin/Resources/Texture/Monster/PoisonSpider/Move/PoisonSpider_Move%d.png", 24); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"PoisonSpider_Att", L"../bin/Resources/Texture/Monster/PoisonSpider/Att/PoisonSpider_Att%d.png", 52); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"PoisonSpider_Hit", L"../bin/Resources/Texture/Monster/PoisonSpider/Hit/PoisonSpider_Hit%d.png", 24); if FAILED(hr) return hr;

	//Monster - PoisonJelly
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"PoisonJelly_Stand", L"../bin/Resources/Texture/Monster/PoisonJelly/Stand/PoisonJelly_Stand%d.png", 16); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"PoisonJelly_Att", L"../bin/Resources/Texture/Monster/PoisonJelly/Att/PoisonJelly_Att%d.png", 20); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"PoisonJelly_Hit", L"../bin/Resources/Texture/Monster/PoisonJelly/Hit/PoisonJelly_Hit%d.png", 4); if FAILED(hr) return hr;

	//Monster - Skeleton
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Skeleton_Stand", L"../bin/Resources/Texture/Monster/Skeleton/Stand/Skeleton_Stand%d.png", 16); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Skeleton_Move", L"../bin/Resources/Texture/Monster/Skeleton/Move/Skeleton_Move%d.png", 28); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Skeleton_Att", L"../bin/Resources/Texture/Monster/Skeleton/Att/Skeleton_Att%d.png", 16); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Skeleton_Hit", L"../bin/Resources/Texture/Monster/Skeleton/Hit/Skeleton_Hit%d.png", 4); if FAILED(hr) return hr;

	//Monster - Akenaton
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Akhenaton_Stand", L"../bin/Resources/Texture/Monster/Akhenaton/Stand/Akhenaton_Stand%d.png", 16); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Akhenaton_Att", L"../bin/Resources/Texture/Monster/Akhenaton/Att/Akhenaton_Att%d.png", 4); if FAILED(hr) return hr;

	//Effect
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Damage_Effect", L"../bin/Resources/Texture/Effect/Particle/Particle%d.png", 14); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Explosion_Effect", L"../bin/Resources/Texture/Effect/Explosion/Explosion%d.png", 24); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Guard_Effect", L"../bin/Resources/Texture/BattleUI/BattleIng/Text/Guard%d.png", 7); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Red_Particle_Effect", L"../bin/Resources/Texture/Effect/RedParticle/RedParticle%d.png", 40); if FAILED(hr) return hr; 
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Bling_Effect", L"../bin/Resources/Texture/Effect/Bling/Bling%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Skill_Charge", L"../bin/Resources/Texture/Effect/Charge/Charge%d.png", 1); if FAILED(hr) return hr;

	//Magic
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"FireBall", L"../bin/Resources/Texture/Magic/FireBall/FireBall%d.png", 20); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"FireRain", L"../bin/Resources/Texture/Magic/FireShower/FireShower%d.png", 8); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Meteo", L"../bin/Resources/Texture/Magic/Meteo/Meteo%d.png", 16); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Dark", L"../bin/Resources/Texture/Magic/Dark/%d.png", 7); if FAILED(hr)	return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Nova", L"../bin/Resources/Texture/Magic/Nova/%d.png", 4); if FAILED(hr)	return hr;

	// etc
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Water_Nomal", L"../bin/Resources/Texture/etc/Water/water%d.png", 32); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_DYNAMIC, TEXTURE_TYPE_CUBE, L"Wall_Nomal", L"../bin/Resources/Texture/etc/DDS/Wall%d.dds", 4); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_DYNAMIC, TEXTURE_TYPE_CUBE, L"Treasurechest_Nomal", L"../bin/Resources/Texture/etc/Treasurechest/Treasurechest%d.dds", 2); if FAILED(hr) return hr;

	//NPC
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"NPC1_STAND", L"../bin/Resources/Texture/NPC/NPC1/NPC1_Stand%d.png", 4); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"NPC2_Run", L"../bin/Resources/Texture/NPC/NPC2/NPC2_Run%d.png", 16); if FAILED(hr) return hr;
	hr = pResourceManager->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"NPC2_STAND", L"../bin/Resources/Texture/NPC/NPC2/NPC2_Stand%d.png", 4); if FAILED(hr) return hr;
	return S_OK;
}
