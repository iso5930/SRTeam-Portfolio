#include "SubPage.h"

#include "Export_Function.h"

#include "MainUIObserver.h"
#include "GroupObserver.h"
#include "Button.h"
#include "CharacterGroup.h"

ENGINE::CSubPage::CSubPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
:CPage(_pOwner, pSprite), m_iCharCur(0), m_eCharCur(CHARACTER_END), m_iMainUICur(0)
{

}

ENGINE::CSubPage::~CSubPage(void)
{
	Release();
}

ENGINE::CSubPage* ENGINE::CSubPage::Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
{
	CSubPage* pPage = new CSubPage(_pOwner, pSprite);

	if(FAILED(pPage->Init()))
	{
		SAFE_DELETE(pPage);
	}

	return pPage;
}

int ENGINE::CSubPage::Update(void)
{
	m_iMainUICur = m_pObserver->GetLeftIndex();

	switch(m_iMainUICur)
	{
	case MENU_CHARACTER:
		CharUpdate();
		break;

	case MENU_DIARY:
		DiaryUpdate();
		break;
	}

	return 0;
}

void ENGINE::CSubPage::Render(void)
{
	switch(m_iMainUICur)
	{
	case MENU_CHARACTER:
		CharRender();
		break;

	case MENU_DIARY:
		DiaryRender();
		break;
	}
}

HRESULT ENGINE::CSubPage::Init(void)
{
	m_vecCharID.push_back(CHARACTER_SIZZ);
	m_vecCharID.push_back(CHARACTER_MARIA);
	m_vecCharID.push_back(CHARACTER_ELLUARD);
	m_vecCharID.push_back(CHARACTER_TENZI);

	m_eCharCur = m_vecCharID[m_iCharCur];

	m_pObserver = CMainUIObserver::Create(m_pOwner);
	ENGINE::GetInfoSubject()->Subscribe(m_pObserver);

	ENGINE::GetInfoSubject()->AddData(MESSAGE_SUBUI, &m_eCharCur);

	m_pCharObserver = CGroupObserver::Create(m_pOwner);
	ENGINE::GetInfoSubject()->Subscribe(m_pCharObserver);

	float fX = 149.f;
	float fY = 127.f;
	float fCX = 53.f;
	float fCY = 53.f;

	D3DXVECTOR3 vPos;

	vPos.x = fX;
	vPos.y = 0.f;
	vPos.z = 0.f;

	for(size_t i = 0; i< m_vecCharID.size(); ++i)
	{
		fY = 127.f + (i * 52.f);
		vPos.y = fY;
		
		CButton* pButton = CButton::Create(m_pOwner, vPos, fCX, fCY);

		m_vecButton.push_back(pButton);
	}

	return S_OK;
}

void ENGINE::CSubPage::Release(void)
{
	SAFE_DELETE(m_pObserver);
	SAFE_DELETE(m_pCharObserver);

	for(size_t i = 0; i < m_vecButton.size(); ++i)
	{
		SAFE_DELETE(m_vecButton[i]);
	}
	m_vecButton.clear();
}
void ENGINE::CSubPage::CharUpdate(void)
{
	if(ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
	{
		if(m_bMessageBox)
		{
			D3DXVECTOR3 vMessagePos = m_vMessagePos;

			vMessagePos.x += 57 + 20;
			vMessagePos.y += 11 + 16;
			//이때 메세지 박스와 충돌 처리..
			RECT rcMessage1;

			rcMessage1.left = long(vMessagePos.x - 57);
			rcMessage1.right = long(vMessagePos.x + 57);
			rcMessage1.top = long(vMessagePos.y - 11);
			rcMessage1.bottom = long(vMessagePos.y + 11);
	
			if(PtInRect(&rcMessage1, m_ptMouse))
			{
				if(m_iCharCur == 0)
				{
					m_bMessageBox = false;
					return;
				}

				eCharacterID eTemp = m_vecCharID[m_iCharCur];
				m_vecCharID[m_iCharCur] = m_vecCharID[m_iCharCur - 1];
				m_vecCharID[m_iCharCur - 1] = eTemp;

				m_iCharCur = 0;
				m_eCharCur = m_vecCharID[0];
				ENGINE::GetInfoSubject()->Notify(MESSAGE_SUBUI);	

				dynamic_cast<CGroupObserver*>(m_pCharObserver)->GetCharacterGroup()->GroupSort(&m_vecCharID);
			}
			else
			{
				rcMessage1.top += 22;
				rcMessage1.bottom += 22;

				if(PtInRect(&rcMessage1, m_ptMouse))
				{
					//2번 메세지 충돌
					if(m_iCharCur == m_vecCharID.size() - 1)
					{
						m_bMessageBox = false;
						return;
					}

					eCharacterID eTemp = m_vecCharID[m_iCharCur];
					m_vecCharID[m_iCharCur] = m_vecCharID[m_iCharCur + 1];
					m_vecCharID[m_iCharCur + 1] = eTemp;

					m_iCharCur = 0;
					m_eCharCur = m_vecCharID[0];
					ENGINE::GetInfoSubject()->Notify(MESSAGE_SUBUI);	

					dynamic_cast<CGroupObserver*>(m_pCharObserver)->GetCharacterGroup()->GroupSort(&m_vecCharID);
				}
			}
		}

		m_bMessageBox = false;

		for(size_t i = 0; i < m_vecButton.size(); ++i)
		{
			m_vecButton[i]->SetMousePos(m_ptMouse);

			if(m_vecButton[i]->Update() == 1)
			{
				m_iCharCur = i;
				m_eCharCur = m_vecCharID[m_iCharCur];
				ENGINE::GetInfoSubject()->Notify(MESSAGE_SUBUI);

				break;
			}
		}
	}

	if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_RBUTTON))
	{
		for(size_t i = 0; i < m_vecButton.size(); ++i)
		{
			m_vecButton[i]->SetMousePos(m_ptMouse);

			if(m_vecButton[i]->Update() == 1)
			{
				if(m_bMessageBox)
				{
					m_bMessageBox = false;
				}
				else
				{
					m_bMessageBox = true;
					m_vMessagePos.x = (float)m_ptMouse.x;
					m_vMessagePos.y = (float)m_ptMouse.y;

					m_iCharCur = i;
					m_eCharCur = m_vecCharID[m_iCharCur];
					ENGINE::GetInfoSubject()->Notify(MESSAGE_SUBUI);
				}
			}
		}
	}
}

void ENGINE::CSubPage::DiaryUpdate(void)
{

}

void ENGINE::CSubPage::CharRender(void)
{
	CPage::DrawSprite(RESOURCE_TYPE_STATIC, L"CharIconSubMenuCur", 149.f, 127.f + (m_iCharCur * 52.f), m_vecCharID[m_iCharCur], NULL);
	//현재 선택한 캐릭터 아이콘
	CPage::DrawSprite(RESOURCE_TYPE_STATIC, L"OKButton", 122.f, 127.f + (m_iCharCur * 52.f), 0, NULL);
	//OK 이미지

	for(size_t i = 0; i < m_vecCharID.size(); ++i)
	{
		if(m_iCharCur == i)
		{
			continue;
		}

		CPage::DrawSprite(RESOURCE_TYPE_STATIC, L"CharIconSubMenuDefault", 149.f, 127.f + (i * 52.f), m_vecCharID[i], NULL);
	}
	//비활성화된 캐릭터 이미지

	for(size_t i = 0; i < m_vecCharID.size(); ++i)
	{
		char szName[20] = "";

		switch(m_vecCharID[i])
		{
		case CHARACTER_SIZZ:
			strcpy_s(szName, sizeof(char) * 20, "sizz");
			break;

		case CHARACTER_MARIA:
			strcpy_s(szName, sizeof(char) * 20, "maria");
			break;

		case CHARACTER_ELLUARD:
			strcpy_s(szName, sizeof(char) * 20, "elluard");
			break;

		case CHARACTER_TENZI:
			strcpy_s(szName, sizeof(char) * 20, "tenzi");
			break;
		}

		int iLength = strlen(szName);

		float fX = 190 - (iLength * 8.f);

		CPage::DrawFont(szName, fX, 147 + ((float)i * 52.f), 8.f, 0.f);
	}

	if(m_bMessageBox)
	{
		DrawSprite(RESOURCE_TYPE_STATIC, L"MessageBox", m_vMessagePos.x + 80, m_vMessagePos.y + 30, 0, NULL);

		if(m_iCharCur != 0)
		{
			CPage::DrawText(L"위로 올리기", D3DCOLOR_ARGB(255, 0, 0, 0), m_vMessagePos.x + 20, m_vMessagePos.y + 16);
		}
		else
			CPage::DrawText(L"위로 올리기", D3DCOLOR_ARGB(255, 255, 0, 0), m_vMessagePos.x + 20, m_vMessagePos.y + 16);
		
		if(m_iCharCur != m_vecCharID.size() - 1)
		{
			CPage::DrawText(L"아래로 내리기", D3DCOLOR_ARGB(255, 0, 0, 0), m_vMessagePos.x  + 20, m_vMessagePos.y + 37);
		}
		else
			CPage::DrawText(L"아래로 내리기", D3DCOLOR_ARGB(255, 255, 0, 0), m_vMessagePos.x  + 20, m_vMessagePos.y + 37);
	}
}

void ENGINE::CSubPage::DiaryRender(void)
{

}