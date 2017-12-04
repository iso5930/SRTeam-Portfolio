/*!
 * \file Event_Stage_Stage3.h
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

#ifndef Event_Stage_Stage3_h__
#define Event_Stage_Stage3_h__


// 씬 진입시 fadein..
class CEvn_FadeinAtStage3 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"FadeinAtStage3");
			_pEvent->Reset();
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeinAtStage3(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeinAtStage3(void) { }
};


// 씬 나갈 때.. to stage 2
class CEvn_FadeoutAtStage3ToStage2 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"FadeoutAtStage3ToStage2");
			_pEvent->Reset();
			ENGINE::GetEventManager()->SwitchOn(L"SceneChangeAtStage3ToStage2");
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeoutAtStage3ToStage2(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeoutAtStage3ToStage2(void) { }
};
// 씬 전환할 때..
class CEvn_SceneChangeAtStage3ToStage2 : public ENGINE::CEventFunctor
{
	eSceneID m_eSceneID;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		ENGINE::GetEventManager()->SwitchOff(L"SceneChangeAtStage3ToStage2");
		_pEvent->Reset();

		HRESULT hr = ENGINE::GetManagement()->ChangeScene(m_eSceneID, CSceneSelector(m_eSceneID));

		ENGINE::CCharacterGroup* pGroup = static_cast<ENGINE::CCharacterGroup*>(ENGINE::GetManagement()->GetGameObject(L"CharacterGroup"));
		pGroup->GetCharacter(CHARACTER_SIZZ)->SetPos(9.5f, 21.5f);
		pGroup->GetCharacter(CHARACTER_MARIA)->SetPos(9.5f, 21.6f);
		pGroup->GetCharacter(CHARACTER_ELLUARD)->SetPos(9.5f, 21.7f);
		pGroup->GetCharacter(CHARACTER_TENZI)->SetPos(9.5f, 21.8f);
	}
public:
	explicit CEvn_SceneChangeAtStage3ToStage2(eSceneID _eSceneID)
		:m_eSceneID(_eSceneID) { }
	virtual ~CEvn_SceneChangeAtStage3ToStage2(void) { }
};


// 씬 나갈 때.. to stage 4
class CEvn_FadeoutAtStage3ToStage4 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"FadeoutAtStage3ToStage4");
			_pEvent->Reset();
			ENGINE::GetEventManager()->SwitchOn(L"SceneChangeAtStage3ToStage4");
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeoutAtStage3ToStage4(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeoutAtStage3ToStage4(void) { }
};
// 씬 전환할 때..
class CEvn_SceneChangeAtStage3ToStage4 : public ENGINE::CEventFunctor
{
	eSceneID m_eSceneID;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		ENGINE::GetEventManager()->SwitchOff(L"SceneChangeAtStage3ToStage4");
		_pEvent->Reset();

		HRESULT hr = ENGINE::GetManagement()->ChangeScene(m_eSceneID, CSceneSelector(m_eSceneID));

		ENGINE::CCharacterGroup* pGroup = static_cast<ENGINE::CCharacterGroup*>(ENGINE::GetManagement()->GetGameObject(L"CharacterGroup"));
		pGroup->GetCharacter(CHARACTER_SIZZ)->SetPos(5.f, 2.f);
		pGroup->GetCharacter(CHARACTER_MARIA)->SetPos(5.f, 1.9f);
		pGroup->GetCharacter(CHARACTER_ELLUARD)->SetPos(5.f, 1.8f);
		pGroup->GetCharacter(CHARACTER_TENZI)->SetPos(5.f, 1.7f);
	}
public:
	explicit CEvn_SceneChangeAtStage3ToStage4(eSceneID _eSceneID)
		:m_eSceneID(_eSceneID) { }
	virtual ~CEvn_SceneChangeAtStage3ToStage4(void) { }
};


#endif // Event_Stage_Stage3_h__