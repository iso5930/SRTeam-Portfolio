#include "stdafx.h"
#include "Character_Elluard.h"
#include "Transform.h"
#include "Equip.h"
#include "Inventory.h"
#include "AbilityGroup.h"
#include "Skill.h"
#include "Export_Function.h"
#include "Texture.h"
#include "Stage.h"
#include "TerrainCollision.h"
#include "Sprite.h"
#include "MouseCollision.h"
#include "Movement.h"
#include "OBBCollision.h"
#include "StaticCamera.h"
#include "Item.h"
#include "Effect.h"
#include "..\Engine\Utility\src\MathManager.h"

CCharacter_Elluard::CCharacter_Elluard(eObjectType _eObjectType)
:CCharacter(_eObjectType)
{

}

CCharacter_Elluard::~CCharacter_Elluard(void)
{
	Release();
}

CCharacter_Elluard* CCharacter_Elluard::Create(eObjectType _eObjectType)
{
	CCharacter_Elluard* pCharacter = new CCharacter_Elluard(_eObjectType);

	if(FAILED(pCharacter->Initialize()))
	{
		SAFE_DELETE(pCharacter);
	}

	return pCharacter;
}

HRESULT CCharacter_Elluard::Initialize(void)
{
	HRESULT hr = AddComponent();

	if(FAILED(hr))
	{
		return hr;
	}

	m_eCharacterID = CHARACTER_ELLUARD;

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

	m_tCharacterState.iSTR = 18;
	m_tCharacterState.iVIT = 16;
	m_tCharacterState.iINT = 15;
	m_tCharacterState.iAGI = 8;
	m_tCharacterState.iLUK = 5;

	m_tCharacterState.iATK = 40;
	m_tCharacterState.iDEF = 34;
	m_tCharacterState.iMAG = 79;
	m_tCharacterState.iSPD = 39;
	m_tCharacterState.iCRI = 49;

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

	ENGINE::CAbility* pAbility = ENGINE::CSkill::Create(OBJECT_TYPE_STATIC, L"라이어트 웨이브", ABILITY_ISP, 45, ABILITY_ESP, 25);
	m_pAbilityGroup->AddAbility(pAbility);

	pAbility = ENGINE::CSkill::Create(OBJECT_TYPE_STATIC, L"옥시피틀 버스트", ABILITY_ISP, 100, ABILITY_ESP, 100, ABILITY_PSP, 100);
	//pAbility->SetField(true);
	m_pAbilityGroup->AddAbility(pAbility);

	m_eState = Character_Stand;

	m_ePrevState = m_eState;

	return S_OK;
}

void CCharacter_Elluard::Release(void)
{

}

int CCharacter_Elluard::Update(void)
{
	CCharacter::Update();

	return 0;
}

HRESULT CCharacter_Elluard::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Rectangle_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));
	
	//이미지 스프라이트 추가.
	
	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Elluard_Stand");
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Elluard_Stand", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Elluard_Run");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Elluard_Run", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Elluard_Hit");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Elluard_Hit", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Elluard_Battle_Stand");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Elluard_Battle_Stand", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Elluard_Battle_Run");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Elluard_Battle_Run", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Elluard_Battle_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Elluard_Battle_Att", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Elluard_Skill1_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Elluard_Skill1_Att", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Elluard_Skill2_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Elluard_Skill2_Att", pComponent));

	//이미지 스프라이트 추가.

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

void CCharacter_Elluard::SetState(void)
{
	if(m_eState == m_ePrevState)
	{
		return;
	}

	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	switch(m_eState)
	{
	case Character_Stand:
		iter = m_ComponentMap.find(L"Elluard_Stand");
		break;

	case Character_Run:
		iter = m_ComponentMap.find(L"Elluard_Run");
		break;
	}

	if(iter != m_ComponentMap.end())
	{
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);
	}
	m_ePrevState = m_eState;
}

void CCharacter_Elluard::BattleState(void)
{
	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	if(m_eBattleMessage == m_ePrevBattleMessage)
	{
		return;
	}

	switch(m_eBattleMessage)
	{
	case BATTLE_MESSAGE_MOVE:
		iter = m_ComponentMap.find(L"Elluard_Battle_Run");
		ENGINE::GetSoundManager()->PlayElluardSound(L"Run3.wav");
		break;

	case BATTLE_MESSAGE_END: //스탠드
		iter = m_ComponentMap.find(L"Elluard_Battle_Stand");
		break;

	case BATTLE_MESSAGE_HIT:
		iter = m_ComponentMap.find(L"Elluard_Hit");
		ENGINE::GetSoundManager()->PlayElluardSound(L"Char_Damage.wav");
		break;

	case BATTLE_MESSAGE_ATTACK:
		iter = m_ComponentMap.find(L"Elluard_Battle_Att");
		ENGINE::GetSoundManager()->PlayElluardSound(L"Ellu_Atk.wav");
		break;

	case BATTLE_MESSAGE_SKILL1:
		iter = m_ComponentMap.find(L"Elluard_Skill1_Att");
		ENGINE::GetSoundManager()->PlayElluardSound(L"Ellu_Skill.wav");
		break;

	case BATTLE_MESSAGE_SKILL2:
		iter = m_ComponentMap.find(L"Elluard_Skill2_Att");
		ENGINE::GetSoundManager()->PlayElluardSound(L"Ellu_Skill.wav");
		break;
	}

	if(iter != m_ComponentMap.end())
	{
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);
	}

	m_ePrevBattleMessage = m_eBattleMessage;
}

void CCharacter_Elluard::SetBattleAngle(void)
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
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 7, float(iIndex * 7) - 1, 10.f));
			break;

		case BATTLE_MESSAGE_SKILL1:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 15, float(iIndex * 15) - 1, 10.f));
			break;

		case BATTLE_MESSAGE_SKILL2:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 17, float(iIndex * 17) - 1, 10.f));
			break;
		}

		m_iPrevIndex = iIndex;
	}
}

void CCharacter_Elluard::SetCamera(void)
{
	ENGINE::CGameObject* pObj = ENGINE::GetManagement()->GetGameObject(L"Camera");

	static_cast<CStaticCamera*>(pObj)->SetTargetInfo(m_pInfo);
}

int CCharacter_Elluard::BattleUpdate(void)
{
	
	if(m_eBattleMessage == BATTLE_MESSAGE_SKILL1)
	{
		int iCur = (int)m_pSpriteFrame->GetCurFrame();

		int iFrmae = iCur % 15;

		if(m_bSkillCharge == false && iFrmae > 6)
		{
			if(m_bSkillCharge != true)
			{
				m_pSpriteFrame->SetCurFrame(iCur);
			}
		}
		if(iFrmae == 3 && m_iSkillCount == 0)
		{
			++m_iSkillCount;
			//1차 히트박스 발생.. 타겟팅
			ENGINE::CGameObject* pObj = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster, 0.5f, 0.5f, 0.5f, m_tCharacterState.iATK - 20, true, true);
			ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pObj);
		}
		else if(iFrmae == 6 && m_iSkillCount == 1)
		{
			++m_iSkillCount;
			//하나는 커지는 이펙트...
			//점점 커지는 이펙트..
			//이펙트 발생.
			ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, this, EFFECT_CHARGE, m_pInfo->m_vPos.x, m_pInfo->m_vPos.y, m_pInfo->m_vPos.z);
			ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
			ENGINE::GetSoundManager()->PlayWeaponSound(L"Whip_Skill2.wav");

			m_bSkillCharge = false;
		}
		else if(iFrmae == 10 && m_iSkillCount == 2)
		{
			++m_iSkillCount;
			//2차 히트박스 발생. 논 타겟팅 제자리에서 전방에 인원 전체에게 입력...
			//아니다 그냥 개냬들한테 전부 달아줄까? 그게 낫겟네..
			vector<ENGINE::CMonster*>* vecMonster = m_pTargetMonster->GetOwner()->GetMonsterGroup();

			for(size_t i = 0; i < vecMonster->size(); ++i)
			{
				D3DXVECTOR3 vDist = ((*vecMonster)[i])->GetInfo()->m_vPos - m_pInfo->m_vPos;

				vDist.y = 0.f;

				float fLength = D3DXVec3Length(&vDist);

				if(fLength < 3.f)
				{
					ENGINE::CGameObject* pObj = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, ((*vecMonster)[i]), 0.5f, 0.5f, 0.5f, m_tCharacterState.iATK, true, true);
					ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pObj);
				}
			}
		}
		if(m_pSpriteFrame->GetFrameEnd() == true)
		{
			m_eBattleMessage = BATTLE_MESSAGE_END;
		}
	}
	else if(m_eBattleMessage == BATTLE_MESSAGE_SKILL2)
	{
		//7번 20번
		int iCur = (int)m_pSpriteFrame->GetCurFrame();

		int iFrame = iCur % 17;
	
		if(iFrame < 4)
		{
			m_pInfo->m_vPos.y += 1.f * ENGINE::GetTimeDelta();
			//여기서 어택을 하고...

			//12번에서 착지 모션...
		}
		else if(iFrame == 5 && m_iSkillCount == 0)
		{
			++m_iSkillCount;
				ENGINE::GetSoundManager()->PlayWeaponSound(L"Whip_Skill.wav");

			D3DXVECTOR3 vPos = m_pTargetMonster->GetInfo()->m_vPos;

			m_pInfo->m_vPos = vPos;

			m_pInfo->m_vPos.y += 0.5f;

		}
		else if(iFrame == 6 && m_iSkillCount == 1)
		{
			++m_iSkillCount;

			//공격모션 실행..
			ENGINE::CGameObject* pObj = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster, 0.5f, 1.f, 0.5f, 15, false, true);
			ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pObj);
		}
		
		if(m_pSpriteFrame->GetFrameEnd() == true)
		{
			m_eBattleMessage = BATTLE_MESSAGE_END;
		}
	}

	CCharacter::BattleUpdate();

	return 0;
}