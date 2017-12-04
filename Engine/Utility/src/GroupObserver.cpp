#include "GroupObserver.h"

#include "Export_Function.h"

#include "Equip.h"
#include "AbilityGroup.h"

ENGINE::CGroupObserver::CGroupObserver(ENGINE::CGameObject* _pOwner)
:CObserver(_pOwner)
{

}

ENGINE::CGroupObserver::~CGroupObserver(void)
{

}

ENGINE::CGroupObserver* ENGINE::CGroupObserver::Create(ENGINE::CGameObject* _pOwner)
{
	return new CGroupObserver(_pOwner);
}

void ENGINE::CGroupObserver::Update(int _iMessage)
{
	const list<void*>* pDataList = ENGINE::GetInfoSubject()->GetDataList(_iMessage);

	if(pDataList->size() == 0)
	{
		return;
	}

	void* pData = pDataList->front();

	switch(_iMessage)
	{
	case MESSAGE_CHARACTER_GROUP:
		m_pCharacterGroup = ((CCharacterGroup*)(pData));
		break;

	case MESSAGE_INVEN:
		m_pInventory = ((CInventory*)(pData));
		break;

	case MESSAGE_EQUIP:
		switch(((CEquip*)(pData))->GetCharacterID())
		{
		case CHARACTER_SIZZ:
			m_pEquip[CHARACTER_SIZZ] = ((CEquip*)(pData));
			break;

		case CHARACTER_MARIA:
			m_pEquip[CHARACTER_MARIA] = ((CEquip*)(pData));
			break;
		}
		break;

	case MESSAGE_ABILITY:
		switch(((CAbilityGroup*)(pData))->GetCharacterID())
		{
		case CHARACTER_SIZZ:
			m_pAbilityGroup[CHARACTER_SIZZ] = ((CAbilityGroup*)(pData));
			break;

		case CHARACTER_MARIA:
			m_pAbilityGroup[CHARACTER_MARIA] = ((CAbilityGroup*)(pData));
			break;
		}

		break;
	}
}

ENGINE::CCharacterGroup* ENGINE::CGroupObserver::GetCharacterGroup(void)
{
	return m_pCharacterGroup;
}

ENGINE::CInventory* ENGINE::CGroupObserver::GetInventory(void)
{
	return m_pInventory;
}

ENGINE::CEquip* ENGINE::CGroupObserver::GetEquip(eCharacterID _eType)
{
	return m_pEquip[_eType];
}

ENGINE::CAbilityGroup* ENGINE::CGroupObserver::GetAbilityGroup(eCharacterID _eType)
{
	return m_pAbilityGroup[_eType];
}