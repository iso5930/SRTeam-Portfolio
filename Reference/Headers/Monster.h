/*!
 * \file Monster.h
 * \date 2016/06/18 20:50
 *
 * \author 이진형
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Monster_h__
#define Monster_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class CTransform;
class CVIBuffer;
class CTexture;
class CSprite;
class CMouseCollision;
class COBBCollision;
class CMovement;
class CMonsterGroup;
class CGroupObserver;
class CTerrainCollision;

class ENGINE_DLL_SPECIFIER CMonster : public CGameObject
{
protected:
	CMonsterGroup*		m_pOwner;

protected:
	MONSTER_STATE		m_tState;
	int					m_iPattern;

protected:
	CGroupObserver*		m_pGroupObserver;

protected:
	CTransform*			m_pInfo;
	CVIBuffer*			m_pVIBuffer;
	CTexture*			m_pTexture;
	CSprite*			m_pSprite;
	CMouseCollision*	m_pMouseCollision;
	COBBCollision*		m_pOBBCollision;
	CMovement*			m_pMovement;
	CTerrainCollision*	m_pTerrainCollision;

protected:
	eMonsterState		m_eMonsterState;
	eUnitType			m_eUnitType;
	eMonsterID			m_eMonsterID;

protected:
	eMonsterState		m_ePrevMonsterState;
	int					m_iPrevIndex;

protected:
	D3DXVECTOR3			m_vDestPos;
	bool				m_bMonsterDeath;
	D3DXVECTOR3			m_vHitDir; //피해를 입었을때..
	D3DXVECTOR3*		m_pTargetPos; //공격 타겟. 실시간으로 DestPos에 대입
	bool				m_bAttack;
	TCHAR				m_szSubName[50];
	CGameObject*		m_pTarget;

public:
	virtual int Update(void);
	virtual int BattleUpdate(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	void	SetBillBoard(void);
	bool	MonsterPickCheck(bool* _Check);
	void	MonsterHit(int _iAtk, D3DXVECTOR3 _vDir);

protected:
	virtual void	SetState(void)PURE;
	virtual	void	SetBattleState(void)PURE;
	virtual	void	SetAngle(void)PURE;
	
public:
	CTransform*		GetInfo(void);
	MONSTER_STATE*	GetMonsterState(void);
	void			SetPos(D3DXVECTOR3 _vPos);
	CMonsterGroup*	GetOwner(void);
	void			SetOwner(CMonsterGroup* _pOwner);
	bool			GetMonsterDeath(void);
	eUnitType		GetUnitType(void);
	eMonsterID		GetMonsterID(void);
	void			SetDestPos(D3DXVECTOR3 _vPos);
	eMonsterState	GetState(void);
	void			SetState(eMonsterState _State);
	void			SetTargetPos(D3DXVECTOR3* _pTargetPos);
	void			SetSubName(PTCHAR _pName);
	CMovement*		GetMovement(void);
	void			SetTarget(CGameObject* _pTarget);
	

protected:
	explicit CMonster(eObjectType _eObjectType);

public:
	virtual ~CMonster(void);
};

END_NAMESPACE

#endif // Monster_h__