/*!
 * \file Event_Stage_Logo.h
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

#ifndef Event_Stage_Logo_h__
#define Event_Stage_Logo_h__

#include "PlaneObject.h"

// 해당 플레인 오브젝트안에 들어있는 스프라이트를 페이드-아웃 시킨다!
// 이건 이제 wizard..
class CEvn_LogoFadeout : public ENGINE::CEventFunctor
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
			// 이벤트를 종료시킨다.
			ENGINE::GetEventManager()->SwitchOff(L"LogoFadeout_00");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_LogoFadeout(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f) { }
	virtual ~CEvn_LogoFadeout(void) { }
};

// gravity,.
class CEvn_LogoFadeout_01 : public ENGINE::CEventFunctor
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
			// 이벤트를 종료시킨다.
			ENGINE::GetEventManager()->SwitchOff(L"LogoFadeout_01");
			_pEvent->Finish();
			m_fTime = 0.f;
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_LogoFadeout_01(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f) { }
	virtual ~CEvn_LogoFadeout_01(void) { }
};

// sonnori fadeout..
class CEvn_LogoFadeout_02 : public ENGINE::CEventFunctor
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
			// 이벤트를 종료시킨다.
			ENGINE::GetEventManager()->SwitchOff(L"LogoFadeout_02");
			_pEvent->Finish();
			m_fTime = 0.f;

			// 다음 실행할 이벤트를 켠다!
			ENGINE::GetEventManager()->SwitchOn(L"SceneChangeAtLogoToMainmenu");
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_LogoFadeout_02(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f) { }
	virtual ~CEvn_LogoFadeout_02(void) { }
};


// 씬 전환할 때..
class CEvn_SceneChangeAtLogoToMainmenu : public ENGINE::CEventFunctor
{
	eSceneID m_eSceneID;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		ENGINE::GetEventManager()->SwitchOff(L"SceneChangeAtLogoToMainmenu");
		_pEvent->Reset();

		HRESULT hr = ENGINE::GetManagement()->ChangeScene(m_eSceneID, CSceneSelector(m_eSceneID));
	}
public:
	explicit CEvn_SceneChangeAtLogoToMainmenu(eSceneID _eSceneID)
		:m_eSceneID(_eSceneID) { }
	virtual ~CEvn_SceneChangeAtLogoToMainmenu(void) { }
};

#endif // Event_Stage_Logo_h__