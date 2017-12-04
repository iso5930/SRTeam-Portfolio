/*!
 * \file Event_Stage_Stage1.h
 * \date 2016/06/22 0:23
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

#ifndef Event_Stage_Stage1_h__
#define Event_Stage_Stage1_h__

#include "SmartText.h"
#include "Export_Function.h"
#include "Talkbox.h"
#include "Character.h"
#include "CharacterGroup.h"


// 씬 진입시 fadein..
class CEvn_FadeinAtStage1 : public ENGINE::CEventFunctor
{
	CPlaneObject* m_pPlane;
	float m_fTime;
	bool m_bMoveOn;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		if (!m_bMoveOn)
		{
			m_bMoveOn = true;
			// 다음 실행할 이벤트를 켠다!
			ENGINE::GetEventManager()->SwitchOn(L"stage1_move_00");
			ENGINE::GetEventManager()->SwitchOn(L"stage1_move_01");
			ENGINE::GetEventManager()->SwitchOn(L"stage1_move_02");
			ENGINE::GetEventManager()->SwitchOn(L"stage1_move_03");
		}
		m_fTime += ENGINE::GetTimeDelta() * 1.f;
		int iAlpha = (int)(255 - 255 * m_fTime);
		//cout << iAlpha << endl;
		if (iAlpha <= 128)
		{
			iAlpha = 128;
			m_fTime = 0.f;
			// 이벤트를 종료시킨다.
			ENGINE::GetEventManager()->SwitchOff(L"FadeinAtStage1");
			_pEvent->Reset();
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeinAtStage1(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeinAtStage1(void) { }
};


// 시작과 동시에 단체 이동..
// sizz..
class CEvn_Move_00 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_pChar->SetSpeed(0.6f);
		m_pChar->SetDestPos(&m_pDest);
		m_pChar->SetStateForEvent(Character_Run);

		float fLength = m_pChar->GetLengthToDest();
		//cout << fLength << endl;
		if (fLength < 0.5f)
		{
			m_pChar->SetStateForEvent(Character_Stand);
			m_pChar->SetSpeed(5.f);

			m_pChar->GetMemento()->clear();

			// 이벤트를 끈다..
			ENGINE::GetEventManager()->SwitchOff(L"stage1_move_00");
			ENGINE::GetEventManager()->SwitchOn(L"stage1_move_00_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Move_00(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Move_00(void) { }
};
// maria..
class CEvn_Move_01 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_pChar->SetSpeed(0.6f);
		m_pChar->SetDestPos(&m_pDest);
		m_pChar->SetStateForEvent(Character_Run);

		float fLength = m_pChar->GetLengthToDest();
		//cout << fLength << endl;
		if (fLength < 0.5f)
		{
			m_pChar->SetStateForEvent(Character_Stand);
			m_pChar->SetSpeed(5.f);

			m_pChar->GetMemento()->clear();

			// 이벤트를 끈다..
			ENGINE::GetEventManager()->SwitchOff(L"stage1_move_01");
			ENGINE::GetEventManager()->SwitchOn(L"stage1_move_01_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Move_01(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Move_01(void) { }
};
// elluard
class CEvn_Move_02 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_pChar->SetSpeed(0.6f);
		m_pChar->SetDestPos(&m_pDest);
		m_pChar->SetStateForEvent(Character_Run);

		float fLength = m_pChar->GetLengthToDest();
		//cout << fLength << endl;
		if (fLength < 0.5f)
		{
			m_pChar->SetStateForEvent(Character_Stand);
			m_pChar->SetSpeed(5.f);

			m_pChar->GetMemento()->clear();

			// 이벤트를 끈다..
			ENGINE::GetEventManager()->SwitchOff(L"stage1_move_02");
			ENGINE::GetEventManager()->SwitchOn(L"stage1_move_02_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Move_02(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Move_02(void) { }
};
// tenzi
class CEvn_Move_03 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_pChar->SetSpeed(0.6f);
		m_pChar->SetDestPos(&m_pDest);
		m_pChar->SetStateForEvent(Character_Run);

		float fLength = m_pChar->GetLengthToDest();
		//cout << fLength << endl;
		if (fLength < 0.5f)
		{
			m_pChar->SetStateForEvent(Character_Stand);
			m_pChar->SetSpeed(5.f);

			m_pChar->GetMemento()->clear();

			// 이벤트를 끈다..
			ENGINE::GetEventManager()->SwitchOff(L"stage1_move_03");
			ENGINE::GetEventManager()->SwitchOn(L"stage1_move_03_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Move_03(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Move_03(void) { }
};

// 대기..
class CEvn_Wait_00 : public ENGINE::CEventFunctor
{
	float m_fTime;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta();
		// 이벤트를 끌 때 받는 입력..
		if (m_fTime > 1.f)
		{
			ENGINE::GetEventManager()->SwitchOff(L"stage1_talk_00");
			ENGINE::GetEventManager()->SwitchOff(L"stage1_move_00_finish");
			ENGINE::GetEventManager()->SwitchOff(L"stage1_move_01_finish");
			ENGINE::GetEventManager()->SwitchOff(L"stage1_move_02_finish");
			ENGINE::GetEventManager()->SwitchOff(L"stage1_move_03_finish");
			_pEvent->Finish();
			m_fTime = 0.f;

			ENGINE::GetEventManager()->SwitchOn(L"stage1_talk_00");
		}
	}
public:
	explicit CEvn_Wait_00(void)
		:m_fTime(0.f) { }
	virtual ~CEvn_Wait_00(void) { }
};


// 대화상자들..
class CEvn_Talk_00 : public ENGINE::CEventFunctor
{
	CTalkbox* m_pTalkbox;
	float m_fTime;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta();
		m_pTalkbox->SetDraw(true);
		// 이벤트를 끌 때 받는 입력..
		if (m_fTime > 1.f && ENGINE::GetInputManager()->IsEventProgressKeyDownNow())
		{
			m_pTalkbox->SetDraw(false);
			ENGINE::GetEventManager()->SwitchOff(L"stage1_talk_00");
			ENGINE::GetEventManager()->SwitchOn(L"stage1_talk_01");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Talk_00(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Talk_00(void) { }
};


class CEvn_Talk_01 : public ENGINE::CEventFunctor
{
	CTalkbox* m_pTalkbox;
	float m_fTime;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta();
		m_pTalkbox->SetDraw(true);
		// 이벤트를 끌 때 받는 입력..
		if (m_fTime > 1.f && ENGINE::GetInputManager()->IsEventProgressKeyDownNow())
		{
			m_pTalkbox->SetDraw(false);
			ENGINE::GetEventManager()->SwitchOff(L"stage1_talk_01");
			ENGINE::GetEventManager()->SwitchOn(L"stage1_talk_02");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Talk_01(CTalkbox* _pTalkbox) :m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Talk_01(void) { }
};


class CEvn_Talk_02 : public ENGINE::CEventFunctor
{
	CTalkbox* m_pTalkbox;
	float m_fTime;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta();
		m_pTalkbox->SetDraw(true);
		// 이벤트를 끌 때 받는 입력..
		if (m_fTime > 1.f && ENGINE::GetInputManager()->IsEventProgressKeyDownNow())
		{
			m_pTalkbox->SetDraw(false);
			ENGINE::GetEventManager()->SwitchOff(L"stage1_talk_02");
			ENGINE::GetEventManager()->SwitchOn(L"stage1_talk_03");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Talk_02(CTalkbox* _pTalkbox) :m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Talk_02(void) { }
};


class CEvn_Talk_03 : public ENGINE::CEventFunctor
{
	CTalkbox* m_pTalkbox;
	float m_fTime;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta();
		m_pTalkbox->SetDraw(true);
		// 이벤트를 끌 때 받는 입력..
		if (m_fTime > 1.f && ENGINE::GetInputManager()->IsEventProgressKeyDownNow())
		{
			m_pTalkbox->SetDraw(false);
			ENGINE::GetEventManager()->SwitchOff(L"stage1_talk_03");
			//ENGINE::GetEventManager()->SwitchOn(L"stage1_talk_04");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Talk_03(CTalkbox* _pTalkbox) :m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Talk_03(void) { }
};


// 마을 입구랑 충돌났을 때,
class CEvn_Talk_04 : public ENGINE::CEventFunctor
{
	CTalkbox* m_pTalkbox;
	float m_fTime;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		if (ENGINE::GetEventManager()->IsSwitchOn(L"stage1_move_04"))
		{
			ENGINE::GetEventManager()->SwitchOff(L"stage1_talk_04");
			return;
		}

		m_fTime += ENGINE::GetTimeDelta();
		m_pTalkbox->SetDraw(true);
		// 이벤트를 끌 때 받는 입력..
		if (m_fTime > 1.f && ENGINE::GetInputManager()->IsEventProgressKeyDownNow())
		{
			m_pTalkbox->SetDraw(false);
			ENGINE::GetEventManager()->SwitchOff(L"stage1_talk_04");
			ENGINE::GetEventManager()->SwitchOn(L"stage1_move_04");
			_pEvent->Reset();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Talk_04(CTalkbox* _pTalkbox) :m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Talk_04(void) { }
};
// 마을 입구랑 충돌났을 때, 연속적으로..
class CEvn_Move_04 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_pChar->SetDestPos(&m_pDest);
		m_pChar->SetStateForEvent(Character_Run);

		float fLength = m_pChar->GetLengthToDest();
		//cout << fLength << endl;
		if (fLength < 0.5f)
		{
			m_pChar->SetStateForEvent(Character_Stand);

			// 이벤트를 끈다..
			ENGINE::GetEventManager()->SwitchOff(L"stage1_move_04");
			_pEvent->Reset();
		}
	}
public:
	explicit CEvn_Move_04(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Move_04(void) { }
};


// 씬 나갈 때..
class CEvn_FadeoutAtStage1 : public ENGINE::CEventFunctor
{
	CPlaneObject* m_pPlane;
	float m_fTime;
	bool m_bMoveOn;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta() * 1.f;
		int iAlpha = (int)(128 * m_fTime) + 128;
		if (iAlpha >= 255)
		{
			iAlpha = 255;
			m_fTime = 0.f;
			// 이벤트를 종료시킨다.
			ENGINE::GetEventManager()->SwitchOff(L"FadeoutAtStage1");
			_pEvent->Reset();
			ENGINE::GetEventManager()->SwitchOn(L"SceneChangeAtMainmenuToStage2");
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeoutAtStage1(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeoutAtStage1(void) { }
};
// 씬 전환할 때..
class CEvn_SceneChangeAtStage1ToStage2 : public ENGINE::CEventFunctor
{
	eSceneID m_eSceneID;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		ENGINE::GetEventManager()->SwitchOff(L"SceneChangeAtMainmenuToStage2");
		_pEvent->Reset();

		HRESULT hr = ENGINE::GetManagement()->ChangeScene(m_eSceneID, CSceneSelector(m_eSceneID));

		ENGINE::CCharacterGroup* pGroup = static_cast<ENGINE::CCharacterGroup*>(ENGINE::GetManagement()->GetGameObject(L"CharacterGroup"));
		pGroup->GetCharacter(CHARACTER_SIZZ)->SetPos(27.5f, 2.f);
		pGroup->GetCharacter(CHARACTER_MARIA)->SetPos(27.5f, 1.9f);
		pGroup->GetCharacter(CHARACTER_ELLUARD)->SetPos(27.5f, 1.8f);
		pGroup->GetCharacter(CHARACTER_TENZI)->SetPos(27.5f, 1.7f);
	}
public:
	explicit CEvn_SceneChangeAtStage1ToStage2(eSceneID _eSceneID)
		:m_eSceneID(_eSceneID) { }
	virtual ~CEvn_SceneChangeAtStage1ToStage2(void) { }
};


#endif // Event_Stage_Stage1_h__