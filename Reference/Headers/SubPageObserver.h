/*!
 * \file SubPageObserver.h
 * \date 2016/06/05 21:29
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

#ifndef SubPageObserver_h__
#define SubPageObserver_h__

#include "Observer.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CSubPageObserver : public CObserver
{
private:
	eCharacterID m_eCharCur;

public:
	eCharacterID GetCharCur(void);

public:
	static CSubPageObserver* Create(ENGINE::CGameObject* _pOwner);

public:
	virtual void Update(int _iMessage);

private:
	CSubPageObserver(ENGINE::CGameObject* _pOwner);

public:
	virtual ~CSubPageObserver(void);
};

END_NAMESPACE

#endif // SubPageObserver_h__