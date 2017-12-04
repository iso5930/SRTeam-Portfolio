#include "stdafx.h"
#include "Character_Sizz.h"
#include "Transform.h"
#include "Equip.h"
#include "Inventory.h"
#include "Character.h"
#include "AbilityGroup.h"
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
#include "Magic.h"
#include "Sizz_Magic.h"

CCharacter_Sizz::CCharacter_Sizz(eObjectType _eObjectType)
:CCharacter(_eObjectType)
{

}

CCharacter_Sizz::~CCharacter_Sizz(void)
{
	Release();
}

CCharacter_Sizz* CCharacter_Sizz::Create(eObjectType _eObjectType)
{
	CCharacter_Sizz* pCharacter_Sizz = new CCharacter_Sizz(_eObjectType);

	if(FAILED(pCharacter_Sizz->Initialize()))
	{
		SAFE_DELETE(pCharacter_Sizz);
	}

	return pCharacter_Sizz;
}

HRESULT CCharacter_Sizz::Initialize(void)
{
	HRESULT hr = AddComponent();

	if(FAILED(hr))
	{
		return hr;
	}

	m_eCharacterID = CHARACTER_SIZZ;

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

	m_tCharacterState.iATK = 35;//35;
	m_tCharacterState.iDEF = 34;
	m_tCharacterState.iMAG = 79;
	m_tCharacterState.iSPD = 72;
	m_tCharacterState.iCRI = 49;

	m_tCharacterState.iAbility1 = 100;
	m_tCharacterState.iAbility2 = 100;
	m_tCharacterState.iAbility3 = 100;
	m_tCharacterState.iMaxAbility1 = 100;
	m_tCharacterState.iMaxAbility2 = 100;
	m_tCharacterState.iMaxAbility3 = 100;

	m_eAbilityID = ABILITYID_MAGIC;

	m_vecAbilityType.push_back(ABILITY_FIRE);
	m_vecAbilityType.push_back(ABILITY_WIND);
	m_vecAbilityType.push_back(ABILITY_EARTH);

	m_tTempState = m_tCharacterState;

	ENGINE::CAbility* pAbility = ENGINE::CMagic::Create(OBJECT_TYPE_STATIC, L"파이어볼", ABILITY_FIRE, 20);
	m_pAbilityGroup->AddAbility(pAbility);

	pAbility = ENGINE::CMagic::Create(OBJECT_TYPE_STATIC, L"파이어 레인", ABILITY_FIRE, 50, ABILITY_WIND, 50);
	m_pAbilityGroup->AddAbility(pAbility);

	pAbility = ENGINE::CMagic::Create(OBJECT_TYPE_STATIC, L"메테오", ABILITY_FIRE, 100, ABILITY_WIND, 100, ABILITY_EARTH, 100);
	m_pAbilityGroup->AddAbility(pAbility);

	m_eState = Character_Stand;

	m_ePrevState = m_eState;
	
	return S_OK;
}

int CCharacter_Sizz::Update(void)
{
	CCharacter::Update();

	vector<ENGINE::CItem*>*		vecEquip = m_pEquip->GetvecEquip();

	//cout << "sizz : " << m_pInfo->m_vPos.x << " " << m_pInfo->m_vPos.y << " " << m_pInfo->m_vPos.z << endl;
	return 0;
}

void CCharacter_Sizz::Release(void)
{
	
}

HRESULT CCharacter_Sizz::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Rectangle_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Sizz_Stand");
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Sizz_Stand", pComponent));
	
	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Sizz_Run");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Sizz_Run", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Sizz_Hit");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Sizz_Hit", pComponent));
	
	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Sizz_Battle_Stand");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Sizz_Battle_Stand", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Sizz_Battle_Run");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Sizz_Battle_Run", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Sizz_Battle_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Sizz_Battle_Att", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Sizz_Battle_Magic");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Sizz_Battle_Magic", pComponent));

	m_pMouseCollision = ENGINE::CMouseCollision::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"MouseCollision", m_pMouseCollision));

	pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 0.f, 10.f));
	m_pSpriteFrame = static_cast<ENGINE::CSprite*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));

	pComponent = ENGINE::CMovement::Create(this, m_pInfo, &m_vDestPos, 5.f);
	m_pMovement = static_cast<ENGINE::CMovement*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Movement", pComponent));

	//! terrain이랑 충돌했을 때, 실행할 functor.. 자신의 행동을 결정함..
	m_pTerrainCollision = ENGINE::CTerrainCollision::Create(this, m_pInfo, new ENGINE::CColStop(m_pInfo, m_pMovement));
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"TerrainCollision", m_pTerrainCollision));

	//! 다른 OBB랑 충돌했을 때, 실행할 functor.. 상대의 행동을 결정함..
	m_pOBBCollision = ENGINE::COBBCollision::Create(this, m_pInfo, m_pMovement, 0.25f, 0.4f, 0.25f, NULL, true);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollision));

	return S_OK;
}

void CCharacter_Sizz::SetState(void)
{
	if(m_eState == m_ePrevState)
	{
		return;
	}

	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	switch(m_eState)
	{
	case Character_Stand:
		iter = m_ComponentMap.find(L"Sizz_Stand");
		break;

	case Character_Run:
		iter = m_ComponentMap.find(L"Sizz_Run");
		break;
	}

	if(iter != m_ComponentMap.end())
	{
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);
	}
	m_ePrevState = m_eState;
}

void CCharacter_Sizz::BattleState(void)
{
	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	if(m_eBattleMessage == m_ePrevBattleMessage)
	{
		return;
	}

	switch(m_eBattleMessage)
	{
	case BATTLE_MESSAGE_MOVE:
		iter = m_ComponentMap.find(L"Sizz_Battle_Run");
		ENGINE::GetSoundManager()->PlaySizzSound(L"Run0.wav");
		break;

	case BATTLE_MESSAGE_END: //스탠드
		iter = m_ComponentMap.find(L"Sizz_Battle_Stand");
		break;

	case BATTLE_MESSAGE_HIT:
		iter = m_ComponentMap.find(L"Sizz_Hit");
		ENGINE::GetSoundManager()->PlaySpiderSound(L"Char_Damage.wav");
		break;

	case BATTLE_MESSAGE_DEFENSE:
		iter = m_ComponentMap.find(L"Sizz_Battle_Stand");
		break;

	case BATTLE_MESSAGE_ATTACK:
		iter = m_ComponentMap.find(L"Sizz_Battle_Att");
		ENGINE::GetSoundManager()->PlaySizzSound(L"Sizz_Atk.wav");
		break;

	case BATTLE_MESSAGE_MAGIC:
		iter = m_ComponentMap.find(L"Sizz_Battle_Magic");
		ENGINE::GetSoundManager()->PlaySizzSound(L"Sizz_Spell.wav");
		break;
	}

	if(iter != m_ComponentMap.end())
	{
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);
	}

	m_ePrevBattleMessage = m_eBattleMessage;
}

void CCharacter_Sizz::SetBattleAngle(void)
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

		case BATTLE_MESSAGE_DEFENSE:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 4, float(iIndex * 4) - 1, 10.f));
			break;

		case BATTLE_MESSAGE_ATTACK:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 5, float(iIndex * 5) - 1, 10.f));
			break;

		case BATTLE_MESSAGE_MAGIC:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1) * 16, float(iIndex * 16) - 1, 10.f));
			break;
		}

		m_iPrevIndex = iIndex;
	}
}

void CCharacter_Sizz::SetCamera(void)
{
	ENGINE::CGameObject* pObj = ENGINE::GetManagement()->GetGameObject(L"Camera");

	static_cast<CStaticCamera*>(pObj)->SetTargetInfo(m_pInfo);
}

int CCharacter_Sizz::BattleUpdate(void)
{
	CCharacter::BattleUpdate();

	//배틀 업뎃
	//각자 내려준이유.. 플레이어마다 스킬이 달라서?
	if(m_eBattleMessage == BATTLE_MESSAGE_MAGIC)
	{
		if(m_pSpriteFrame->GetFrameEnd() == true)
		{
			ENGINE::CGameObject* pMagic = NULL;

			switch(m_iAbilityCur)
			{
			case 0:
				pMagic = CSizz_Magic::Create(OBJECT_TYPE_DYNAMIC, this, MAGIC_FIREBALL, m_pInfo->m_vPos, m_pTargetMonster->GetInfo()->m_vPos, m_tCharacterState.iATK, m_pTargetMonster);
				ENGINE::GetManagement()->AddGameObject(L"Magic", 1, pMagic);
				//파이어볼 //이게 타겟팅...
				break;

			case 1:
				//파이어 레인...

				pMagic = CSizz_Magic::Create(OBJECT_TYPE_DYNAMIC, this, MAGIC_FIRERAIN, m_pInfo->m_vPos, D3DXVECTOR3(0.f, 0.f, 0.f), m_tCharacterState.iATK - 10, NULL);
				ENGINE::GetManagement()->AddGameObject(L"Magic", 1, pMagic);

				for(int i = 0; i < 20; ++i)
				{
					float fX = float(rand() % 4);
					float fZ = float(rand() % 4);
					float fY = float(rand() % 3);
					float fCount = float(rand() % 2);

					D3DXVECTOR3 vPos;

					vPos.y = m_pInfo->m_vPos.y + fY;
					
					if(fCount == 0)
					{
						vPos.x = m_pInfo->m_vPos.x + fX;
						vPos.z = m_pInfo->m_vPos.z + fZ;
					}
					else
					{
						vPos.x = m_pInfo->m_vPos.x - fX;
						vPos.z = m_pInfo->m_vPos.z - fZ;
					}

					pMagic = CSizz_Magic::Create(OBJECT_TYPE_DYNAMIC, this, MAGIC_FIRERAIN, vPos, D3DXVECTOR3(0.f, 0.f, 0.f), 15, NULL);
					ENGINE::GetManagement()->AddGameObject(L"Magic", 1, pMagic);
				}
				break;

			case 2:
				for(int i = 0; i < 10; ++i)
				{
					float fX = float(rand() % 4);
					float fZ = float(rand() % 4);
					float fY = float(rand() % 3);
					float fCount = float(rand() % 2);

					D3DXVECTOR3 vPos;

					vPos.y = m_pInfo->m_vPos.y + fY;

					if(fCount == 0)
					{
						vPos.x = m_pInfo->m_vPos.x + fX;
						vPos.z = m_pInfo->m_vPos.z + fZ;
					}
					else
					{
						vPos.x = m_pInfo->m_vPos.x - fX;
						vPos.z = m_pInfo->m_vPos.z - fZ;
					}

					pMagic = CSizz_Magic::Create(OBJECT_TYPE_DYNAMIC, this, MAGIC_METEO, vPos, D3DXVECTOR3(0.f, 0.f, 0.f), m_tCharacterState.iATK * 2, NULL);
					ENGINE::GetManagement()->AddGameObject(L"Magic", 1, pMagic);
				}
				//메테오
				//상하좌우로 3정도씩 떨어진 곳에서 랜덤으로 생성을 해주자...
				break;
			}
			//스킬 생성... 이녀석은 히트박스와 스킬을 생성해준다.

			m_eBattleMessage = BATTLE_MESSAGE_END;
		}
		
		//추가적으로 이펙트 생성도 해주어야 한다...
		//이펙트는 나중에 추가...
	}

	return 0;
}
