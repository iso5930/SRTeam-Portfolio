#include "Monster.h"
#include "MouseCollision.h"
#include "Texture.h"
#include "Sprite.h"
#include "GroupObserver.h"
#include "MainUIObserver.h"

ENGINE::CMonster::CMonster(eObjectType _eObjectType)
:CGameObject(_eObjectType)
, m_eMonsterState(MONSTER_END)
, m_ePrevMonsterState(MONSTER_END)
, m_iPrevIndex(0)
, m_pGroupObserver(NULL)
, m_bMonsterDeath(false)
, m_eUnitType(UNIT_MONSTER)
, m_eMonsterID(MONSTERID_END)
, m_bAttack(false)
, m_iPattern(0)
{
	ZeroMemory(&m_tState, sizeof(MONSTER_STATE));
	ZeroMemory(&m_szSubName, sizeof(TCHAR) * 50);
}

ENGINE::CMonster::~CMonster(void)
{
	Release();
}

int ENGINE::CMonster::Update(void)
{
	SetAngle();
	this->SetState();
	return 0;
}

int ENGINE::CMonster::BattleUpdate(void)
{
	SetAngle();
	this->SetBattleState();

	//if(m_eMonsterID != MONSTERID_AKHENATON)
	//{
		if(m_eMonsterState == MONSTER_HIT)
		{
			if(m_pSprite->GetFrameEnd() == true)
			{
				m_eMonsterState = MONSTER_STAND;
			}

			D3DXVECTOR3 vDeltaMove = m_vHitDir * 1.f * ENGINE::GetTimeDelta();

			m_pInfo->m_vPos += vDeltaMove;

			m_pMovement->SetDeltaMove(vDeltaMove);
			//movement쪽으로 넣어주자..
		}
		else if(m_eMonsterState == MONSTER_ATTMOVE)
		{
			if(m_pMovement->GetMove() == false)
			{
				if(m_bAttack)
				{
					m_eMonsterState = MONSTER_ATT;
					m_bAttack = false;
				}
				else
					m_eMonsterState = MONSTER_STAND;
			}

			m_vDestPos = (*m_pTargetPos);
		}
	//}
		
	return 0;
}

bool ENGINE::CMonster::MonsterPickCheck(bool* _Check)
{
	m_pMouseCollision->PickObject(m_pOBBCollision->GetOBBInfo(), &m_pInfo->m_matWorld, new ENGINE::CColMonsterCheck(_Check));

	return (*_Check);
}

ENGINE::CTransform* ENGINE::CMonster::GetInfo(void)
{
	return m_pInfo;
}

MONSTER_STATE* ENGINE::CMonster::GetMonsterState(void)
{
	return &m_tState;
}

void ENGINE::CMonster::SetBillBoard(void)
{
	this->SetAngle();
	m_pInfo->Update();

	D3DXMATRIX matBill;
	ENGINE::GetDevice()->GetTransform(D3DTS_VIEW, &matBill);
	ZeroMemory(matBill.m[3], sizeof(float) * 3);
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;
}

void ENGINE::CMonster::Render(void)
{
	if(m_bMonsterDeath)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice = ENGINE::GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	ENGINE::GetDevice()->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pTexture->Render((int)m_pSprite->GetCurFrame());
	m_pVIBuffer->Render();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pOBBCollision->Render();
}

void ENGINE::CMonster::SetPos(D3DXVECTOR3 _vPos)
{
	m_pInfo->m_vPos = _vPos;
}

void ENGINE::CMonster::SetOwner(CMonsterGroup* _pOwner)
{
	m_pOwner = _pOwner;
}

ENGINE::CMonsterGroup* ENGINE::CMonster::GetOwner(void)
{
	return m_pOwner;
}

void ENGINE::CMonster::MonsterHit(int _iAtk, D3DXVECTOR3 _vDir)
{
	if(m_tState.iBarrierPoint > 0)
	{
		m_tState.iBarrierPoint -= _iAtk;

		if(m_tState.iBarrierPoint < 0)
		{
			m_tState.iBarrierPoint = 0;
		}
	}
	else
	{
		m_tState.iHitPoint -= _iAtk;

		if(m_tState.iHitPoint <= 0)
		{
			m_tState.iHitPoint = 0;
			m_bMonsterDeath = true;
		}
	}

	m_eMonsterState = MONSTER_HIT;

	m_vHitDir = _vDir;

	m_bAttack = false;
}

bool ENGINE::CMonster::GetMonsterDeath(void)
{
	return m_bMonsterDeath;
}

eUnitType ENGINE::CMonster::GetUnitType(void)
{
	return m_eUnitType;
}

eMonsterID ENGINE::CMonster::GetMonsterID(void)
{
	return m_eMonsterID;
}

void ENGINE::CMonster::SetDestPos(D3DXVECTOR3 _vPos)
{
	m_vDestPos = _vPos;
}

eMonsterState ENGINE::CMonster::GetState(void)
{
	return m_eMonsterState;
}

void ENGINE::CMonster::SetState(eMonsterState _State)
{
	m_eMonsterState = _State;
}

void ENGINE::CMonster::SetTargetPos(D3DXVECTOR3* _pTargetPos)
{	
	m_pTargetPos = _pTargetPos;

	D3DXVECTOR3 vSource(m_pInfo->m_vPos.x, 0.f, m_pInfo->m_vPos.z);
	D3DXVECTOR3 vTarget(_pTargetPos->x, 0.f, _pTargetPos->z);
	D3DXVECTOR3 vDist = vSource - vTarget;

	float fLength = D3DXVec3Length(&vDist);

	if(fLength >= 1.f)
	{
		m_pMovement->SetMove(true);
		m_eMonsterState = MONSTER_ATTMOVE;
		m_bAttack = true;
		m_vDestPos = (*_pTargetPos);
	}
}

void ENGINE::CMonster::SetSubName(PTCHAR _pName)
{
	lstrcpy(m_szSubName, _pName);
}

ENGINE::CMovement* ENGINE::CMonster::GetMovement(void)
{
	return m_pMovement;
}

void ENGINE::CMonster::SetTarget(CGameObject* _pTarget)
{
	m_pTarget = _pTarget;
}

void ENGINE::CMonster::Release(void)
{

}