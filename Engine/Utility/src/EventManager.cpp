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

		// ���� �ش� �̺�Ʈ�� ����Ǿ��ٸ�..
		if (pEvent->GetState() == CGameEvent::EVENT_STATE_FINISH)
		{
			++uNoEventCounter;
			continue;
		}

		// �̺�Ʈ�� �����ϱ⿡ ������ ����ġ���� �������� Ȯ�� ��..
		if(CheckEventConditions(pEvent))
		{
			// Ű�� ���Ѵ�..
			ENGINE::GetInputManager()->SetOnEvent(true);

			// �̺�Ʈ�� ���� �ѹ��� ���۵��� �ʾҾ��ٸ�,
			if (pEvent->GetState() == CGameEvent::EVENT_STATE_WAIT)
			{
				pEvent->Start();
				pEvent->Update();
			}
			// �̺�Ʈ�� �ѹ��̶� ���۵Ǿ����ٸ�..
			else if (pEvent->GetState() == CGameEvent::EVENT_STATE_ING)
			{
				// �̺�Ʈ�� 1ȸ���� ���,
				if (pEvent->IsDisposable())
				{
					pEvent->Finish();
					++uNoEventCounter;
				}
				// �̺�Ʈ�� �ݺ����� ���..
				else
					pEvent->Update();
			}
		}
		else
			++uNoEventCounter;
	}

	if (uNoEventCounter == uEventVecSize)
	{
		// Ű �Է��� Ǭ��..
		ENGINE::GetInputManager()->SetOnEvent(false);
	}

	return 0;
}

void ENGINE::CEventManager::CreateSwitch(const wstring& _strSwitchKey)
{
	SWITCH_MAP::iterator iter = m_SwitchMap.find(_strSwitchKey);
	if (iter != m_SwitchMap.end())
	{
		UTIL::SHOW_ERROR(_strSwitchKey.c_str(), L"����ġ Ű �̹� �ִµ���");
		return;
	}

	m_SwitchMap.insert(SWITCH_MAP::value_type(_strSwitchKey, false));
}

void ENGINE::CEventManager::SwitchOn(const wstring& _strSwitchKey)
{
	SWITCH_MAP::iterator iter = m_SwitchMap.find(_strSwitchKey);
	if (iter == m_SwitchMap.end())
	{
		UTIL::SHOW_ERROR(_strSwitchKey.c_str(), L"����ġ Ű ���µ� �ӷ��� ��");
		return;
	}

	iter->second = true;
}

void ENGINE::CEventManager::SwitchOff(const wstring& _strSwitchKey)
{
	SWITCH_MAP::iterator iter = m_SwitchMap.find(_strSwitchKey);
	if (iter == m_SwitchMap.end())
	{
		UTIL::SHOW_ERROR(_strSwitchKey.c_str(), L"����ġ Ű ���µ� ������ ��");
		return;
	}

	iter->second = false;
}

bool ENGINE::CEventManager::IsSwitchOn(const wstring& _strSwitchKey)
{
	SWITCH_MAP::iterator iter = m_SwitchMap.find(_strSwitchKey);
	if (iter == m_SwitchMap.end())
	{
		UTIL::SHOW_ERROR(_strSwitchKey.c_str(), L"����ġ Ű ����");
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
