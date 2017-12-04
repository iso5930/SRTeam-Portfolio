/*!
 * \file Event_Stage_Logo.h
 * \date 2016/06/22 0:23
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

#ifndef Event_Stage_Logo_h__
#define Event_Stage_Logo_h__

#include "PlaneObject.h"

// �ش� �÷��� ������Ʈ�ȿ� ����ִ� ��������Ʈ�� ���̵�-�ƿ� ��Ų��!
// �̰� ���� wizard..
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
			// �̺�Ʈ�� �����Ų��.
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
			// �̺�Ʈ�� �����Ų��.
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
			// �̺�Ʈ�� �����Ų��.
			ENGINE::GetEventManager()->SwitchOff(L"LogoFadeout_02");
			_pEvent->Finish();
			m_fTime = 0.f;

			// ���� ������ �̺�Ʈ�� �Ҵ�!
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


// �� ��ȯ�� ��..
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