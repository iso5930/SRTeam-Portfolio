/*!
 * \file Collision.h
 * \date 2016/06/05 16:52
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

#ifndef Collision_h__
#define Collision_h__

#include "Engine_Include.h"
#include "Component.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CCollision : public CComponent
{
	// member variable
protected:
	// -

	// member function
public:
	// -

	// getter & setter
public:
	// -

	// constructor & destructor
protected:
	explicit CCollision(ENGINE::CGameObject* _pOwner);
public:
	virtual ~CCollision(void) PURE;
};
END_NAMESPACE

#endif // Collision_h__