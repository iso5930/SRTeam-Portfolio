#include "stdafx.h"
#include "Character_Maria.h"
#include "Transform.h"
#include "Equip.h"
#include "Inventory.h"
#include "Character.h"
#include "AbilityGroup.h"
#include "Skill.h"
#include "Export_Utility.h"
#include "TerrainCollision.h"
#include "Export_System.h"
#include "Texture.h"
#include "Sprite.h"
#include "VIBuffer.h"
#include "OBBCollision.h"
#include "Export_Resources.h"
#include "MouseCollision.h"
#include "Movement.h"
#include "StaticCamera.h"
#include "Item.h"
#include "Effect.h"

CCharacter_Maria::CCharacter_Maria(eObjectType _eObjectType)
:CCharacter(_eObjectType)
{

}

CCharacter_Maria::~CCharacter_Maria(void)
{
	Release();
}

CCharacter_Maria* CCharacter_Maria::Create(eObjectType _eObjectType)
{
	CCharacter_Maria* pCharacter_Maria = new CCharacter_Maria(_eObjectType);

	if(FAILED(pCharacter_Maria->Initialize()))
	{
		SAFE_DELETE(pCharacter_Maria);
	}

	return pCharacter_Maria;
}

HRESULT CCharacter_Maria::Initialize(void)
{
	HRESULT hr = AddComponent();

	if(FAILED(hr))
	{
		return hr;
	}

	m_eCharacterID = CHARACTER_MARIA;

	m_pEquip = ENGINE::CEquip::Create(OBJECT_TYPE_STATIC, m_eCharacterID);
	if(m_pEquip == NULL)
		return E_FAIL;

	m_pInventory = ENGINE::CInventory::Create(OBJECT_TYPE_STATIC);
	if(m_pEquip == NULL)
		return E_FAIL;

	m_pAbilityGroup = ENGINE::CAbilityGroup::Create(OBJECT_TYPE_STATIC, m_eCharacterID);
	if(m_pAbilityGroup == NULL)
		return E_FAIL;

	m_tCharacterState.iLevel = 1;
	m_tCharacterState.iExp = 0;
	m_tCharacterState.iNextExp = 100;
	m_tCharacterState.iBarrierPoint = 36;
	m_tCharacterState.iMaxBarrierPoint = 36;
	m_tCharacterState.iHitPoint = 30;
	m_tCharacterState.iMaxHitPoint = 30;
	m_tCharacterState.iRageGauge = 0;
	m_tCharacterState.iMaxRageGauge = 100;

	m_tCharacterState.iSTR = 50;
	m_tCharacterState.iVIT = 90;
	m_tCharacterState.iINT = 100;
	m_tCharacterState.iAGI = 55;
	m_tCharacterState.iLUK = 60;

	m_tCharacterState.iATK = 100;
	m_tCharacterState.iDEF = 180;
	m_tCharacterState.iMAG = 190;
	m_tCharacterState.iSPD = 50;
	m_tCharacterState.iCRI = 89;

	m_tCharacterState.iAbility1 = 100;
	m_tCharacterState.iAbility2 = 100;
	m_tCharacterState.iAbility3 = 100;
	m_tCharacterState.iMaxAbility1 = 100;
	m_tCharacterState.iMaxAbility2 = 100;
	m_tCharacterState.iMaxAbility3 = 100;

	m_eAbilityID = ABILITYID_SKILL;

	m_vecAbilityType.push_back(ABILITY_ISP);
	m_vecAbilityType.push_back(ABILITY_ESP);
	m_vecAbilityType.push_back(ABILITY_PSP);

	m_tTempState = m_tCharacterState;

	ENGINE::CAbility* pAbility = ENGINE::CSkill::Create(OBJECT_TYPE_STATIC, L"승박", ABILITY_ISP, 45, ABILITY_ESP, 25);
	m_pAbilityGroup->AddAbility(pAbility);

	pAbility = ENGINE::CSkill::Create(OBJECT_TYPE_STATIC, L"홍약저", ABILITY_ISP, 100, ABILITY_ESP, 100, ABILITY_PSP, 100);
	//pAbility->SetField(true);
	m_pAbilityGroup->AddAbility(pAbility);

	m_eState = Character_Stand;

	m_ePrevState = m_eState;

	//마리아 스킬 6 / 12 / 30

	return S_OK;
}

int CCharacter_Maria::Update(void)
{
	CCharacter::Update();

	return 0;
}

void CCharacter_Maria::Release(void)
{
	
}

HRESULT CCharacter_Maria::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Rectangle_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));

	//=========== 마리아 텍스쳐 추가

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Maria_Stand");
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Maria_Stand", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Maria_Run");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Maria_Run", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Maria_Hit");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Maria_Hit", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Maria_Battle_Stand");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Maria_Battle_Stand", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Maria_Battle_Run");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Maria_Battle_Run", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Maria_Battle_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Maria_Battle_Att", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Maria_Skill1_Run");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Maria_Skill1_Run", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Maria_Skill1_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Maria_Skill1_Att", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Maria_Skill2_Run");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Maria_Skill2_Run", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Maria_Skill2_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Maria_Skill2_Att", pComponent));

	//=========== 마리아 텍스쳐 추가

	m_pMouseCollision = ENGINE::CMouseCollision::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"MouseCollision", m_pMouseCollision));

	pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 0.f, 10.f));
	m_pSpriteFrame = static_cast<ENGINE::CSprite*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));

	pComponent = ENGINE::CMovement::Create(this, m_pInfo, &m_vDestPos, 5.f);
	m_pMovement = static_cast<ENGINE::CMovement*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Movement", pComponent));

	m_pTerrainCollision = ENGINE::CTerrainCollision::Create(this, m_pInfo, new ENGINE::CColStop(m_pInfo, m_pMovement));
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"TerrainCollision", m_pTerrainCollision));

	m_pOBBCollision = ENGINE::COBBCollision::Create(this, m_pInfo, m_pMovement, 0.25f, 0.4f, 0.25f, NULL, true);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollision));

	return S_OK;
}

void CCharacter_Maria::SetState(void)
{
	if(m_eState == m_ePrevState)
	{
		return;
	}

	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	switch(m_eState)
	{
	case Character_Stand:
		iter = m_ComponentMap.find(L"Maria_Stand");
		break;

	case Character_Run:
		iter = m_ComponentMap.find(L"Maria_Run");
		break;

	case Character_Att:
		iter = m_ComponentMap.find(L"Maria_Att");
		break;
	}

	if(iter != m_ComponentMap.end())
	{
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);
	}

	m_ePrevState = m_eState;
}

void CCharacter_Maria::BattleState(void)
{
	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	if(m_eBattleMessage == m_ePrevBattleMessage)
	{
		return;
	}

	switch(m_eBattleMessage)
	{
	case BATTLE_MESSAGE_MOVE:
		iter = m_ComponentMap.find(L"Maria_Battle_Run");
		ENGINE::GetSoundManager()->PlayMariaSound(L"Run1.wav");
		break;

	case BATTLE_MESSAGE_END: //스탠드
		iter = m_ComponentMap.find(L"Maria_Battle_Stand");
		break;

	case BATTLE_MESSAGE_HIT:
		iter = m_ComponentMap.find(L"Maria_Hit");
		ENGINE::GetSoundManager()->PlayMariaSound(L"Char_Damage.wav");
		break;

	case BATTLE_MESSAGE_ATTACK:
		iter = m_ComponentMap.find(L"Maria_Battle_Att");
		ENGINE::GetSoundManager()->PlayMariaSound(L"Maria_Atk.wav");
		break;

	case BATTLE_MESSAGE_SKILL1_RUN:
		iter = m_ComponentMap.find(L"Maria_Skill1_Run");
		ENGINE::GetSoundManager()->PlayMariaSound(L"Run1.wav");
		break;

	case BATTLE_MESSAGE_SKILL1:
		iter = m_ComponentMap.find(L"Maria_Skill1_Att");
		ENGINE::GetSoundManager()->PlayMariaSound(L"Maria_Skill1.wav");
		break;

	case BATTLE_MESSAGE_SKILL2:	
		iter = m_ComponentMap.find(L"Maria_Skill2_Att");
		ENGINE::GetSoundManager()->PlayMariaSound(L"Maria_Skill2.wav");
		break;

	case BATTLE_MESSAGE_SKILL2_RUN:
		iter = m_ComponentMap.find(L"Maria_Skill2_Run");
		ENGINE::GetSoundManager()->PlayMariaSound(L"Run1.wav");
		break;
	}

	if(iter != m_ComponentMap.end())
	{
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);
	}

	m_ePrevBattleMessage = m_eBattleMessage;
}

void CCharacter_Maria::SetBattleAngle(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::GetManagement()->GetComponent(L"Camera", L"Transform");
	float fCameraAngle = ((ENGINE::CTransform*)pComponent)->m_pAngle[ANGLE_TYPE_Y];

	D3DXVECTOR3 vDest = m_vDestPos - m_pInfo->m_vPos;

	vDest.y = 0.f;

	D3DXMATRIX matRot;

	D3DXMatrixRotationY(&matRot, fCameraAngle);

	D3DXVECTOR3 vLook(1.f, 0.f, 0.f);

	D3DXVec3TransformNormal(&vLook, &vLook, &matRot);

	D3DXVec3Normalize(&vDest, &vDest);

	float fAngle = D3DXVec3Dot(&vLook, &vDest);

	fAngle = acosf(fAngle);

	D3DXVECTOR3 vDestPos = m_vDestPos;
	D3DXVECTOR3 vCharacter = m_pInfo->m_vPos;

	D3DXMatrixRotationY(&matRot, -fCameraAngle); //매번 변할수 있는 값..

	D3DXVec3TransformCoord(&vDestPos, &vDestPos, &matRot);
	D3DXVec3TransformCoord(&vCharacter, &vCharacter, &matRot);

	if(vCharacter.z < vDestPos.z)
	{
		fAngle = 2 * D3DX_PI - fAngle;
	}

	float fSource = 0.f;
	int iIndex = 0;
	fAngle = D3DXToDegree(fAngle);

	for(int i = 1; i < 5; ++i)
	{
		fSource = 90.f * i;

		if(fSource >= fAngle)
		{
			iIndex = i;
			break;
		}
	}

	m_fAngle = fAngle + 90.f;

	if(m_iPrevIndex != iIndex || m_eBattleMessage != m_ePrevBattleMessage)
	{
		switch(m_eBattleMessage)
		{
		case BATTLE_MESSAGE_MOVE:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 8, float(iIndex * 8) - 1, 10.f));
			break;

		case BATTLE_MESSAGE_END:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 4, float(iIndex * 4) - 1, 10.f));
			break;

		case BATTLE_MESSAGE_HIT:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 2, float(iIndex * 2) -1, 10.f));
			break;

		case BATTLE_MESSAGE_ATTACK:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 6, float(iIndex * 6) - 1, 10.f));
			break;

		case BATTLE_MESSAGE_SKILL1_RUN:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 4, float(iIndex * 4) - 1, 10.f));
			break;

		case BATTLE_MESSAGE_SKILL1:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 32, float(iIndex * 32) - 1, 20.f));
			break;

		case BATTLE_MESSAGE_SKILL2_RUN:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 4, float(iIndex * 4) - 1, 10.f));
			break;

		case BATTLE_MESSAGE_SKILL2:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 32, float(iIndex * 32) - 1, 20.f));
			break;
		}

		m_iPrevIndex = iIndex;
	}
}

void CCharacter_Maria::SetCamera(void)
{
	ENGINE::CGameObject* pObj = ENGINE::GetManagement()->GetGameObject(L"Camera");

	static_cast<CStaticCamera*>(pObj)->SetTargetInfo(m_pInfo);
}

int CCharacter_Maria::BattleUpdate(void)
{
	CCharacter::BattleUpdate();

	if(m_bSkillRun)
	{
		if(m_pMovement->GetMove() == false)
		{
			if(m_eBattleMessage == BATTLE_MESSAGE_SKILL1_RUN)
			{
				m_eBattleMessage = BATTLE_MESSAGE_SKILL1;
			}
			else if(m_eBattleMessage == BATTLE_MESSAGE_SKILL2_RUN)
			{
				m_eBattleMessage = BATTLE_MESSAGE_SKILL2;
			}

			m_bSkillRun = false;
		}
	}

	if(m_eBattleMessage == BATTLE_MESSAGE_SKILL1)
	{
		int iCur = (int)m_pSpriteFrame->GetCurFrame();//현재 프레임
		//6번 프레임, 28번 프레임

		int iFrame = iCur % 32;

		if(iFrame == 6 && m_iSkillCount == 0)
		{
			++m_iSkillCount;
			//ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, this, EFFECT_EXPLOSION, m_pInfo->m_vPos.x, m_pInfo->m_vPos.y, m_pInfo->m_vPos.z);
			//ENGINE::GetManagement()->AddGameObject(L"Effect", 2, pObj);
			ENGINE::CGameObject* pObj = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster, 0.5f, 0.5f, 0.5f, m_tCharacterState.iATK  / 2, false, true);
			ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pObj);
		}
		else if(iFrame == 28 && m_iSkillCount == 1)
		{
			++m_iSkillCount;
			//ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, this, EFFECT_DAMAGE, m_pInfo->m_vPos.x, m_pInfo->m_vPos.y, m_pInfo->m_vPos.z);
			//ENGINE::GetManagement()->AddGameObject(L"Effect", 2, pObj);
			ENGINE::CGameObject* pObj = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster, 0.5f, 0.5f, 0.5f, (m_tCharacterState.iATK  / 2) + 10, true, true);
			ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pObj);
		}
		
		if(m_pSpriteFrame->GetFrameEnd() == true)
		{
			m_eBattleMessage = BATTLE_MESSAGE_END;
		}
	}
	else if(m_eBattleMessage == BATTLE_MESSAGE_SKILL2)
	{	
		//6번 12번 30번에서 히트박스 생성

		int iCur = (int)m_pSpriteFrame->GetCurFrame();

		int iFrame = iCur % 32;

		if(iFrame == 6 && m_iSkillCount == 0)
		{
			ENGINE::CGameObject* pObj = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster, 0.5f, 0.5f, 0.5f, 30, false, true);
			ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pObj);
			++m_iSkillCount;
		}
		else if(iFrame == 12 && m_iSkillCount == 1)
		{
			ENGINE::CGameObject* pObj = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster, 0.5f, 0.5f, 0.5f, 40, false, true);
			ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pObj);
			++m_iSkillCount;
		}
		else if(iFrame == 30 && m_iSkillCount == 2)
		{
			ENGINE::CGameObject* pObj = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster, 0.5f, 0.5f, 0.5f, 50, true, true);
			ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pObj);
			++m_iSkillCount;
		}

		if(m_pSpriteFrame->GetFrameEnd() == true)
		{
			m_eBattleMessage = BATTLE_MESSAGE_END;
		}
	}

	return 0;	
}