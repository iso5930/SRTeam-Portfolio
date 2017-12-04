#include "GameEvent.h"
#include "EventFunctors.h"
#include "EventManager.h"

ENGINE::CGameEvent::CGameEvent(ENGINE::CEventFunctor* _pFunctor,
							   bool _bDisposable /*= false*/)
							   :m_pFunctor(_pFunctor)
							   ,m_eState(EVENT_STATE_WAIT)
							   ,m_bDisposable(_bDisposable)
{

}

ENGINE::CGameEvent::~CGameEvent(void)
{
	Release();
}

ENGINE::CGameEvent* ENGINE::CGameEvent::Create(ENGINE::CEventFunctor* _pFunctor,
											   bool _bDisposable /*= false*/)
{
	CGameEvent* pInstance = new CGameEvent(_pFunctor, _bDisposable);
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int ENGINE::CGameEvent::Update(void)
{
	if (m_pFunctor)
		(*m_pFunctor)(this);

	return 0;
}

HRESULT ENGINE::CGameEvent::Initialize(void)
{
	return S_OK;
}

void ENGINE::CGameEvent::Release(void)
{
	SAFE_DELETE(m_pFunctor);
}

const ENGINE::CGameEvent::CONDITION_VEC* ENGINE::CGameEvent::GetConditions(void)
{
	return &m_ConditionVec;
}

void ENGINE::CGameEvent::AddCondition(const wstring& _strSwitchKey)
{
	m_ConditionVec.push_back(_strSwitchKey);
	CEventManager::GetInstance()->CreateSwitch(_strSwitchKey);
}

ENGINE::CGameEvent::eEventState ENGINE::CGameEvent::GetState(void)
{
	return m_eState;
}

void ENGINE::CGameEvent::Start(void)
{
	m_eState = EVENT_STATE_ING;
}

void ENGINE::CGameEvent::Finish(void)
{
	m_eState = EVENT_STATE_FINISH;
}

void ENGINE::CGameEvent::Reset(void)
{
	m_eState = EVENT_STATE_WAIT;
}
