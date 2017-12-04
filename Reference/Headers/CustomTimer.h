/*!
 * \file CustomTimer.h
 * \date 2016/06/09 19:11
 *
 * \author 박정민
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 시간은 알아서 타임매니저가 업데이트 해주니까,
 밖에서 꺼내쓸만한 녀석들은
 reset timer, : 말그대로 타이머를 새로 초기화. 재사용 가능하게 만듬
 check round, : 이걸 가장 자주 쓸꺼임. 1초면 1초, 한바퀴 돌았나 체크해주는 함수.
				한바퀴 지나가면 false뜨니까 매 프레임별로 체크해주는게 맞음.
 get lap count, 시작부터 몇 바퀴나 돌았는지 알려주는 녀석.
 reach lap goal 목표 바퀴 수(예를 들어, 1초씩 5바퀴 설정했다면 그걸 체크해주는 함수)
 정도 뿐! 버그있으면 말해주시길.
*/

#ifndef CustomTimer_h__
#define CustomTimer_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CCustomTimer
{
	// member variable
private:
	float m_fElapsedTime;
	float m_fTimeInterval;
	bool m_bMakeRound;
	DWORD m_dwLapCount;
	DWORD m_dwLapGoal;

	// member function
public:
	static CCustomTimer* Create(float _fTimeInterval, DWORD _dwLapGoal = 0);
	void Update(float _fTimeDelta);
	void ResetTimer(float _fTimeInterval = 0.f, DWORD _dwLapGoal = 0);
private:
	void Initialize(float _fTimeInterval, DWORD _dwLapGoal = 0);

	// getter & setter
public:
	const bool CheckRound(void) const;
	const DWORD GetLapCount(void) const;
	int IsReachLapGoal(void) const;

	// constructor & destructor
private:
	explicit CCustomTimer(void);
public:
	~CCustomTimer(void);
	MAKE_UNCOPYABLE(CCustomTimer)
};
END_NAMESPACE

#endif // CustomTimer_h__