/*!
 * \file MainUIObserver.h
 * \date 2016/06/05 21:19
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

#ifndef MainUIObserver_h__
#define MainUIObserver_h__

#include "Observer.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CMainUIObserver : public CObserver
{
private:
	int					m_iLeftIndex;
	int					m_iTopIndex;
	bool				m_bSwitch;

public:
	int		GetTopIndex(void);
	int		GetLeftIndex(void);
	bool	GetSwitch(void);

public:
	static CMainUIObserver* Create(ENGINE::CGameObject* _pOwner);

public:
	virtual	void Update(int _iMessage);

private:
	CMainUIObserver(ENGINE::CGameObject* _pOwner);

public:
	virtual ~CMainUIObserver(void);
};

END_NAMESPACE

#endif // MainUIObserver_h__
