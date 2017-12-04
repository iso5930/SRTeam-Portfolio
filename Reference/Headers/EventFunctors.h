/*!
 * \file EventFunctors.h
 * \date 2016/06/20 20:00
 *
 * \author ¹ÚÁ¤¹Î
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef EventFunctors_h__
#define EventFunctors_h__

#include "GameEvent.h"

BEGIN_NAMESPACE(ENGINE)
class CEventFunctor
{
public:
	virtual void operator ()(CGameEvent* _pEvent) PURE;
public:
	explicit CEventFunctor(void) { }
	virtual ~CEventFunctor(void) PURE { }
};
END_NAMESPACE

#endif // EventFunctors_h__