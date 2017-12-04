#include "stdafx.h"
#include "Akhenaton.h"
#include "Transform.h"
#include "Sprite.h"
#include "Texture.h"
#include "OBBCollision.h"
#include "MouseCollision.h"
#include "Export_Function.h"
#include "GroupObserver.h"
#include "TerrainCollision.h"
#include "Magic.h"
#include "Sizz_Magic.h"

//이동, 공격 이동, 히트 없음 -> 이동시에 순간이동같은 개념으로 이동.

CAkhenaton::CAkhenaton(eObjectType _eObjectType)
:CMonster(_eObjectType)
{

}

CAkhenaton::~CAkhenaton(void)
{
	Release();
}

CAkhenaton* CAkhenaton::Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos)
{
	CAkhenaton* pMonster = new CAkhenaton(_eObjectType);

	if(FAILED(pMonster->Initialize()))
	{
		SAFE_DELETE(pMonster);
	}

	pMonster->SetPos(_vPos);

	return pMonster;
}

HRESULT CAkhenaton::Initialize(void)
{
	if(FAILED(AddComponent()))
	{
		return E_FAIL;
	}

	m_vDestPos = m_pInfo->m_vPos;

	m_tState.iLevel = 12;
	m_tState.eMonType = MONSTER_TYPE_WIND;
	m_tState.iSPD = 35;
	m_tState.iATK = 60;
	m_tState.iDEF = 70;
	m_tState.iEXP = 3000;
	m_tState.iHitPoint = 550;
	m_tState.iMaxHitPoint = 550;
	m_tState.iBarrierPoint = 1000;
	m_tState.iMaxBarrierPoint = 1000;
	m_iPattern = rand() % 5;

	strcpy_s(m_tState.szName, sizeof(char) * 20, "아케나톤");

	m_eMonsterState = MONSTER_STAND;

	m_pGroupObserver = ENGINE::CGroupObserver::Create(this);
	ENGINE::GetInfoSubject()->Subscribe(m_pGroupObserver);

	m_eMonsterID = MONSTERID_AKHENATON;

	return S_OK;
}

void CAkhenaton::Release(void)
{

}

int CAkhenaton::Update(void)
{
	CMonster::Update();

	ENGINE::CGameObject::Update();

	CMonster::SetBillBoard();

	return 0;
}

int CAkhenaton::BattleUpdate(void)
{
	ENGINE::CGameObject*	pMagic = NULL;

	if(m_eMonsterState == MONSTER_ATT)
	{
		m_iPattern = rand() % 3;

		//pMagic = CSizz_Magic::Create(OBJECT_TYPE_DYNAMIC, this, MAGIC_DARK, *m_pTargetPos, *m_pTargetPos, 25, NULL);
		//ENGINE::GetManagement()->AddGameObject(L"Magic", 1, pMagic);

		switch(m_iPattern)
		{
		case 0 :
			m_eMonsterState = MONSTER_STAND;
			break;

		case 1 :
			//m_eMonsterState = MONSTER_ATT;
			pMagic = CSizz_Magic::Create(OBJECT_TYPE_DYNAMIC, this, MAGIC_DARK, *m_pTargetPos, *m_pTargetPos, 25, NULL);
			ENGINE::GetManagement()->AddGameObject(L"Magic", 1, pMagic);
			break;

		case 2 :
			for(int i = 0; i < 10; ++i)
			{
				float fX = float(rand() % 4);
				float fZ = float(rand() % 4);
				float fY = float(rand() % 2);
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

				pMagic = CSizz_Magic::Create(OBJECT_TYPE_DYNAMIC, this, MAGIC_NOVA, vPos, D3DXVECTOR3(0.f, 0.f, 0.f), 10, NULL);
				ENGINE::GetManagement()->AddGameObject(L"Magic", 1, pMagic);
			}
			//m_eMonsterState = MONSTER_ATT;
			break;
		}
	}

	CMonster::BattleUpdate();

	ENGINE::CGameObject::Update();

	CMonster::SetBillBoard();

	return 0;
}

HRESULT CAkhenaton::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Rectangle_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));

	//============== 몬스터 텍스쳐 추가

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Akhenaton_Stand");
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Akhenaton_Stand", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Akhenaton_Att");
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Akhenaton_Att", pComponent));

	//============== 몬스터 텍스쳐 추가

	pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 10.f, 10.f));
	m_pSprite = static_cast<ENGINE::CSprite*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Akhenaton", pComponent));

	pComponent = ENGINE::CMovement::Create(this, m_pInfo, &m_vDestPos, 5.f);
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

void CAkhenaton::SetState(void)
{
	if(m_eMonsterState == m_ePrevMonsterState)
		return;

	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	switch(m_eMonsterState)
	{
	case MONSTER_STAND:
		iter = m_ComponentMap.find(L"Akhenaton_Stand");
		break;

	case MONSTER_MOVE:
		iter = m_ComponentMap.find(L"Akhenaton_Stand");
		break;
	}

	if(iter != m_ComponentMap.end())
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);

	m_ePrevMonsterState = m_eMonsterState;
}

void CAkhenaton::SetBattleState(void)
{

	COMPONENT_MAP::iterator iter = m_ComponentMap.end();

	if(m_eMonsterState == m_ePrevMonsterState)
		return;

	switch(m_eMonsterState)
	{
	case MONSTER_ATT:
		iter = m_ComponentMap.find(L"Akhenaton_Att");
		ENGINE::GetSoundManager()->PlayAkhenatonSound(L"Akhenaton_Att.wav");
		m_pSprite->SetFrame(FRAME(float(0), float(3), 5.f));
		break;

	case MONSTER_ATTMOVE:
		iter = m_ComponentMap.find(L"Akhenaton_Stand");
		break;

	case MONSTER_HIT:
		iter = m_ComponentMap.find(L"Akhenaton_Stand");
		ENGINE::GetSoundManager()->PlayAkhenatonSound(L"Akhenaton_Damage.wav");

		break;

	case MONSTER_STAND:
		iter = m_ComponentMap.find(L"Akhenaton_Stand");
		break;
	}

	if(iter != m_ComponentMap.end())
		m_pTexture = dynamic_cast<ENGINE::CTexture*>(iter->second);

	m_ePrevMonsterState = m_eMonsterState;
}

void CAkhenaton::SetAngle(void)
{
	if(m_eMonsterState == MONSTER_ATT)
	{
		return;
	}

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
			m_pSprite->SetFrame(FRAME(float(iIndex - 1) * 4, float(iIndex * 4) - 1, 5.f));
			break;

		case MONSTER_MOVE:
			m_pSprite->SetFrame(FRAME(float(iIndex - 1) * 4, float(iIndex * 4) - 1, 5.f));
			break;

		case MONSTER_HIT:
			m_pSprite->SetFrame(FRAME(float(iIndex - 1) * 4, float(iIndex * 4) - 1, 5.f));
			break;

		case MONSTER_ATTMOVE:
			m_pSprite->SetFrame(FRAME(float(iIndex - 1) * 4, float(iIndex * 4) - 1, 5.f));
			break;

		case MONSTER_ATT:
			m_pSprite->SetFrame(FRAME(float(iIndex - 1) * 4, float(iIndex * 4) - 1, 5.f));
			break;
		}

		//cout << "인덱스 :" << iIndex << endl;

		m_iPrevIndex = iIndex;
	}
}
