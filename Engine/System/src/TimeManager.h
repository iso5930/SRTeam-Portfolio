/*!
 * \file TimeManager.h
 * \date 2016/06/01 21:46
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef TimeManager_h__
#define TimeManager_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class CCustomTimer;
class ENGINE_DLL_SPECIFIER CTimeManager
{
	DECLARE_SINGLETON(CTimeManager)

private:
	typedef map<wstring, CCustomTimer*> TIMER_MAP;

	// member variable
private:
	LARGE_INTEGER m_CurrentCount;
	LARGE_INTEGER m_LastFrameCount;
	LARGE_INTEGER m_LastSecondCount;
	LARGE_INTEGER m_Frequency;
	float m_fTimeDelta;

	TIMER_MAP m_TimerMap;

	// member function
public:
	void InitTime(void);
	void SetTime(void);

	void CreateTimer(const wstring& _strTimerKey,
					 float _fTimeInterval,
					 DWORD _dwMaxLapCount = 0);
	void ReleaseTimer(const wstring& _strTimerKey);
private:
	void Release();

	// getter & setter
public:
	const float GetTimeDelta(void) const;
	const CCustomTimer* GetTimer(const wstring& _strTimerKey);

	// constructor & destructor
private:
	explicit CTimeManager(void);
	~CTimeManager(void);
};
END_NAMESPACE

#endif // TimeManager_h__