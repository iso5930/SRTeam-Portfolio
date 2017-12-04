#include "EventManager.h"
#include "GameEvent.h"
#include "Export_Function.h"

IMPLEMENT_SINGLETON(ENGINE::CEventManager)

ENGINE::CEventManager::CEventManager(void)
{

}

ENGINE::CEventManager::~CEventManager(void)
{
	Release();
}

int ENGINE::CEventManager::Update(CScene::EVENT_VEC* _pEventVec)
{
	unsigned int uNoEventCounter = 0;
	unsigned int uEventVecSize = _pEventVec->size();
	for (unsigned int i = 0; i < uEventVecSize; ++i)
	{
		ENGINE::CGameEvent* pEvent = ((*_pEventVec)[i]);

		// 만약 해당 이벤트가 종료되었다면..
		if (pEvent->GetState() == CGameEvent::EVENT_STATE_FINISH)
		{
			++uNoEventCounter;
			continue;
		}

		// 이벤트를 실행하기에 적절한 스위치들이 켜졌는지 확인 후..
		if(CheckEventConditions(pEvent))
		{
			// 키를 락한다..
			ENGINE::GetInputManager()->SetOnEvent(true);

			// 이벤트가 아직 한번도 시작되지 않았었다면,
			if (pEvent->GetState() == CGameEvent::EVENT_STATE_WAIT)
			{
				pEvent->Start();
				pEvent->Update();
			}
			// 이벤트가 한번이라도 시작되었었다면..
			else if (pEvent->GetState() == CGameEvent::EVENT_STATE_ING)
			{
				// 이벤트가 1회용일 경우,
				if (pEvent->IsDisposable())
				{
					pEvent->Finish();
					++uNoEventCounter;
				}
				// 이벤트가 반복성일 경우..
				else
					pEvent->Update();
			}
		}
		else
			++uNoEventCounter;
	}

	if (uNoEventCounter == uEventVecSize)
	{
		// 키 입력을 푼다..
		ENGINE::GetInputManager()->SetOnEvent(false);
	}

	return 0;
}

void ENGINE::CEventManager::CreateSwitch(const wstring& _strSwitchKey)
{
	SWITCH_MAP::iterator iter = m_SwitchMap.find(_strSwitchKey);
	if (iter != m_SwitchMap.end())
	{
		UTIL::SHOW_ERROR(_strSwitchKey.c_str(), L"스위치 키 이미 있는뎁쇼");
		return;
	}

	m_SwitchMap.insert(SWITCH_MAP::value_type(_strSwitchKey, false));
}

void ENGINE::CEventManager::SwitchOn(const wstring& _strSwitchKey)
{
	SWITCH_MAP::iterator iter = m_SwitchMap.find(_strSwitchKey);
	if (iter == m_SwitchMap.end())
	{
		UTIL::SHOW_ERROR(_strSwitchKey.c_str(), L"스위치 키 없는데 켤려고 함");
		return;
	}

	iter->second = true;
}

void ENGINE::CEventManager::SwitchOff(const wstring& _strSwitchKey)
{
	SWITCH_MAP::iterator iter = m_SwitchMap.find(_strSwitchKey);
	if (iter == m_SwitchMap.end())
	{
		UTIL::SHOW_ERROR(_strSwitchKey.c_str(), L"스위치 키 없는데 끌려고 함");
		return;
	}

	iter->second = false;
}

bool ENGINE::CEventManager::IsSwitchOn(const wstring& _strSwitchKey)
{
	SWITCH_MAP::iterator iter = m_SwitchMap.find(_strSwitchKey);
	if (iter == m_SwitchMap.end())
	{
		UTIL::SHOW_ERROR(_strSwitchKey.c_str(), L"스위치 키 없엉");
		return false;
	}

	return iter->second;
}

bool ENGINE::CEventManager::CheckEventConditions(CGameEvent* _pEvent)
{
	const CGameEvent::CONDITION_VEC* pConditions = _pEvent->GetConditions();

	unsigned int uConditionVecSize = pConditions->size();
	for (unsigned int j = 0; j < uConditionVecSize; ++j)
	{
		SWITCH_MAP::iterator iter = m_SwitchMap.find((*pConditions)[j]);
		if (iter == m_SwitchMap.end() || iter->second == false)
			return false;
	}

	return true;
}

void ENGINE::CEventManager::Release(void)
{
	m_SwitchMap.clear();
}
