#include "Movement.h"
#include "Transform.h"
#include "Export_System.h"
#include "Monster.h"
#include "Character.h"

ENGINE::CMovement::CMovement(ENGINE::CGameObject* _pOwner)
:CComponent(_pOwner),
m_pInfo(NULL), 
m_pDestPos(NULL),
m_fSpeed(0.f),
m_vDir(0.f, 0.f, 0.f),
m_fDeltaTime(0.f),
m_fDist(0.f),
m_bMove(false),
m_vDeltaMove(0.f, 0.f, 0.f)
{
	
}

ENGINE::CMovement::~CMovement(void)
{

}

ENGINE::CMovement* ENGINE::CMovement::Create(ENGINE::CGameObject* _pOwner, CTransform* _pInfo, D3DXVECTOR3* _pDest, float _fSpeed)
{
	CMovement* pMovement = new CMovement(_pOwner);

	if(FAILED(pMovement->Init(_pInfo,_pDest, _fSpeed)))
	{
		SAFE_DELETE(pMovement);
	}

	return pMovement;
}

HRESULT ENGINE::CMovement::Init(CTransform* _pInfo, D3DXVECTOR3* _pDest, float _fSpeed)
{
	m_pInfo = _pInfo;
	m_pDestPos = _pDest;
	m_fSpeed = _fSpeed;

	return S_OK;
}

void ENGINE::CMovement::Move(void)
{
	D3DXVECTOR3 vTemp1(m_pDestPos->x, 0.f, m_pDestPos->z);
	D3DXVECTOR3 vTemp2(m_pInfo->m_vPos.x, 0.f, m_pInfo->m_vPos.z);

	D3DXVECTOR3 vTemp3 = vTemp1 - vTemp2;

	m_vDir = (*m_pDestPos) - m_pInfo->m_vPos;

	m_fDist = D3DXVec3Length(&vTemp3);

	D3DXVec3Normalize(&m_vDir, &m_vDir);

	//! 내가 추가했다..
	m_pInfo->m_vDir = m_vDir;

	m_vDeltaMove = m_vDir * m_fSpeed * m_fDeltaTime;

	m_pInfo->m_vPos += m_vDeltaMove;

	if(m_fDist <= 0.5f)
	{
		m_bMove = false;
	}
}



int ENGINE::CMovement::Update(void)
{
	if(m_bMove == false)
	{
		ENGINE::CMonster* pMonster = dynamic_cast<ENGINE::CMonster*>(m_pOwner);
		ENGINE::CCharacter* pCharacter = NULL;

		if(pMonster == NULL)
		{
			pCharacter = dynamic_cast<ENGINE::CCharacter*>(m_pOwner);

			if(pCharacter->GetBattleMessage() == BATTLE_MESSAGE_HIT)
			{
				return 0;
			}
		}
		else
		{
			if(pMonster->GetState() == MONSTER_HIT)
			{
				return 0;
			}
		}

		m_vDeltaMove = D3DXVECTOR3(0.f, 0.f, 0.f);

		return 0;
	}
	
	m_fDeltaTime = ENGINE::GetTimeDelta();

	Move();

	return 0;
}

void ENGINE::CMovement::SetMove(bool _bMove)
{
	m_bMove = _bMove;
}

D3DXVECTOR3 ENGINE::CMovement::GetDeltaMove(void)
{
	return m_vDeltaMove;
}

bool ENGINE::CMovement::GetMove(void)
{
	return m_bMove;
}

void ENGINE::CMovement::SetDeltaMove(D3DXVECTOR3 _vDeltaMove)
{
	m_vDeltaMove = _vDeltaMove;
}