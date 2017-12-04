/*!
 * \file Observer.h
 * \date 2016/06/04 21:37
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

#ifndef Observer_h__
#define Observer_h__

#include "Engine_Include.h"
#include "Component.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CObserver : public CComponent
{
	// member variable
protected:
	// -

	// member function
public:
	virtual void Update(int _iMessage) PURE;

	// getter & setter
public:
	// -

	// constructor & destructor
protected:
	explicit CObserver(ENGINE::CGameObject* _pOwner);
	virtual ~CObserver(void);
	MAKE_UNCOPYABLE(CObserver)
};
END_NAMESPACE

#endif // Observer_h__