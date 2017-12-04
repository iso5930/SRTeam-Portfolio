/*!
 * \file MonsterGroup.h
 * \date 2016/06/18 20:44
 *
 * \author ������
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef MonsterGroup_h__
#define MonsterGroup_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class CMonster;
class CMainUIObserver;

class ENGINE_DLL_SPECIFIER CMonsterGroup : public CGameObject
{
private:
	vector<CMonster*>	m_vecMonster;
	bool				m_bMonsterDeath;
	CMainUIObserver*	m_pMainUIObserver;

	// get component helper
	vector<CMonster*>::iterator m_finder;
	vector<CMonster*>::iterator m_finder_end;

public:
	static CMonsterGroup* Create(eObjectType _eObjectType);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);

public:
	virtual int		Update(void);
	virtual void	Render(void);

public:
	vector<CMonster*>*	GetMonsterGroup(void);
	void				SetMonsterDeath(void);
	void				BattleInit(void);
	void				DeleteMonster(int _iCur);
	CMonster*			GetLeaderMonster(void);

public:
	void	AddMonster(CMonster* _pMonster);

	//! �̷��� ��ü�� wrapper�� �۵��ϴ� ģ������, get component�� �������̵� �������..
	virtual void PrepareFind(void);
	virtual ENGINE::CComponent* GetComponent(const wstring& _strComponentKey);

private:
	explicit CMonsterGroup(eObjectType _eObjectType);

public:
	virtual ~CMonsterGroup(void);	
};

END_NAMESPACE

#endif // MonsterGroup_h__