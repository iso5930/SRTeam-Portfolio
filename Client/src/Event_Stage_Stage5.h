/*!
 * \file Event_Stage_Stage5.h
 * \date 2016/06/22 0:24
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

#ifndef Event_Stage_Stage5_h__
#define Event_Stage_Stage5_h__


// 씬 진입시 fadein..
class CEvn_FadeinAtStage5 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"FadeinAtStage5");
			_pEvent->Reset();
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeinAtStage5(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeinAtStage5(void) { }
};


// 씬 나갈 때.. to stage 4
class CEvn_FadeoutAtStage5ToStage4 : public ENGINE::CEventFunctor
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
			ENGINE::GetEventManager()->SwitchOff(L"FadeoutAtStage5ToStage4");
			_pEvent->Reset();
			ENGINE::GetEventManager()->SwitchOn(L"SceneChangeAtStage5ToStage4");
		}
		DWORD dwColor = D3DCOLOR_ARGB(iAlpha, 255, 255, 255);
		m_pPlane->SetColor(dwColor);
	}
public:
	explicit CEvn_FadeoutAtStage5ToStage4(CPlaneObject* _pPlane)
		:m_pPlane(_pPlane), m_fTime(0.f), m_bMoveOn(false) { }
	virtual ~CEvn_FadeoutAtStage5ToStage4(void) { }
};
// 씬 전환할 때..
class CEvn_SceneChangeAtStage5ToStage4 : public ENGINE::CEventFunctor
{
	eSceneID m_eSceneID;
public:
	virtual void operator ()(ENGINE::CGameEvent* _pEvent)
	{
		ENGINE::GetEventManager()->SwitchOff(L"SceneChangeAtStage5ToStage4");
		_pEvent->Reset();

		HRESULT hr = ENGINE::GetManagement()->ChangeScene(m_eSceneID, CSceneSelector(m_eSceneID));

		ENGINE::CCharacterGroup* pGroup = static_cast<ENGINE::CCharacterGroup*>(ENGINE::GetManagement()->GetGameObject(L"CharacterGroup"));
		pGroup->GetCharacter(CHARACTER_SIZZ)->SetPos(3.f, 28.f);
		pGroup->GetCharacter(CHARACTER_MARIA)->SetPos(3.f, 28.1f);
		pGroup->GetCharacter(CHARACTER_ELLUARD)->SetPos(3.f, 28.2f);
		pGroup->GetCharacter(CHARACTER_TENZI)->SetPos(3.f, 28.3f);
	}
public:
	explicit CEvn_SceneChangeAtStage5ToStage4(eSceneID _eSceneID)
		:m_eSceneID(_eSceneID) { }
	virtual ~CEvn_SceneChangeAtStage5ToStage4(void) { }
};


#endif // Event_Stage_Stage5_h__