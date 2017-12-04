#include "SubPageObserver.h"

#include "Export_Function.h"

ENGINE::CSubPageObserver::CSubPageObserver(ENGINE::CGameObject* _pOwner)
:CObserver(_pOwner)
,m_eCharCur(CHARACTER_SIZZ)
{

}

ENGINE::CSubPageObserver::~CSubPageObserver(void)
{

}

eCharacterID ENGINE::CSubPageObserver::GetCharCur(void)
{
	return m_eCharCur;
}

ENGINE::CSubPageObserver* ENGINE::CSubPageObserver::Create(ENGINE::CGameObject* _pOwner)
{
	return new CSubPageObserver(_pOwner);
}

void ENGINE::CSubPageObserver::Update(int _iMessage)
{
	const list<void*>* pDataList = ENGINE::GetInfoSubject()->GetDataList(_iMessage);

	if(pDataList->size() == 0)
	{
		return;
	}

	void* pData = pDataList->front();

	switch(_iMessage)
	{
	case MESSAGE_SUBUI:
		m_eCharCur = *((eCharacterID*)(pData));
		break;
	}
}