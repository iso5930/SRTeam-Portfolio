#include "CustomTimer.h"

#include "TimeManager.h"

ENGINE::CCustomTimer::CCustomTimer(void)
:m_fElapsedTime(0.f)
,m_fTimeInterval(0.f)
,m_bMakeRound(false)
,m_dwLapCount(0)
,m_dwLapGoal(0)
{

}

ENGINE::CCustomTimer::~CCustomTimer(void)
{

}

ENGINE::CCustomTimer* ENGINE::CCustomTimer::Create(float _fTimeInterval, DWORD _dwLapGoal /*= 0*/)
{
	CCustomTimer* pInstance = new CCustomTimer;
	pInstance->Initialize(_fTimeInterval, _dwLapGoal);

	return pInstance;
}

void ENGINE::CCustomTimer::Update(float _fTimeDelta)
{
	m_bMakeRound = false;

	m_fElapsedTime += _fTimeDelta;
	if (m_fTimeInterval <= m_fElapsedTime)
	{
		++m_dwLapCount;
		m_fElapsedTime = 0;

		m_bMakeRound = true;
	}
}

void ENGINE::CCustomTimer::ResetTimer(float _fTimeInterval /*= 0.f*/, DWORD _dwLapGoal /*= 0*/)
{
	m_fElapsedTime = 0.f;
	if (_fTimeInterval > 0.f)
		m_fTimeInterval = _fTimeInterval;

	m_bMakeRound = false;

	m_dwLapCount = 0;
	if (_dwLapGoal > 0)
		m_dwLapGoal = _dwLapGoal;
}

void ENGINE::CCustomTimer::Initialize(float _fTimeInterval, DWORD _dwLapGoal /*= 0*/)
{
	m_fTimeInterval = _fTimeInterval;
	m_dwLapGoal = _dwLapGoal;
}

const bool ENGINE::CCustomTimer::CheckRound(void) const
{
	return m_bMakeRound;
}

const DWORD ENGINE::CCustomTimer::GetLapCount(void) const
{
	return m_dwLapCount;
}

int ENGINE::CCustomTimer::IsReachLapGoal(void) const
{
	if (m_dwLapCount < m_dwLapGoal)
		return -1;
	else if (m_dwLapCount == m_dwLapGoal)
		return 0;
	else //if (m_dwLapCount > m_dwLapGoal)
		return 1;
}
