#include "MainUIObserver.h"

#include "Export_Function.h"

ENGINE::CMainUIObserver::CMainUIObserver(ENGINE::CGameObject* _pOwner)
:CObserver(_pOwner)
{

}

ENGINE::CMainUIObserver::~CMainUIObserver(void)
{

}

int ENGINE::CMainUIObserver::GetTopIndex(void)
{
	return m_iTopIndex;
}

int ENGINE::CMainUIObserver::GetLeftIndex(void)
{
	return m_iLeftIndex;
}

ENGINE::CMainUIObserver* ENGINE::CMainUIObserver::Create(ENGINE::CGameObject* _pOwner)
{
	return new CMainUIObserver(_pOwner);
}

void ENGINE::CMainUIObserver::Update(int _iMessage)
{
	const list<void*>* pDataList = ENGINE::GetInfoSubject()->GetDataList(_iMessage);

	if(pDataList->size() == 0)
	{
		return;
	}

	void* pData = pDataList->front();
	
	switch(_iMessage)
	{
	case MESSAGE_MAINUI_LEFT:
		m_iLeftIndex = *((int*)(pData));
		break;

	case MESSAGE_MAINUI_TOP:
		m_iTopIndex = *((int*)(pData));
		break;

	case MESSAGE_MAINUI_SWITCH:
		m_bSwitch = *((bool*)(pData));
		break;
	}
}

bool ENGINE::CMainUIObserver::GetSwitch(void)
{
	return m_bSwitch;
}