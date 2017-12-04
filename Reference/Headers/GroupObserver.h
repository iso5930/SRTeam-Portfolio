/*!
 * \file GroupObserver.h
 * \date 2016/06/07 19:34
 *
 * \author ÀÌÁøÇü
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/


#ifndef GroupObserver_h__
#define GroupObserver_h__

#include "Observer.h"

BEGIN_NAMESPACE(ENGINE)

class CCharacterGroup;
class CInventory;
class CEquip;
class CAbilityGroup;

class ENGINE_DLL_SPECIFIER CGroupObserver : public CObserver
{
private:
	CCharacterGroup*	m_pCharacterGroup;
	CInventory*			m_pInventory;
	CEquip*				m_pEquip[CHARACTER_END];
	CAbilityGroup*		m_pAbilityGroup[CHARACTER_END];

public:
	CCharacterGroup* GetCharacterGroup(void);
	CInventory*		GetInventory(void);
	CEquip*			GetEquip(eCharacterID _eType);
	CAbilityGroup*	GetAbilityGroup(eCharacterID _eType);

public:
	static CGroupObserver* Create(ENGINE::CGameObject* _pOwner);

public:
	virtual	void Update(int _iMessage);

private:
	CGroupObserver(ENGINE::CGameObject* _pOwner);

public:
	virtual ~CGroupObserver(void);
};

END_NAMESPACE

#endif // GroupObserver_h__