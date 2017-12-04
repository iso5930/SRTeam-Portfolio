/*!
 * \file AbilityGroup.h
 * \date 2016/06/07 21:24
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

#ifndef AbilityGroup_h__
#define AbilityGroup_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class CAbility;

class ENGINE_DLL_SPECIFIER CAbilityGroup : public CGameObject
{
private:
	eCharacterID		m_eCharID;
	vector<CAbility*>	m_vecAbility;

public:
	static CAbilityGroup* Create(eObjectType _eObjectType, eCharacterID _CharID);

private:
	virtual HRESULT Initialize(void);
	HRESULT Initialize(eCharacterID _CharID);
	void	Release(void);

public:
	virtual int Update(void);
	virtual void Render(void);

public:
	void				AddAbility(CAbility* _pAbility);
	eCharacterID		GetCharacterID(void);
	vector<CAbility*>*	GetAbility(void);

private:
	explicit CAbilityGroup(eObjectType _eObjectType);

public:
	virtual ~CAbilityGroup(void);
};

END_NAMESPACE

#endif // AbilityGroup_h__