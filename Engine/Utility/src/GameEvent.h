/*!
* \file GameEvent.h
* \date 2016/06/20 18:14
*
* \author ������
* Contact: user@company.com
*
* \brief 
*
* TODO: long description
*
* \note
*/
// �̺�Ʈ ����.. �� ���� ǥ���� �ʿ䰡 �ֳ�? enum?
#ifndef GameEvent_h__
#define GameEvent_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class CEventFunctor;
class ENGINE_DLL_SPECIFIER CGameEvent
{
public:
	//! �̰� �����ؾ� �Ѵ�.. finish�� ����ġ�� �ѵ���, �׸��� ���� �ɾ state�� ���� ����ǰ� ���� �����ϵ���..
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
	// �� �̺�Ʈ�� �����Ű�� ���� �Ѿ� �ϴ� ����ġ���� ����ִ�..
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