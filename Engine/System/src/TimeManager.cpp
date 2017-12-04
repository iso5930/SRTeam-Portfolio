#include "TimeManager.h"

#include "CustomTimer.h"

IMPLEMENT_SINGLETON(ENGINE::CTimeManager)

ENGINE::CTimeManager::CTimeManager(void)
:m_fTimeDelta(0.f)
{

}

ENGINE::CTimeManager::~CTimeManager(void)
{
	Release();
}

void ENGINE::CTimeManager::InitTime(void)
{
	QueryPerformanceCounter(&m_CurrentCount);
	QueryPerformanceCounter(&m_LastFrameCount);
	QueryPerformanceCounter(&m_LastSecondCount);
	QueryPerformanceFrequency(&m_Frequency);
}

void ENGINE::CTimeManager::SetTime(void)
{
	// 현재 시간(에 해당하는 카운터 값)을 우선 가져오고..
	QueryPerformanceCounter(&m_CurrentCount);

	// frequency == 진동수, 1초 동안 올라가는 count값
	// 여기는 1초마다, frequency에 변동이 있는지 체크하는 코드
	if (m_CurrentCount.QuadPart - m_LastSecondCount.QuadPart > m_Frequency.QuadPart)
	{
		QueryPerformanceFrequency(&m_Frequency);
		m_LastSecondCount.QuadPart = m_CurrentCount.QuadPart;
	}

	// set time은 frame이 한바퀴 돌 때마다 실행된다..
	// 그러니까 이 시점에서 지난번 frame이 실행되었을 때 얼마나 시간이 지났는지 알 수 있다.
	m_fTimeDelta =
		float(m_CurrentCount.QuadPart - m_LastFrameCount.QuadPart) / m_Frequency.QuadPart;
	m_LastFrameCount = m_CurrentCount;

	TIMER_MAP::iterator iter = m_TimerMap.begin();
	TIMER_MAP::iterator iter_end = m_TimerMap.end();
	for (; iter != iter_end; ++iter)
	{
		iter->second->Update(m_fTimeDelta);
	}
}

void ENGINE::CTimeManager::CreateTimer(const wstring& _strTimerKey, float _fTimeInterval, DWORD _dwMaxLapCount /*= 0*/)
{
	CCustomTimer* pTimer = CCustomTimer::Create(_fTimeInterval, _dwMaxLapCount);

	m_TimerMap.insert(TIMER_MAP::value_type(_strTimerKey, pTimer));
}

void ENGINE::CTimeManager::ReleaseTimer(const wstring& _strTimerKey)
{
	TIMER_MAP::iterator iter = m_TimerMap.find(_strTimerKey);
	if (iter != m_TimerMap.end())
	{
		SAFE_DELETE(iter->second);

		m_TimerMap.erase(iter);
	}
}

// 이 값을 어떻게 쓰면 되느냐..
// ex) 캐릭터가 1초동안 10m를 이동해야 한다고 가정하자,
// GetTimeDelta()을 실행해서 리턴받는 값은 지난번 체크포인트(set time 호출 시점)으로부터
// 0.xxxx초가 지났다는 뜻, 바로 그 숫자.
// 그러니까 GetTimeDelta()을 곱해주면 이번 프레임에는 10 * 0.xxxx 미터만큼 이동하겠지..
// 그게 프레임별로 쌓이고 쌓이면,
// 100프레임이든 5000프레임이든 캐릭터는 화면 위에서 1초동안 10m만을 움직이게 된다, 는 원리
const float ENGINE::CTimeManager::GetTimeDelta(void) const
{
	return m_fTimeDelta;
}

const ENGINE::CCustomTimer* ENGINE::CTimeManager::GetTimer(const wstring& _strTimerKey)
{
	TIMER_MAP::iterator iter = m_TimerMap.find(_strTimerKey);
	if (iter != m_TimerMap.end())
	{
		return iter->second;
	}

	return NULL;
}

void ENGINE::CTimeManager::Release()
{
	TIMER_MAP::iterator iter = m_TimerMap.begin();
	TIMER_MAP::iterator iter_end = m_TimerMap.end();
	for (; iter != iter_end; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_TimerMap.clear();
}
