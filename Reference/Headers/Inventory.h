/*!
 * \file Inventory.h
 * \date 2016/06/07 21:23
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

#ifndef Inventory_h__
#define Inventory_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class CItem;

class ENGINE_DLL_SPECIFIER CInventory : public CGameObject
{
private:
	eCharacterID	m_eCharID;
	vector<CItem*> m_vecInven;

public:
	static CInventory* Create(eObjectType _eObjectType);

private:
	virtual HRESULT Initialize(void);
	void		Release(void);
	HRESULT		Initialize(int iNum);

public:
	virtual int Update(void);
	virtual void Render(void);

	eCharacterID	GetCharacterID(void);
	vector<CItem*>*	GetvecInven(void);
private:
	explicit CInventory(eObjectType _eObjectType);

public:
	virtual ~CInventory(void);
};

END_NAMESPACE


#endif // Inventory_h__