/*!
 * \file Subject.h
 * \date 2016/06/04 21:26
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

#ifndef Subject_h__
#define Subject_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class CObserver;
class ENGINE_DLL_SPECIFIER CSubject
{
protected:
	typedef list<CObserver*> OBSERVER_LIST;

	// member variable
protected:
	OBSERVER_LIST m_ObserverList;

	// member function
public:
	virtual void Subscribe(CObserver* _pObserver);
	virtual void Unsubscribe(CObserver* _pObserver);
	virtual void Notify(int _iMessage);
private:
	void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
protected:
	explicit CSubject(void);
	virtual ~CSubject(void) PURE;
	MAKE_UNCOPYABLE(CSubject)
};
END_NAMESPACE

#endif // Subject_h__