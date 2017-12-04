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
	// ���� �ð�(�� �ش��ϴ� ī���� ��)�� �켱 ��������..
	QueryPerformanceCounter(&m_CurrentCount);

	// frequency == ������, 1�� ���� �ö󰡴� count��
	// ����� 1�ʸ���, frequency�� ������ �ִ��� üũ�ϴ� �ڵ�
	if (m_CurrentCount.QuadPart - m_LastSecondCount.QuadPart > m_Frequency.QuadPart)
	{
		QueryPerformanceFrequency(&m_Frequency);
		m_LastSecondCount.QuadPart = m_CurrentCount.QuadPart;
	}

	// set time�� frame�� �ѹ��� �� ������ ����ȴ�..
	// �׷��ϱ� �� �������� ������ frame�� ����Ǿ��� �� �󸶳� �ð��� �������� �� �� �ִ�.
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

// �� ���� ��� ���� �Ǵ���..
// ex) ĳ���Ͱ� 1�ʵ��� 10m�� �̵��ؾ� �Ѵٰ� ��������,
// GetTimeDelta()�� �����ؼ� ���Ϲ޴� ���� ������ üũ����Ʈ(set time ȣ�� ����)���κ���
// 0.xxxx�ʰ� �����ٴ� ��, �ٷ� �� ����.
// �׷��ϱ� GetTimeDelta()�� �����ָ� �̹� �����ӿ��� 10 * 0.xxxx ���͸�ŭ �̵��ϰ���..
// �װ� �����Ӻ��� ���̰� ���̸�,
// 100�������̵� 5000�������̵� ĳ���ʹ� ȭ�� ������ 1�ʵ��� 10m���� �����̰� �ȴ�, �� ����
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
