#include "stdafx.h"
#include "WildBoar.h"
#include "Transform.h"
#include "Texture.h"
#include "Sprite.h"
#include "Export_Function.h"
#include "OBBCollision.h"
#include "MouseCollision.h"
#include "GroupObserver.h"
#include "CharacterGroup.h"
#include "Character.h"
#include "TerrainCollision.h"

CWildBoar::CWildBoar(eObjectType _eObjectType)
:CMonster(_eObjectType)
{

}

CWildBoar::~CWildBoar(void)
{
	Release();
}

CWildBoar* CWildBoar::Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos)
{
	CWildBoar* pMonster = new CWildBoar(_eObjectType);

	if(FAILED(pMonster->Initialize()))
	{
		SAFE_DELETE(pMonster);
	}

	pMonster->SetPos(_vPos);

	return pMonster;
}

HRESULT CWildBoar::Initialize(void)
{	
	if(FAILED(AddComponent()))
	{
		return E_FAIL;
	}

	m_tState.iLevel = 2;
	m_tState.eMonType =	MONSTER_TYPE_EARTH;
	m_tState.iSPD = 20;
	m_tState.iATK = 35;
	m_tState.iDEF = 23;
	m_tState.iEXP = 50;
	m_tState.iHitPoint = 75;
	m_tState.iMaxHitPoint = 75;
	m_tState.iBarrierPoint = 0;
	m_tState.iMaxBarrierPoint = 0;
	m_iPattern = rand() % 5;

	strcpy_s(m_tState.szName, sizeof(char) * 20, "멧돼지");

	m_eMonsterState = MONSTER_STAND;

	m_pGroupObserver = ENGINE::CGroupObserver::Create(this);
	ENGINE::GetInfoSubject()->Subscribe(m_pGroupObserver);

	m_eMonsterID = MONSTERID_WILD_BOAR;

	return S_OK;
}

int CWildBoar::Update(void)
{
	ENGINE::CTransform*	pPlayerInfo = m_pGroupObserver->GetCharacterGroup()->GetLeaderCharacter()->GetInfo();

	D3DXVECTOR3	vDist = pPlayerInfo->m_vPos - m_pInfo->m_vPos;
	
	vDist.y = 0;

	float fLength = D3DXVec3Length(&vDist);
	
	if(m_pSprite->GetFrameEnd() == true)
		m_iPattern = rand() % 5;

	//해당 거리에 플레이어가 존재시
	if(fLength < 2 && !ENGINE::GetInputManager()->GetOnEvent())
	{
		m_eMonsterState = MONSTER_MOVE;
		m_vDestPos = pPlayerInfo->m_vPos;
		m_pMovement->SetMove(true);
	}
	//평소 이동
	//else
	//{
	//	switch(m_iPattern)
	//	{
	//	case 0 :
	//		//정지
	//		m_eMonsterState = MONSTER_STAND;
	//		m_pMovement->SetMove(false);
	//		break;
	//	case 1 :
	//		//LU
	//		m_eMonsterState = MONSTER_MOVE;
	//		m_vDestPos.x -= 0.2f;
	//		m_vDestPos.z += 0.2f;
	//		m_pMovement->SetMove(true);
	//		break;

	//	case 2 :
	//		//RU
	//		m_eMonsterState = MONSTER_MOVE;
	//		m_vDestPos.x += 0.2f;
	//		m_vDestPos.z += 0.2f;
	//		m_pMovement->SetMove(true);
	//		break;

	//	case 3:
	//		//LD
	//		m_eMonsterState = MONSTER_MOVE;
	//		m_vDestPos.x -= 0.2f;
	//		m_vDestPos.z -= 0.2f;
	//		m_pMovement->SetMove(true);
	//		break;

	//	case 4:
	//		//RD
	//		m_eMonsterState = MONSTER_MOVE;
	//		m_vDestPos.x += 0.2f;
	//		m_vDestPos.z -= 0.2f;
	//		m_pMovement->SetMove(true);
	//		break;
	//	}
	//}

	CMonster::Update();

	ENGINE::CGameObject::Update();

	CMonster::SetBillBoard();

	return 0;
}

int CWildBoar::BattleUpdate(void)
{
	if(m_bMonsterDeath)
	{	
		return 0;
	}

	CMonster::BattleUpdate();

	ENGINE::CGameObject::Update();

	if(m_eMonsterState == MONSTER_ATT)
	{
		int iAtk = m_tState.iATK - ((ENGINE::CCharacter*)(m_pTarget))->GetCharacterState()->iDEF;
		if(iAtk < 1)
			iAtk = 0;
		if(m_pSprite->GetFrameEnd())
		{
			ENGINE::CGameObject* pHitBox = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTarget, 0.5f, 0.5f, 0.5f, iAtk, true, false);
			ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pHitBox);
			m_eMonsterState = MONSTER_STAND;
		}
	}

	CMonster::SetBillBoard();

	return 0;
}

HRESULT CWildBoar::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Rectangle_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"WildBoar_Stand");
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"WildBoar_Stand", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"WildBoar_Move");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"WildBoar_Move", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"WildBoar_Hit");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"WildBoar_Hit", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"WildBoar_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"WildBoar_Att", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"WildBoar_AttMove");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"WildBoar_AttMove", pComponent));
	
	pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 10.f, 10.f));
	m_pSprite = static_cast<ENGINE::CSprite*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"WildBoar_Frame", pComponent));

	pComponent = ENGINE::CMovement::Create(this, m_pInfo, &m_vDestPos, 3.f);
	m_pMovement = static_cast<ENGINE::CMovement*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Movement", pComponent));

	m_pTerrainCollision = ENGINE::CTerrainCollision::Create(this, m_pInfo, new ENGINE::CColStop(m_pInfo, m_pMovement));
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"TerrainCollision", m_pTerrainCollision));

	m_pOBBCollision = ENGINE::COBBCollision::Create(this, m_pInfo, m_pMovement, 0.5f, 0.7f, 0.5f, new ENGINE::CColMonsterPick(this));
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollision));

	m_pMouseCollision = ENGINE::CMouseCollision::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"MouseCollision", m_pMouseCollision));

	return S_OK;
}

void CWildBoar::Release(void)
{
	ENGINE::GetSoundManager()->PlayWildBoarSound(L"WildBoar_Die.wav");
}

void CWildBoar::SetAngle(void)
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

	if(m_iPrevIndex != iIndex || m_eMonsterState != m_ePrevMonsterState)
	{
		switch(m_eMonsterState)
		{
		case MONSTER_STAND:
			m_pSprite->SetFrame(FRAME(float(iIndex - 1) * 11, float(iIndex * 11) -1, 6.f));
			break;

		case MONSTER_MOVE:
			m_pSprite->SetFrame(FRAME(float(iIndex - 1) * 6, float(iIndex * 6) - 1, 8.f));
			break;

		case MONSTER_HIT:
			m_pSprite->SetFrame(FRAME(float(iIndex - 1) * 7, float(iIndex * 7) - 1, 5.f));
			break;

		case MONSTER_ATTMOVE:
			m_pSprite->SetFrame(FRAME(float(iIndex - 1) * 2, float(iIndex * 2) - 1, 3.f));
			break;

		case MONSTER_ATT:
			m_pSprite->SetFrame(FRAME(float(iIndex - 1) * 2, float(iIndex * 2) - 1, 3.f));
			
			break;
		}

		m_iPrevIndex = iIndex;
	}
}

void CWildBoar::SetState(void)
{
	if(m_eMonsterState == m_ePrevMonsterState)
		return;

	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	switch(m_eMonsterState)
	{
	case MONSTER_STAND:
		iter = m_ComponentMap.find(L"WildBoar_Stand");
		break;

	case MONSTER_MOVE:
		iter = m_ComponentMap.find(L"WildBoar_Move");
		break;
	}
	
	if(iter != m_ComponentMap.end())
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);

	m_ePrevMonsterState = m_eMonsterState;
}

void CWildBoar::SetBattleState(void)
{
	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	if(m_eMonsterState == m_ePrevMonsterState)
		return;

	switch(m_eMonsterState)
	{
	case MONSTER_ATT:
		iter = m_ComponentMap.find(L"WildBoar_Att");
		ENGINE::GetSoundManager()->PlayWildBoarSound(L"WildBoar_Att.wav");
		break;

	case MONSTER_ATTMOVE:
		iter = m_ComponentMap.find(L"WildBoar_AttMove");
		break;

	case MONSTER_HIT:
		iter = m_ComponentMap.find(L"WildBoar_Hit");
		ENGINE::GetSoundManager()->PlayWildBoarSound(L"WildBoar_Damage.wav");
		break;

	case MONSTER_STAND:
		iter = m_ComponentMap.find(L"WildBoar_Stand");
		break;
	}
	
	if(iter != m_ComponentMap.end())
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);

	m_ePrevMonsterState = m_eMonsterState;
}