/*!
 * \file Equip.h
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

#ifndef Equip_h__
#define Equip_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class CItem;

class ENGINE_DLL_SPECIFIER CEquip : public CGameObject
{
private:
	eCharacterID	m_eCharID;
	vector<CItem*>	m_vecEquip;

public:
	static CEquip* Create(eObjectType _eObjectType, eCharacterID _CharID);

private:
	virtual HRESULT Initialize(void);
	HRESULT Initialize(eCharacterID _CharID);
	void Release(void);

public:
	virtual int Update(void);
	virtual void Render(void);
	void InitEquip(int iNum);

public:
	eCharacterID	GetCharacterID(void);
	vector<CItem*>*	GetvecEquip(void);

private:
	explicit CEquip(eObjectType _eObjectType);

public:
	virtual ~CEquip(void);
};

END_NAMESPACE

#endif // Equip_h__