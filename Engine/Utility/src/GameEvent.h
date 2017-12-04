/*!
* \file GameEvent.h
* \date 2016/06/20 18:14
*
* \author 박정민
* Contact: user@company.com
*
* \brief 
*
* TODO: long description
*
* \note
*/
// 이벤트 종류.. 를 따로 표시할 필요가 있나? enum?
#ifndef GameEvent_h__
#define GameEvent_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class CEventFunctor;
class ENGINE_DLL_SPECIFIER CGameEvent
{
public:
	//! 이걸 적용해야 한다.. finish면 스위치를 켜든지, 그리고 조건 걸어서 state에 따라 실행되고 말고 결정하도록..
	enum eEventState
	{
		EVENT_STATE_WAIT,
		EVENT_STATE_ING,
		EVENT_STATE_FINISH,
		EVENT_STATE_END
	};
protected:
	typedef wstring SWITCH_KEY;
public:
	typedef vector<SWITCH_KEY> CONDITION_VEC;

	// member variable
protected:
	bool m_bDisposable;
	eEventState m_eState;
	// 이 이벤트를 실행시키기 위해 켜야 하는 스위치들이 들어있다..
	CONDITION_VEC m_ConditionVec;
	CEventFunctor* m_pFunctor;

	// member function
public:
	static CGameEvent* Create(CEventFunctor* _pFunctor, bool _bDisposable = false);
	virtual int Update(void);
protected:
	virtual HRESULT Initialize(void);
	virtual void Release(void);

	// getter & setter
public:
	const CONDITION_VEC* GetConditions(void);
	void AddCondition(const wstring& _strSwitchKey);

	eEventState GetState(void);
	void Start(void);
	void Finish(void);
	void Reset(void);

	bool IsDisposable(void)
	{
		return m_bDisposable;
	}

	// constructor & destructor
protected:
	explicit CGameEvent(CEventFunctor* _pFunctor, bool _bDisposable = false);
public:
	virtual ~CGameEvent(void);
	MAKE_UNCOPYABLE(CGameEvent)
};
END_NAMESPACE

#endif // GameEvent_h__