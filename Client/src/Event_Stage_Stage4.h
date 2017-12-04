/*!
 * \file Event_Stage_Stage4.h
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

#ifndef Event_Stage_Stage4_h__
#define Event_Stage_Stage4_h__


// 씬 진입시 fadein..
class CEvn_FadeinAtStage4 : public ENGINE::CEventFunctor
{
	CPlaneObject* m_pPlane;
	float m_fTime;
	bool m_bMoveOn;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta() * 1.f;
		int iAlpha = (int)(255 - 255 * m_fTime);
		if (iAlpha <= 0)
		{
			iAlpha = 0;
			m_fTime = 0.f;
			// 이벤트를 종료시킨다.
			ENGINE::GetEventManager()->SwitchOff(L"FadeinAtStage4");
			_pEvent->Reset();
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeinAtStage4(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeinAtStage4(void) { }
};


// 씬 나갈 때.. to stage 3
class CEvn_FadeoutAtStage4ToStage3 : public ENGINE::CEventFunctor
{
	CPlaneObject* m_pPlane;
	float m_fTime;
	bool m_bMoveOn;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta() * 1.f;
		int iAlpha = (int)(255 * m_fTime);
		if (iAlpha >= 255)
		{
			iAlpha = 255;
			m_fTime = 0.f;
			// 이벤트를 종료시킨다.
			ENGINE::GetEventManager()->SwitchOff(L"FadeoutAtStage4ToStage3");
			_pEvent->Reset();
			ENGINE::GetEventManager()->SwitchOn(L"SceneChangeAtStage4ToStage3");
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeoutAtStage4ToStage3(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeoutAtStage4ToStage3(void) { }
};
// 씬 전환할 때..
class CEvn_SceneChangeAtStage4ToStage3 : public ENGINE::CEventFunctor
{
	eSceneID m_eSceneID;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		ENGINE::GetEventManager()->SwitchOff(L"SceneChangeAtStage4ToStage3");
		_pEvent->Reset();

		HRESULT hr = ENGINE::GetManagement()->ChangeScene(m_eSceneID, CSceneSelector(m_eSceneID));

		ENGINE::CCharacterGroup* pGroup = static_cast<ENGINE::CCharacterGroup*>(ENGINE::GetManagement()->GetGameObject(L"CharacterGroup"));
		pGroup->GetCharacter(CHARACTER_SIZZ)->SetPos(4.5f, 2.f);
		pGroup->GetCharacter(CHARACTER_MARIA)->SetPos(4.5f, 2.1f);
		pGroup->GetCharacter(CHARACTER_ELLUARD)->SetPos(4.5f, 2.2f);
		pGroup->GetCharacter(CHARACTER_TENZI)->SetPos(4.5f, 2.3f);
	}
public:
	explicit CEvn_SceneChangeAtStage4ToStage3(eSceneID _eSceneID)
		:m_eSceneID(_eSceneID) { }
	virtual ~CEvn_SceneChangeAtStage4ToStage3(void) { }
};


// 씬 나갈 때.. to stage 5
class CEvn_FadeoutAtStage4ToStage5 : public ENGINE::CEventFunctor
{
	CPlaneObject* m_pPlane;
	float m_fTime;
	bool m_bMoveOn;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta() * 1.f;
		int iAlpha = (int)(255 * m_fTime);
		if (iAlpha >= 255)
		{
			iAlpha = 255;
			m_fTime = 0.f;
			// 이벤트를 종료시킨다.
			ENGINE::GetEventManager()->SwitchOff(L"FadeoutAtStage4ToStage5");
			_pEvent->Reset();
			ENGINE::GetEventManager()->SwitchOn(L"SceneChangeAtStage4ToStage5");
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeoutAtStage4ToStage5(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeoutAtStage4ToStage5(void) { }
};
// 씬 전환할 때..
class CEvn_SceneChangeAtStage4ToStage5 : public ENGINE::CEventFunctor
{
	eSceneID m_eSceneID;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		ENGINE::GetEventManager()->SwitchOff(L"SceneChangeAtStage4ToStage5");
		_pEvent->Reset();

		HRESULT hr = ENGINE::GetManagement()->ChangeScene(m_eSceneID, CSceneSelector(m_eSceneID));

		ENGINE::CCharacterGroup* pGroup = static_cast<ENGINE::CCharacterGroup*>(ENGINE::GetManagement()->GetGameObject(L"CharacterGroup"));
		pGroup->GetCharacter(CHARACTER_SIZZ)->SetPos(35.5f, 2.f);
		pGroup->GetCharacter(CHARACTER_MARIA)->SetPos(35.5f, 1.9f);
		pGroup->GetCharacter(CHARACTER_ELLUARD)->SetPos(35.5f, 1.8f);
		pGroup->GetCharacter(CHARACTER_TENZI)->SetPos(35.5f, 1.7f);
	}
public:
	explicit CEvn_SceneChangeAtStage4ToStage5(eSceneID _eSceneID)
		:m_eSceneID(_eSceneID) { }
	virtual ~CEvn_SceneChangeAtStage4ToStage5(void) { }
};



// scene4로 옮겨야 할 것들..
// 봉인과의 충돌..
class CEvn_Talk_91 : public ENGINE::CEventFunctor
{
	CTalkbox* m_pTalkbox;
	float m_fTime;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		if (ENGINE::GetEventManager()->IsSwitchOn(L"stage4_move_91"))
		{
			ENGINE::GetEventManager()->SwitchOff(L"stage4_talk_91");
			return;
		}

		m_fTime += ENGINE::GetTimeDelta();
		m_pTalkbox->SetDraw(true);
		// 이벤트를 끌 때 받는 입력..
		if (m_fTime > 1.f && ENGINE::GetInputManager()->IsEventProgressKeyDownNow())
		{
			m_pTalkbox->SetDraw(false);
			ENGINE::GetEventManager()->SwitchOff(L"stage4_talk_91");
			ENGINE::GetEventManager()->SwitchOn(L"stage4_move_91");
			_pEvent->Reset();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Talk_91(CTalkbox* _pTalkbox) :m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Talk_91(void) { }
};
// 봉인과의 충돌.. 연속적으로..
class CEvn_Move_91 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage4_move_91");
			_pEvent->Reset();
		}
	}
public:
	explicit CEvn_Move_91(ENGINE::CCharacter* pChar, D3DXVECTOR3& pDest) :m_pChar(pChar), m_pDest(pDest) { }
	virtual ~CEvn_Move_91(void) { }
};
// 스위치1과의 충돌..
class CEvn_Talk_92 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage4_talk_92");
			ENGINE::GetEventManager()->SwitchOn(L"Stage4Switch1on");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Talk_92(CTalkbox* _pTalkbox) :m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Talk_92(void) { }
};
// 스위치1과의 충돌..
class CEvn_Talk_93 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage4_talk_93");
			ENGINE::GetEventManager()->SwitchOn(L"Stage4Switch2on");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Talk_93(CTalkbox* _pTalkbox) :m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Talk_93(void) { }
};
// 스위치1과의 충돌..
class CEvn_Talk_94 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage4_talk_94");
			ENGINE::GetEventManager()->SwitchOn(L"Stage4Switch3on");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Talk_94(CTalkbox* _pTalkbox) :m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Talk_94(void) { }
};
// 스위치 다 껐을때..
class CEvn_Unseal : public ENGINE::CEventFunctor
{
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		ENGINE::GetEventManager()->SwitchOff(L"Stage4Switch1on");
		ENGINE::GetEventManager()->SwitchOff(L"Stage4Switch2on");
		ENGINE::GetEventManager()->SwitchOff(L"Stage4Switch3on");
		_pEvent->Finish();

		ENGINE::GetEventManager()->SwitchOn(L"Stage4Unseal");
	}
public:
	explicit CEvn_Unseal(void) { }
	virtual ~CEvn_Unseal(void) { }
};


// 상자 A
class CEvn_Stage4_Talk_11 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage4_talk_11");
			ENGINE::GetEventManager()->SwitchOn(L"stage4_box_a_open");

			ENGINE::CItem* pItem = new ENGINE::CItem(OBJECT_TYPE_STATIC);
			pItem->m_iNum = 1;
			pItem->m_bFree = false;
			pItem->m_eID = CHARACTER_END;
			pItem->m_iType = TYPE_EXPENDABLES;
			pItem->m_iImgCode = 0;
			wsprintf(pItem->m_szName, L"건빵");
			pItem->m_iItemCode = 44110;
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
	explicit CEvn_Stage4_Talk_11(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage4_Talk_11(void) { }
};
class CEvn_Stage4_Talk_12 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage4_talk_12");
			//ENGINE::GetEventManager()->SwitchOn(L"stage2_npctalk_finish");
			_pEvent->Reset();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage4_Talk_12(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage4_Talk_12(void) { }
};

// 상자 B
class CEvn_Stage4_Talk_21 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage4_talk_21");
			ENGINE::GetEventManager()->SwitchOn(L"stage4_box_b_open");

			ENGINE::CItem* pItem = new ENGINE::CItem(OBJECT_TYPE_STATIC);
			pItem->m_iNum = 1;
			pItem->m_bFree = false;
			pItem->m_eID = CHARACTER_END;
			pItem->m_iType = TYPE_EXPENDABLES;
			pItem->m_iImgCode = 0;
			wsprintf(pItem->m_szName, L"건빵");
			pItem->m_iItemCode = 44110;
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
	explicit CEvn_Stage4_Talk_21(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage4_Talk_21(void) { }
};
class CEvn_Stage4_Talk_22 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"stage4_talk_22");
			//ENGINE::GetEventManager()->SwitchOn(L"stage2_npctalk_finish");
			_pEvent->Reset();
			m_fTime = 0.f;
		}
	}
public:
	explicit CEvn_Stage4_Talk_22(CTalkbox* _pTalkbox)
		:m_pTalkbox(_pTalkbox), m_fTime(0.f) { }
	virtual ~CEvn_Stage4_Talk_22(void) { }
};


#endif // Event_Stage_Stage4_h__