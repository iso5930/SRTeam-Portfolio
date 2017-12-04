/*!
 * \file Event_Stage_Mainmenu.h
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

#ifndef Event_Stage_Mainmenu_h__
#define Event_Stage_Mainmenu_h__

#include "CharacterGroup.h"
#include "Character.h"

// 해당 플레인 오브젝트안에 들어있는 스프라이트를 페이드-인 시킨다!
class CEvn_FadeinAtMainmenu : public ENGINE::CEventFunctor
{
	CPlaneObject* m_pPlane;
	float m_fTime;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta() * 0.5f;
		int iAlpha = (int)(255 * m_fTime);
		if (iAlpha >= 255)
		{
			m_fTime = 0.f;
			// 이벤트를 종료시킨다.
			ENGINE::GetEventManager()->SwitchOff(L"FadeinAtMainmenu");
			_pEvent->Reset();

			// 다음 실행할 이벤트를 켠다!
			ENGINE::GetEventManager()->SwitchOn(L"ShowMainmenu");
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeinAtMainmenu(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f) { }
	virtual ~CEvn_FadeinAtMainmenu(void) { }
};


//! show menu --
class CEvn_ShowMainmenu : public ENGINE::CEventFunctor
{
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		// 이벤트를 종료시킨다.
		ENGINE::GetEventManager()->SwitchOff(L"ShowMainmenu");
		_pEvent->Reset();

		ENGINE::GetEventManager()->SwitchOn(L"FadeoutAtMainmenu");
	}
public:
	explicit CEvn_ShowMainmenu(void) { }
	virtual ~CEvn_ShowMainmenu(void) { }
};


// 해당 플레인 오브젝트안에 들어있는 스프라이트를 페이드-아웃 시킨다!
class CEvn_FadeoutAtMainmenu : public ENGINE::CEventFunctor
{
	CPlaneObject* m_pPlane;
	float m_fTime;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		m_fTime += ENGINE::GetTimeDelta() * 1.f;
		int iAlpha = (int)(255 - 255 * m_fTime);
		if (iAlpha <= 0)
		{
			m_fTime = 0.f;
			// 이벤트를 종료시킨다.
			ENGINE::GetEventManager()->SwitchOff(L"FadeoutAtMainmenu");
			ENGINE::GetEventManager()->SwitchOff(L"GetEventProgressKey");
			_pEvent->Reset();

			// 다음 실행할 이벤트를 켠다!
			ENGINE::GetEventManager()->SwitchOn(L"SceneChangeAtMainmenuToStage1");
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeoutAtMainmenu(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f) { }
	virtual ~CEvn_FadeoutAtMainmenu(void) { }
};


// 씬 전환할 때..
class CEvn_SceneChangeAtMainmenuToStage1 : public ENGINE::CEventFunctor
{
	eSceneID m_eSceneID;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		ENGINE::GetEventManager()->SwitchOff(L"SceneChangeAtMainmenuToStage1");
		_pEvent->Reset();

		HRESULT hr = ENGINE::GetManagement()->ChangeScene(m_eSceneID, CSceneSelector(m_eSceneID));

		ENGINE::CCharacterGroup* pGroup = static_cast<ENGINE::CCharacterGroup*>(ENGINE::GetManagement()->GetGameObject(L"CharacterGroup"));
		pGroup->GetCharacter(CHARACTER_SIZZ)->SetPos(4.f, 1.1f);
		pGroup->GetCharacter(CHARACTER_MARIA)->SetPos(4.8f, 0.9f);
		pGroup->GetCharacter(CHARACTER_ELLUARD)->SetPos(5.f, 1.6f);
		pGroup->GetCharacter(CHARACTER_TENZI)->SetPos(4.2f, 2.1f);
	}
public:
	explicit CEvn_SceneChangeAtMainmenuToStage1(eSceneID _eSceneID)
		:m_eSceneID(_eSceneID) { }
	virtual ~CEvn_SceneChangeAtMainmenuToStage1(void) { }
};


#endif // Event_Stage_Mainmenu_h__