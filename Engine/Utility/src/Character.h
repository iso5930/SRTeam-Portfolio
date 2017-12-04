/*!
 * \file Character.h
 * \date 2016/06/07 15:33
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

#ifndef Character_h__
#define Character_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class CEquip;
class CAbilityGroup;
class CTransform;
class CVIBuffer;
class CTexture;
class CSprite;
class CMouseCollision;
class CMovement;
class COBBCollision;
class CTerrainCollision;
class CCharacterGroup;
class CInventory;
class CMonster;

class ENGINE_DLL_SPECIFIER CCharacter : public CGameObject
{
protected:
	CCharacterGroup*		m_pOwner;

protected:
	//Struct & Info & Buffer & Texture
	CHARACTER_STATE			m_tCharacterState;
	CHARACTER_STATE			m_tTempState;
	CTransform*				m_pInfo;
	CVIBuffer*				m_pVIBuffer;
	CTexture*				m_pTexture;

protected:
	//Enum
	eCharacterID			m_eCharacterID;
	eAbilityID				m_eAbilityID;
	eCharacterState			m_eState;
	eUnitType				m_eUnitType;
	
protected:
	//Equip & Ability
	CEquip*					m_pEquip;
	CAbilityGroup*			m_pAbilityGroup;
	vector<eAbilityType>	m_vecAbilityType;
	//Inventory
	CInventory*				m_pInventory;

protected:
	//Component
	CMouseCollision*		m_pMouseCollision;
	CMovement*				m_pMovement;
	CSprite*				m_pSpriteFrame;
	COBBCollision*			m_pOBBCollision;
	CTerrainCollision*		m_pTerrainCollision;

protected:
	//PrevState
	eCharacterState			m_ePrevState;
	int						m_iPrevIndex;

	int						m_iPrevFrmae;
	//D3DXVECTOR3				m_vPrevDir;
	D3DXVECTOR3				m_vPrevPos;

	//NowState
	int						m_iNowFrame;
	//D3DXVECTOR3				m_vNowDir;

protected:
	//Outer
	D3DXVECTOR3				m_vDestPos;
	float					m_fAngle;

protected:
	//Test
	deque<MEMENTO>			m_dequeMemento;
	float					m_fJumpY;
	bool					m_bJump;
	float					m_fTime;

protected:
	int						m_iCntX;
	int						m_iCntZ;

protected:
	//Battle
	eBattleMessage			m_ePrevBattleMessage;
	eBattleMessage			m_eBattleMessage;
	bool					m_bAttackMessage;
	float					m_fDefTime;
	COBBCollision*			m_pHitBox;
	D3DXVECTOR3				m_vHitDir; //피격시 팅겨나가는 방향 벡터
	bool					m_bSkillRun; //스킬을 사용했고 지금 움직이고 있는 중일때
	int						m_iAbilityCur; //스킬을 사용했다고 입력이 들어왔을때 몇번째에 있는 스킬을 사용할지.. 결정
	int						m_iSkillCount;
	CMonster*				m_pTargetMonster;
	bool					m_bSkillCharge;

public:
	void					SetCntXZ(int _CntX, int _CntZ);
	bool					BattleResult(int _iExp);

public:
	eCharacterID				GetCharacterID(void);
	eAbilityID					GetAbilityID(void);
	CHARACTER_STATE*			GetCharacterState(void);
	CEquip*						GetEquip(void);
	CInventory*					GetInven(void);
	CAbilityGroup*				GetAbilityGroup(void);
	vector<eAbilityType>*		GetAbilityType(void);
	CTransform*					GetInfo(void);
	float						GetAngle(void);

	eCharacterState				GetPrevState(void);
	int							GetPrevFrame(void);
	deque<MEMENTO>*				GetMemento(void);
	eBattleMessage				GetBattleMessage(void);
	void						SetDestPos(D3DXVECTOR3* _pPos);
	void						SetBattleMessage(eBattleMessage _Message);
	void						SetOwner(CCharacterGroup* _pOwner);
	CCharacterGroup*			GetOwner(void);
	void						SetCharacterState(eCharacterState _State);
	eUnitType					GetUnitType(void);
	void						CharacterHit(int _iAtk, D3DXVECTOR3 _vDir, D3DXVECTOR3 _vDest);
	void						SetAbilityCur(int _iCur);
	void						SetMonsterTarget(CMonster* _pMonsterTarget);
	void						SetSkillCharge(bool _bCharge);
	D3DXVECTOR3					GetDestPos(void);
	void						SetCharacterStatus(CHARACTER_STATE	_Status);
	CHARACTER_STATE				GetOriginStatus(void);
	void						SetState(int _iBp, int _iAtk, int _iDef, int _iSpd, int _iMag, int _iCri);
	
public:
	void	SubCharacterUpdate(deque<MEMENTO>* _dequePrevMemento);
	virtual int Update(void);
	virtual	int	BattleUpdate(void);
	virtual void SetCamera(void);
	virtual void Render(void);
	
public:
	void	Jump(void);
	void	SetBillBoard(void);
	void	ResetCharacter(void);
	void SetStateForEvent(eCharacterState _eState)
	{
		m_eState = _eState;
	}
	float GetLengthToDest(void);
	void SetPos(float _fX, float _fZ);
	void SetSpeed(float _fSpeed);
	D3DXVECTOR3 GetPos(void);

public:
	void	SetAngle(void);
	void	SetDir(void);
	void	KeyCheck(void);

	virtual void SetBattleAngle(void)PURE;
	virtual void SetState(void)PURE;
	virtual void BattleState(void)PURE;

private:
	void	Release(void);
	int		GetSubCharacterFrame(deque<MEMENTO>* _dequePrevMemento);

protected:
	explicit CCharacter(eObjectType _eObjectType);

public:
	virtual ~CCharacter(void);
};

END_NAMESPACE

#endif // Character_h__