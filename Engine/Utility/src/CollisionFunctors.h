/*!
 * \file CollisionFunctors.h
 * \date 2016/06/12 23:41
 *
 * \author 박정민
 * Contact: user@company.com
 *
 * \brief obb 충돌이 일어난 후, '충돌 검사 주체'는 여기 펑터 코드대로 행동하게 된다.
 *
 * TODO: long description
 *
 * \note
*/

#ifndef CollisionFunctors_h__
#define CollisionFunctors_h__

#include "GameObject.h"
#include "Monster.h"
#include "Transform.h"
#include "Movement.h"
#include "Export_Function.h"
#include "Character.h"
#include "CharacterGroup.h"
#include "HitBox.h"
#include "MonsterGroup.h"
#include "Effect.h"

BEGIN_NAMESPACE(ENGINE)
class CCollisionFunctor
{
public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal = NULL) PURE;
public:
	explicit CCollisionFunctor(void) { }
	virtual ~CCollisionFunctor(void) PURE { }
};

// 플레이어의 움직임을 상쇄시킴..
class CColStop : public CCollisionFunctor
{
private:
	ENGINE::CTransform* m_pOwnersInfo;
	ENGINE::CMovement* m_pMovement;
public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal = NULL)
	{
		D3DXVECTOR3 vMove = m_pMovement->GetDeltaMove();
		D3DXVECTOR3 vBack = vMove * -1;
		m_pOwnersInfo->m_vPos += vBack;
	}
public:
	explicit CColStop(ENGINE::CTransform* _pInfo, ENGINE::CMovement* _pMovement)
		:m_pOwnersInfo(_pInfo)
		,m_pMovement(_pMovement) { }
	virtual ~CColStop(void) { }
};

// 플레이어가 들이받은 방향에서, 붙은 다음 슬라이딩하게 만들어버림.
class CColSliding : public CCollisionFunctor
{
public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal = NULL)
	{
		_pHittedObject->PrepareFind();
		ENGINE::CTransform* pInfo = static_cast<ENGINE::CTransform*>(_pHittedObject->GetComponent(L"Transform"));
		_pHittedObject->PrepareFind();
		ENGINE::CMovement* pMovement = static_cast<ENGINE::CMovement*>(_pHittedObject->GetComponent(L"Movement"));

		D3DXVECTOR3 vMove = pMovement->GetDeltaMove();
		float fMoveLen = D3DXVec3Length(&vMove);
		D3DXVECTOR3 vNormal = *_pNormal;
		D3DXVec3Normalize(&vNormal, &vNormal);
		D3DXVECTOR3 vBack = vNormal * fMoveLen;
		pInfo->m_vPos += vBack;


		//// 다음 위치는, MoveDelta 벡터를 법선벡터에 투영했을 때로 한다.
		//D3DXVECTOR3 vMove = _pMovement->GetDeltaMove();
		//D3DXVECTOR3 vBack = vMove * -1;
		//D3DXVECTOR3 vNewNormal = *((D3DXVECTOR3*)(_pParam1));
		//D3DXVec3Normalize(&vNewNormal, &vNewNormal);
		//if (m_vNormal == vNewNormal)
		//{
		//	D3DXVECTOR3 vNext = D3DXVec3Dot(&vBack, &m_vNormal) * m_vNormal;
		//	_pInfo->m_vPos += vNext;

		//	//cout << "case AA" << endl;
		//}
		//else
		//{
		//	float fDotOld = D3DXVec3Dot(&m_vNormal, &vBack);
		//	float fDotNew = D3DXVec3Dot(&vNewNormal, &vBack);
		//	cout << fDotOld << " " << fDotNew << endl;
		//	// 새로 들어온 쪽의 코사인 값이 더 작다면..
		//	// = 새로 들어온 쪽의 각이 더 크다면..
		//	if (fDotOld > fDotNew)
		//	{
		//		// 여전히 old쪽에서 들어온거라 본다..
		//		D3DXVECTOR3 vNext = fDotOld * m_vNormal;
		//		_pInfo->m_vPos += vNext;

		//		//cout << "case BB" << endl;
		//	}
		//	else
		//	{
		//		D3DXVECTOR3 vNext = fDotNew * vNewNormal;
		//		_pInfo->m_vPos += vNext;
		//		m_vNormal = vNewNormal;

		//		cout << "case CC" << endl;
		//	}
		//}
	}
public:
	explicit CColSliding() { }
	virtual ~CColSliding(void) { }
};

class CColMonsterPick : public CCollisionFunctor
{
private:
	ENGINE::CMonster* m_pMonster;

public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal = NULL)
	{	
		ENGINE::CMonster* pMonster = dynamic_cast<ENGINE::CMonster*>(_pFunctorOwner);

		if(m_pMonster != pMonster)
		{
			return;
		}

		ENGINE::CCharacter* pCharacter = dynamic_cast<ENGINE::CCharacter*>(_pHittedObject);

		if(pCharacter == NULL)
			return;

		if(pCharacter->GetUnitType() == UNIT_PLAYER)
		{
			if(ENGINE::GetBattleManeger()->GetBattleStart() == false)
			{
				if(pCharacter == NULL || pMonster == NULL)
				{
					return;
				}
				if(pCharacter->GetOwner()->GetLeaderCharacter() == pCharacter && pMonster->GetOwner()->GetLeaderMonster() == pMonster && !ENGINE::GetInputManager()->GetOnEvent())
				{
					ENGINE::GetBattleManeger()->CreateBattle(pCharacter->GetOwner(), pMonster->GetOwner());
				}
			}
		}
	}
public:
	explicit CColMonsterPick(ENGINE::CMonster* _pMonster)
		:m_pMonster(_pMonster) { }
	virtual ~CColMonsterPick(void){ }
};

class CColMonsterHit : public CCollisionFunctor
{
private:
	ENGINE::CGameObject*	m_pTarget;
	bool*					m_pCheck;
	int						m_iAtk;
	bool					m_bPush;
	
public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal = NULL)
	{
		if(m_pCheck == NULL)
		{
			return;
		}

		if((*m_pCheck) == false)
		{
			if(m_pTarget == NULL)
			{
				//논 타겟팅 
				ENGINE::CMonster* pMonster = dynamic_cast<ENGINE::CMonster*>(_pHittedObject);

				if(!pMonster)
					return;
				
				D3DXVECTOR3 vDir = static_cast<ENGINE::CMonster*>(_pHittedObject)->GetInfo()->m_vPos - static_cast<ENGINE::CCharacter*>(_pFunctorOwner)->GetInfo()->m_vPos;

				vDir.y = 0;

				D3DXVec3Normalize(&vDir, &vDir);
		
				static_cast<ENGINE::CMonster*>(_pHittedObject)->MonsterHit(m_iAtk, vDir);
				static_cast<ENGINE::CMonster*>(_pHittedObject)->SetDestPos(static_cast<ENGINE::CCharacter*>(_pFunctorOwner)->GetInfo()->m_vPos);

				pMonster = dynamic_cast<ENGINE::CMonster*>(_pHittedObject);

				D3DXVECTOR3 vPos = pMonster->GetInfo()->m_vPos;

				ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, _pFunctorOwner, EFFECT_DAMAGE, vPos.x, vPos.y ,vPos.z);
				ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
			}

			if(m_pTarget == _pHittedObject)
			{
				D3DXVECTOR3 vDir(0.f, 0.f, 0.f);

				if(m_bPush)
				{
					vDir = static_cast<ENGINE::CMonster*>(_pHittedObject)->GetInfo()->m_vPos - static_cast<ENGINE::CCharacter*>(_pFunctorOwner)->GetInfo()->m_vPos;

					vDir.y = 0;

					D3DXVec3Normalize(&vDir, &vDir);
				}	

				static_cast<ENGINE::CMonster*>(_pHittedObject)->MonsterHit(m_iAtk, vDir);
				static_cast<ENGINE::CMonster*>(_pHittedObject)->SetDestPos(static_cast<ENGINE::CCharacter*>(_pFunctorOwner)->GetInfo()->m_vPos);
				(*m_pCheck) = true;

				ENGINE::CMonster* pMonster = dynamic_cast<ENGINE::CMonster*>(_pHittedObject);

				D3DXVECTOR3 vPos = pMonster->GetInfo()->m_vPos;

				ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, _pFunctorOwner, EFFECT_DAMAGE, vPos.x, vPos.y ,vPos.z);
				ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
			}
			
			
			/*if(static_cast<ENGINE::CMonster*>(_pHittedObject)->GetUnitType() == UNIT_MONSTER && static_cast<ENGINE::CCharacter*>(_pFunctorOwner)->GetUnitType() == UNIT_PLAYER)
			{
				
			}*/
		}
	}
public:
	explicit CColMonsterHit(int _iAtk, bool* _pCheck, ENGINE::CGameObject* _pMonster, bool _bPush)
		:m_iAtk(_iAtk), m_pCheck(_pCheck), m_pTarget(_pMonster), m_bPush(_bPush){}
	virtual ~CColMonsterHit(void){}
};

class CColMonsterToSkill : public CCollisionFunctor
{
private:
	CGameObject* m_pTarget;
	bool*		m_pCheck;
	int			m_iAtk;
	
public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal = NULL )
	{
		if((*m_pCheck) == false)
		{
			ENGINE::CMonster* pMonster = dynamic_cast<ENGINE::CMonster*>(_pHittedObject);

			if(m_pTarget == NULL)
			{
				//논타겟팅
				if(!pMonster)
					return;

				pMonster->MonsterHit(m_iAtk, D3DXVECTOR3(0.f, 0.f, 0.f));
				(*m_pCheck) = true;

				D3DXVECTOR3 vPos = pMonster->GetInfo()->m_vPos;

				ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, _pFunctorOwner, EFFECT_DAMAGE, vPos.x, vPos.y ,vPos.z);
				ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
			}
			else if(pMonster == m_pTarget)
			{
				pMonster->MonsterHit(m_iAtk, D3DXVECTOR3(0.f, 0.f, 0.f));

				(*m_pCheck) = true;

				D3DXVECTOR3 vPos = pMonster->GetInfo()->m_vPos;

				ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, _pFunctorOwner, EFFECT_DAMAGE, vPos.x, vPos.y ,vPos.z);
				ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
			}
		}
	}

public:
	explicit CColMonsterToSkill(bool* _pCheck, CGameObject* _pTarget, int _iAtk)
		:m_pCheck(_pCheck), m_pTarget(_pTarget), m_iAtk(_iAtk){}
	virtual ~CColMonsterToSkill(void){}
};

class CColCharacterToSkill : public CCollisionFunctor
{
private:
	CGameObject* m_pTarget;
	bool*			m_pCheck;
	int				m_iAtk;

public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal = NULL)
	{
		if((*m_pCheck) == false)
		{
			ENGINE::CCharacter* pCharacter = dynamic_cast<ENGINE::CCharacter*>(_pHittedObject);

			if(!pCharacter)
				return;
			
			if(m_pTarget == NULL)
			{
				//논 타겟팅
				pCharacter->CharacterHit(m_iAtk, D3DXVECTOR3(0.f, 0.f, 0.f), pCharacter->GetDestPos());

				(*m_pCheck) = true;

				D3DXVECTOR3 vPos = pCharacter->GetInfo()->m_vPos;

				ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, _pFunctorOwner, EFFECT_DAMAGE, vPos.x, vPos.y, vPos.z);
				ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
			}
			else if(pCharacter == m_pTarget)
			{
				pCharacter->CharacterHit(m_iAtk, D3DXVECTOR3(0.f, 0.f, 0.f), pCharacter->GetDestPos());

				(*m_pCheck) = true;

				D3DXVECTOR3 vPos = pCharacter->GetInfo()->m_vPos;

				ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, _pFunctorOwner, EFFECT_DAMAGE, vPos.x, vPos.y, vPos.z);
				ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
			}
		}
	}

public:
	explicit CColCharacterToSkill(bool* _pCheck, CGameObject* _pTarget, int _iAtk)
		:m_pCheck(_pCheck), m_pTarget(_pTarget), m_iAtk(_iAtk){}
	virtual ~CColCharacterToSkill(void){}
};
class CColCharacterHit : public CCollisionFunctor
{
private:
	ENGINE::CGameObject*	m_pTarget;
	int						m_iAtk;
	bool*					m_pCheck;

public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal = NULL )
	{
		if((*m_pCheck) == false)
		{
			//ENGINE::CCharacter* pChar = dynamic_cast<ENGINE::CCharacter*>(_pHittedObject);
			//if (!pChar)
				//return;

			//eUnitType eUnitID = pChar->GetUnitType();

			//if(eUnitID == UNIT_PLAYER)
			if(m_pTarget == _pHittedObject)
			{
				D3DXVECTOR3 vPos = static_cast<ENGINE::CMonster*>(_pFunctorOwner)->GetInfo()->m_vPos;

				D3DXVECTOR3 vDir = static_cast<ENGINE::CCharacter*>(_pHittedObject)->GetInfo()->m_vPos - vPos;

				vDir.y = 0.f;

				D3DXVec3Normalize(&vDir, &vDir);
				
				//static_cast<ENGINE::CCharacter*>(_pHittedObject)->SetBattleMessage(BATTLE_MESSAGE_HIT);
				static_cast<ENGINE::CCharacter*>(_pHittedObject)->CharacterHit(m_iAtk, vDir, vPos);

				(*m_pCheck) = true;
			}
		}
	}
public:
	explicit CColCharacterHit(int _iAtk, bool* _pCheck, ENGINE::CGameObject* _pTarget)
		:m_iAtk(_iAtk), m_pCheck(_pCheck), m_pTarget(_pTarget){}
	virtual ~CColCharacterHit(void){}
};

class CColMonsterCheck : public CCollisionFunctor
{
private:
	bool* m_bCheck;

public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal /* = NULL */)
	{
		(*m_bCheck) = true;
	}
public:
	explicit CColMonsterCheck(bool* _bCheck)
		:m_bCheck(_bCheck){}
	virtual ~CColMonsterCheck(void){}
};

END_NAMESPACE

#endif // CollisionFunctors_h__