#include "stdafx.h"
#include "Character_Tenzi.h"
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

CCharacter_Tenzi::CCharacter_Tenzi(eObjectType _eObjectType)
:CCharacter(_eObjectType)
{
	
}

CCharacter_Tenzi::~CCharacter_Tenzi(void)
{

	Release();
}

CCharacter_Tenzi* CCharacter_Tenzi::Create(eObjectType _eObjectType)
{
	CCharacter_Tenzi* pCharacter = new CCharacter_Tenzi(_eObjectType);

	if(FAILED(pCharacter->Initialize()))
	{
		SAFE_DELETE(pCharacter);
	}

	return pCharacter;
}

HRESULT CCharacter_Tenzi::Initialize(void)
{
	HRESULT hr = AddComponent();

	if(FAILED(hr))
	{
		return hr;
	}

	m_eCharacterID = CHARACTER_TENZI;

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

	m_tCharacterState.iATK = 45;
	m_tCharacterState.iDEF = 34;
	m_tCharacterState.iMAG = 79;
	m_tCharacterState.iSPD = 35;
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

	m_eState = Character_Stand;

	ENGINE::CAbility* pAbility = ENGINE::CSkill::Create(OBJECT_TYPE_STATIC, L"도립축", ABILITY_ISP, 45, ABILITY_ESP, 25);
	m_pAbilityGroup->AddAbility(pAbility);

	pAbility = ENGINE::CSkill::Create(OBJECT_TYPE_STATIC, L"역풍축 ", ABILITY_ISP, 100, ABILITY_ESP, 100, ABILITY_PSP, 100);
	//pAbility->SetField(true);
	m_pAbilityGroup->AddAbility(pAbility);

	m_ePrevState = m_eState;

	

	return S_OK;
}

void CCharacter_Tenzi::Release(void)
{

}

int CCharacter_Tenzi::Update(void)
{
	CCharacter::Update();

	return 0;
}

HRESULT CCharacter_Tenzi::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Rectangle_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));

	//이미지 스프라이트 추가.

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Tenzi_Stand");
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Tenzi_Stand", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Tenzi_Run");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Tenzi_Run", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Tenzi_Hit");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Tenzi_Hit", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Tenzi_Battle_Stand");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Tenzi_Battle_Stand", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Tenzi_Battle_Run");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Tenzi_Battle_Run", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Tenzi_Battle_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Tenzi_Battle_Att", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Tenzi_Skill1_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Tenzi_Skill1_Att", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Tenzi_Skill2_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Tenzi_Skill2_Att", pComponent));

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

void CCharacter_Tenzi::SetState(void)
{
	if(m_eState == m_ePrevState)
	{
		return;
	}

	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	switch(m_eState)
	{
	case Character_Stand:
		iter = m_ComponentMap.find(L"Tenzi_Stand");
		break;

	case Character_Run:
		iter = m_ComponentMap.find(L"Tenzi_Run");
		break;
	}

	if(iter != m_ComponentMap.end())
	{
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);
	}
	m_ePrevState = m_eState;
}

void CCharacter_Tenzi::BattleState(void)
{
	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	if(m_eBattleMessage == m_ePrevBattleMessage)
	{
		return;
	}

	switch(m_eBattleMessage)
	{
	case BATTLE_MESSAGE_MOVE:
		iter = m_ComponentMap.find(L"Tenzi_Battle_Run");
		ENGINE::GetSoundManager()->PlayTenziSound(L"Run3.wav");
		break;

	case BATTLE_MESSAGE_END: //스탠드
		iter = m_ComponentMap.find(L"Tenzi_Battle_Stand");
		break;

	case BATTLE_MESSAGE_HIT:
		iter = m_ComponentMap.find(L"Tenzi_Hit");
		ENGINE::GetSoundManager()->PlayTenziSound(L"Char_Damage.wav");
		break;

	case BATTLE_MESSAGE_ATTACK:
		iter = m_ComponentMap.find(L"Tenzi_Battle_Att");
		ENGINE::GetSoundManager()->PlayTenziSound(L"Tenzi_Atk.wav");
		break;

	case BATTLE_MESSAGE_SKILL1:
		iter = m_ComponentMap.find(L"Tenzi_Skill1_Att");
		ENGINE::GetSoundManager()->PlayTenziSound(L"Ellu_Skill.wav");
		break;

	case BATTLE_MESSAGE_SKILL2:
		iter = m_ComponentMap.find(L"Tenzi_Skill2_Att");
		ENGINE::GetSoundManager()->PlayTenziSound(L"Ellu_Skill.wav");
		break;
	}

	if(iter != m_ComponentMap.end())
	{
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);
	}

	m_ePrevBattleMessage = m_eBattleMessage;
}

void CCharacter_Tenzi::SetBattleAngle(void)
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
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 9, float(iIndex * 9) - 1, 10.f));
			break;

		case BATTLE_MESSAGE_SKILL1:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 7, float(iIndex * 7) - 1, 7.f));
			break;

		case BATTLE_MESSAGE_SKILL2:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 12, float(iIndex * 12) - 1, 7.f));
			break;
		}

		m_iPrevIndex = iIndex;
	}
}

void CCharacter_Tenzi::SetCamera(void)
{
	ENGINE::CGameObject* pObj = ENGINE::GetManagement()->GetGameObject(L"Camera");

	static_cast<CStaticCamera*>(pObj)->SetTargetInfo(m_pInfo);
}

int CCharacter_Tenzi::BattleUpdate(void)
{	
	if(m_eBattleMessage == BATTLE_MESSAGE_SKILL1)
	{
		int iCur = (int)m_pSpriteFrame->GetCurFrame();

		int iFrame = iCur % 7;

		if(iFrame == 5 && m_iSkillCount == 0)
		{
			++m_iSkillCount;
			
			ENGINE::CGameObject* pObj = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster, 0.5f, 0.5f, 0.5f, m_tCharacterState.iATK - 10, true, true);
			ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pObj);
		}
		if(m_pSpriteFrame->GetFrameEnd() == true)
		{
			m_eBattleMessage = BATTLE_MESSAGE_END;
		}
		//스킬 1 실행
	}
	else if(m_eBattleMessage == BATTLE_MESSAGE_SKILL2)
	{
		int iCur = (int)m_pSpriteFrame->GetCurFrame();

		int iFrame = iCur % 12;

		if(iFrame < 8)
		{
			D3DXVECTOR3 vDir = m_vDestPos - m_pInfo->m_vPos;
			
			float fLength = D3DXVec3Length(&vDir);

			if(fLength >= 0.2f)
			{
				D3DXVec3Normalize(&vDir, &vDir);
				m_pInfo->m_vPos += vDir * 1.f * ENGINE::GetTimeDelta();
			}
		}
		if(iFrame == 9 && m_iSkillCount == 0)
		{
			++m_iSkillCount;
			
			ENGINE::CGameObject* pObj = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster, 0.5f, 0.5f, 0.5f, m_tCharacterState.iATK, true, true);
			ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pObj);
		}

		if(m_pSpriteFrame->GetFrameEnd() == true)
		{
			m_eBattleMessage = BATTLE_MESSAGE_END;
		}
		//스킬 2 실행
	}

	CCharacter::BattleUpdate();

	return 0;
}