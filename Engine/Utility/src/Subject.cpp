#include "Subject.h"

#include "Observer.h"

ENGINE::CSubject::CSubject(void)
{

}

ENGINE::CSubject::~CSubject(void)
{
	Release();
}

void ENGINE::CSubject::Subscribe(CObserver* _pObserver)
{
	if (_pObserver == NULL)
	{
		UTIL::SHOW_ERROR(L"NULL 포인터 입력", L"NULL이 아닌 포인터를 입력하세요!");
		return;
	}

	OBSERVER_LIST::iterator iter = m_ObserverList.begin();
	OBSERVER_LIST::iterator iter_end = m_ObserverList.end();
	for (; iter != iter_end; ++iter)
	{
		if ((*iter) == _pObserver)
		{
			UTIL::SHOW_ERROR(L"동일 포인터 존재", L"옵저버 리스트에 이미 등록된 객체입니다.");
			return;
		}
	}

	m_ObserverList.push_back(_pObserver);
}

void ENGINE::CSubject::Unsubscribe(CObserver* _pObserver)
{
	if (_pObserver == NULL)
	{
		UTIL::SHOW_ERROR(L"NULL 포인터 입력", L"NULL이 아닌 포인터를 입력하세요!");
		return;
	}

	OBSERVER_LIST::iterator iter = m_ObserverList.begin();
	OBSERVER_LIST::iterator iter_end = m_ObserverList.end();
	for (; iter != iter_end; ++iter)
	{
		if ((*iter) == _pObserver)
		{
			m_ObserverList.erase(iter);
			return;
		}
	}
}

void ENGINE::CSubject::Notify(int _iMessage)
{
	OBSERVER_LIST::iterator iter = m_ObserverList.begin();
	OBSERVER_LIST::iterator iter_end = m_ObserverList.end();
	for (; iter != iter_end; ++iter)
	{
		(*iter)->Update(_iMessage);
	}
}

void ENGINE::CSubject::Release(void)
{
	m_ObserverList.clear();
}
