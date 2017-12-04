/*!
 * \file CustomTimer.h
 * \date 2016/06/09 19:11
 *
 * \author ������
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 �ð��� �˾Ƽ� Ÿ�ӸŴ����� ������Ʈ ���ִϱ�,
 �ۿ��� ���������� �༮����
 reset timer, : ���״�� Ÿ�̸Ӹ� ���� �ʱ�ȭ. ���� �����ϰ� ����
 check round, : �̰� ���� ���� ������. 1�ʸ� 1��, �ѹ��� ���ҳ� üũ���ִ� �Լ�.
				�ѹ��� �������� false�ߴϱ� �� �����Ӻ��� üũ���ִ°� ����.
 get lap count, ���ۺ��� �� ������ ���Ҵ��� �˷��ִ� �༮.
 reach lap goal ��ǥ ���� ��(���� ���, 1�ʾ� 5���� �����ߴٸ� �װ� üũ���ִ� �Լ�)
 ���� ��! ���������� �����ֽñ�.
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