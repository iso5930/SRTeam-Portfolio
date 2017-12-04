/*!
 * \file Event_Stage_Stage2.h
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

#ifndef Event_Stage_Stage2_h__
#define Event_Stage_Stage2_h__


#include "Inventory.h"
#include "Item.h"

// 씬 진입시 fadein..
class CEvn_FadeinAtStage2 : public ENGINE::CEventFunctor
{
	CPlaneObject* m_pPlane;
	float m_fTime;
	bool m_bMoveOn;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta() * 1.f;
		int iAlpha = (int)(255 - 255 * m_fTime);
		if (iAlpha <= 128)
		{
			iAlpha = 128;
			m_fTime = 0.f;
			// 이벤트를 종료시킨다.
			ENGINE::GetEventManager()->SwitchOff(L"FadeinAtStage2");
			_pEvent->Reset();
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeinAtStage2(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeinAtStage2(void) { }
};


// 씬 나갈 때..
class CEvn_FadeoutAtStage2ToStage1 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"FadeoutAtStage2ToStage1");
			_pEvent->Reset();
			ENGINE::GetEventManager()->SwitchOn(L"SceneChangeAtStage2ToStage1");
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeoutAtStage2ToStage1(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeoutAtStage2ToStage1(void) { }
};
// 씬 전환할 때.. to stage 1
class CEvn_SceneChangeAtStage2ToStage1 : public ENGINE::CEventFunctor
{
	eSceneID m_eSceneID;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		ENGINE::GetEventManager()->SwitchOff(L"SceneChangeAtStage2ToStage1");
		_pEvent->Reset();

		HRESULT hr = ENGINE::GetManagement()->ChangeScene(m_eSceneID, CSceneSelector(m_eSceneID));

		ENGINE::CCharacterGroup* pGroup = static_cast<ENGINE::CCharacterGroup*>(ENGINE::GetManagement()->GetGameObject(L"CharacterGroup"));
		pGroup->GetCharacter(CHARACTER_SIZZ)->SetPos(21.5f, 28.5f);
		pGroup->GetCharacter(CHARACTER_MARIA)->SetPos(21.5f, 28.6f);
		pGroup->GetCharacter(CHARACTER_ELLUARD)->SetPos(21.5f, 28.7f);
		pGroup->GetCharacter(CHARACTER_TENZI)->SetPos(21.5f, 28.8f);
	}
public:
	explicit CEvn_SceneChangeAtStage2ToStage1(eSceneID _eSceneID)
		:m_eSceneID(_eSceneID) { }
	virtual ~CEvn_SceneChangeAtStage2ToStage1(void) { }
};


// 씬 나갈 때..
class CEvn_FadeoutAtStage2ToStage3 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"FadeoutAtStage2ToStage3");
			_pEvent->Reset();
			ENGINE::GetEventManager()->SwitchOn(L"SceneChangeAtStage2ToStage3");
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeoutAtStage2ToStage3(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeoutAtStage2ToStage3(void) { }
};
// 씬 전환할 때.. to stage 3
class CEvn_SceneChangeAtStage2ToStage3 : public ENGINE::CEventFunctor
{
	eSceneID m_eSceneID;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		ENGINE::GetEventManager()->SwitchOff(L"SceneChangeAtStage2ToStage3");
		_pEvent->Reset();

		HRESULT hr = ENGINE::GetManagement()->ChangeScene(m_eSceneID, CSceneSelector(m_eSceneID));

		ENGINE::CCharacterGroup* pGroup = static_cast<ENGINE::CCharacterGroup*>(ENGINE::GetManagement()->GetGameObject(L"CharacterGroup"));
		pGroup->GetCharacter(CHARACTER_SIZZ)->SetPos(28.f, 28.2f);
		pGroup->GetCharacter(CHARACTER_MARIA)->SetPos(28.f, 28.3f);
		pGroup->GetCharacter(CHARACTER_ELLUARD)->SetPos(28.f, 28.4f);
		pGroup->GetCharacter(CHARACTER_TENZI)->SetPos(28.f, 28.5f);
	}
public:
	explicit CEvn_SceneChangeAtStage2ToStage3(eSceneID _eSceneID)
		:m_eSceneID(_eSceneID) { }
	virtual ~CEvn_SceneChangeAtStage2ToStage3(void) { }
};


// 미니 전투 이벤트..
// 대화상자들..
class CEvn_Stage2_Talk_00 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_00");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_01");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_00(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_00(void) { }
};

class CEvn_Stage2_Talk_01 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_01");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_01(CTalkbox* _pTalkbox) :m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_01(void) { }
};
// 소리가 난 곳으로 이동한다..
// sizz..
class CEvn_Stage2_Move_00 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
	bool m_bMoveOn;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		if (!m_bMoveOn)
		{
			m_bMoveOn = true;
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_01");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_02");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_03");
		}
		m_pChar->SetSpeed(1.5f);
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_00");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_00_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Stage2_Move_00(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest), m_bMoveOn(false) { }
	virtual ~CEvn_Stage2_Move_00(void) { }
};
// maria..
class CEvn_Stage2_Move_01 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_pChar->SetSpeed(1.5f);
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_01");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_01_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Stage2_Move_01(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Stage2_Move_01(void) { }
};
// elluard
class CEvn_Stage2_Move_02 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_pChar->SetSpeed(1.5f);
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_02");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_02_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Stage2_Move_02(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Stage2_Move_02(void) { }
};
// tenzi
class CEvn_Stage2_Move_03 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_pChar->SetSpeed(1.5f);
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_03");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_03_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Stage2_Move_03(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Stage2_Move_03(void) { }
};

// 대기..
class CEvn_Stage2_Wait_00 : public ENGINE::CEventFunctor
{
	float m_fTime;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta();
		// 이벤트를 끌 때 받는 입력..
		if (m_fTime > 1.f)
		{
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_00_finish");
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_01_finish");
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_02_finish");
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_03_finish");
			_pEvent->Finish();
			m_fTime = 0.f;

			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_02");
		}
	}
public:
	explicit CEvn_Stage2_Wait_00(void)
		:m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Wait_00(void) { }
};
// 이동 후대화..
// help!
class CEvn_Stage2_Talk_02 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_02");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_03");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_02(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_02(void) { }
};
// 악당 : 
class CEvn_Stage2_Talk_03 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_03");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_04");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_03(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_03(void) { }
};
// 우리편 : 
class CEvn_Stage2_Talk_04 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_04");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_05");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_04(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_04(void) { }
};
class CEvn_Stage2_Talk_05 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_05");
			// 전투로 이어짐?
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_05(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_05(void) { }
};


// 던젼 들어가기 전..
// 자리부터 잡자....
// sizz..
class CEvn_Stage2_Move_04 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
	bool m_bMoveOn;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		if (!m_bMoveOn)
		{
			m_bMoveOn = true;
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_05");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_06");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_07");
		}
		m_pChar->SetSpeed(1.5f);
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_04");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_04_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Stage2_Move_04(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest), m_bMoveOn(false) { }
	virtual ~CEvn_Stage2_Move_04(void) { }
};
// maria..
class CEvn_Stage2_Move_05 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_pChar->SetSpeed(1.5f);
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_05");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_05_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Stage2_Move_05(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Stage2_Move_05(void) { }
};
// elluard
class CEvn_Stage2_Move_06 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_pChar->SetSpeed(1.5f);
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_06");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_06_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Stage2_Move_06(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Stage2_Move_06(void) { }
};
// tenzi
class CEvn_Stage2_Move_07 : public ENGINE::CEventFunctor
{
	ENGINE::CCharacter* m_pChar;
	D3DXVECTOR3 m_pDest;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_pChar->SetSpeed(1.5f);
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_07");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_move_07_finish");
			_pEvent->Finish();
		}
	}
public:
	explicit CEvn_Stage2_Move_07(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Stage2_Move_07(void) { }
};

// 대기..
class CEvn_Stage2_Wait_01 : public ENGINE::CEventFunctor
{
	float m_fTime;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta();
		// 이벤트를 끌 때 받는 입력..
		if (m_fTime > 1.f)
		{
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_04_finish");
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_05_finish");
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_06_finish");
			ENGINE::GetEventManager()->SwitchOff(L"stage2_move_07_finish");
			_pEvent->Finish();
			m_fTime = 0.f;

			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_06");
		}
	}
public:
	explicit CEvn_Stage2_Wait_01(void)
		:m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Wait_01(void) { }
};
// 대화를 하고 입장한다..
class CEvn_Stage2_Talk_06 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_06");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_07");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_06(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_06(void) { }
};
class CEvn_Stage2_Talk_07 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_07");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_08");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_07(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_07(void) { }
};
class CEvn_Stage2_Talk_08 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_08");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_09");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_08(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_08(void) { }
};
class CEvn_Stage2_Talk_09 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_09");
			ENGINE::GetEventManager()->SwitchOn(L"FadeoutAtStage2ToStage3");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_09(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_09(void) { }
};


// npc 구해주는 이벤트..
class CEvn_Stage2_Talk_11 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_11");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_12");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_11(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_11(void) { }
};
class CEvn_Stage2_Talk_12 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_12");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_13");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_12(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_12(void) { }
};
class CEvn_Stage2_Talk_13 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_13");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_talk_14");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_13(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_13(void) { }
};
// 아이템 생성 삽입 시점..
class CEvn_Stage2_Talk_14 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_14");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_npctalk_finish");

			ENGINE::CItem* pItem = new ENGINE::CItem(OBJECT_TYPE_STATIC);
			pItem->m_iNum = 5;
			pItem->m_bFree = false;
			pItem->m_eID = CHARACTER_END;
			pItem->m_iType = TYPE_EXPENDABLES;
			pItem->m_iImgCode = 23;
			wsprintf(pItem->m_szName, L"건빵");
			pItem->m_iItemCode = 99989;
			pItem->m_bCursorOn = false;
			pItem->m_bSelect = false;
			ENGINE::CInventory* pInven = static_cast<ENGINE::CInventory*>(ENGINE::GetManagement()->GetGameObject(L"Inventory"));
			//cout << pInven << endl;
			pInven->GetvecInven()->push_back(pItem);
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_14(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_14(void) { }
};
class CEvn_Stage2_Talk_15 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_15");
			//ENGINE::GetEventManager()->SwitchOn(L"stage2_npctalk_finish");
			_pEvent->Reset();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_15(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_15(void) { }
};


// 이건 이제 보물상자..
class CEvn_Stage2_Talk_21 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_21");
			ENGINE::GetEventManager()->SwitchOn(L"stage2_box_open");

			ENGINE::CItem* pItem = new ENGINE::CItem(OBJECT_TYPE_STATIC);
			pItem->m_iNum = 1;
			pItem->m_bFree = false;
			pItem->m_eID = CHARACTER_END;
			pItem->m_iType = TYPE_EXPENDABLES;
			pItem->m_iImgCode = 22;
			wsprintf(pItem->m_szName, L"포도주");
			pItem->m_iItemCode = 22232;
			pItem->m_bCursorOn = false;
			pItem->m_bSelect = false;
			ENGINE::CInventory* pInven = static_cast<ENGINE::CInventory*>(ENGINE::GetManagement()->GetGameObject(L"Inventory"));
			//cout << pInven << endl;
			pInven->GetvecInven()->push_back(pItem);
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_21(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_21(void) { }
};
class CEvn_Stage2_Talk_22 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage2_talk_22");
			//ENGINE::GetEventManager()->SwitchOn(L"stage2_npctalk_finish");
			_pEvent->Reset();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage2_Talk_22(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage2_Talk_22(void) { }
};


#endif // Event_Stage_Stage2_h__