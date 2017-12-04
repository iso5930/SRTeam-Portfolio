/*!
 * \file Component.h
 * \date 2016/05/29 3:39
 *
 * \author ¹ÚÁ¤¹Î
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Component_h__
#define Component_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class CGameObject;
class ENGINE_DLL_SPECIFIER CComponent
{
	// member variable
protected:
	CGameObject* m_pOwner;

	// member function
public:
	virtual int Update(void);

	// getter & setter
public:
	const CGameObject* GetOwner(void) const;

	// constructor & destructor
protected:
	explicit CComponent(CGameObject* _pOwner);
public:
	virtual ~CComponent(void) PURE;
};
END_NAMESPACE

#endif // Component_h__