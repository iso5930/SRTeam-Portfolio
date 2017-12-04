#include "stdafx.h"
#include "MainMenu.h"
#include "GraphicDevice.h"
#include "Page.h"
#include "Button.h"
#include "CharacterStatePage.h"
#include "CharacterItemPage.h"
#include "CharacterEquipPage.h"
#include "CharacterMagicPage.h"
#include "CharacterSkillPage.h"
#include "DiaryItemPage.h"
#include "DiaryMonsterPage.h"
#include "DiaryScrapPage.h"
#include "TacticsPage.h"
#include "SubPage.h"
#include "ResourceManager.h"
#include "CharacterGroup.h"
#include "Character_Sizz.h"
#include "Character_Maria.h"
#include "Export_Function.h"
#include "SubPageObserver.h"

CMainMenu::CMainMenu(eObjectType _eObjectType)
:CGameObject(_eObjectType)
,m_iTopMenuIndex(0), m_iLeftMenuIndex(0), m_pSubPage(NULL), m_bUISwitch(false), m_pSubObserver(NULL)
{
	m_pSprite = ENGINE::GetDeviceManager()->GetSprite();
}

CMainMenu::~CMainMenu(void)
{
	Release();
}

CMainMenu* CMainMenu::Create(eObjectType _eObjectType)
{
	CMainMenu* pMainMenu = new CMainMenu(_eObjectType);

	if(FAILED(pMainMenu->Initialize()))
	{
		SAFE_DELETE(pMainMenu);
	}

	return pMainMenu;
}

HRESULT CMainMenu::Initialize(void)
{
	ENGINE::CPage* pPage = ENGINE::CCharacterStatePage::Create(this, m_pSprite);

	if(pPage == NULL)
		return E_FAIL;

	m_vecPage[MENU_CHARACTER].push_back(pPage);

	pPage = ENGINE::CCharacterItemPage::Create(this, m_pSprite);

	if(pPage == NULL)
		return E_FAIL;

	m_vecPage[MENU_CHARACTER].push_back(pPage);

	pPage = ENGINE::CCharacterEquipPage::Create(this, m_pSprite);

	if(pPage == NULL)
		return E_FAIL;

	m_vecPage[MENU_CHARACTER].push_back(pPage);

	pPage = ENGINE::CCharacterMagicPage::Create(this, m_pSprite);

	if(pPage == NULL)
		return E_FAIL;

	m_vecPage[MENU_CHARACTER].push_back(pPage);

	pPage = ENGINE::CCharacterSkillPage::Create(this, m_pSprite);

	if(pPage == NULL)
		return E_FAIL;

	m_vecPage[MENU_CHARACTER].push_back(pPage);

	pPage = ENGINE::CDiaryItemPage::Create(this, m_pSprite);

	if(pPage == NULL)
		return E_FAIL;

	m_vecPage[MENU_DIARY].push_back(pPage);

	pPage = ENGINE::CDiaryMonsterPage::Create(this, m_pSprite);

	if(pPage == NULL)
		return E_FAIL;

	m_vecPage[MENU_DIARY].push_back(pPage);

	pPage = ENGINE::CDiaryScrapPage::Create(this, m_pSprite);

	if(pPage == NULL)
		return E_FAIL;

	m_vecPage[MENU_DIARY].push_back(pPage);

	pPage = ENGINE::CTacticsPage::Create(this, m_pSprite);

	if(pPage == NULL)
		return E_FAIL;

	m_vecPage[MENU_TACTICS].push_back(pPage);

	m_pSubPage = ENGINE::CSubPage::Create(this, m_pSprite);

	if(m_pSubPage == NULL)
		return E_FAIL;

	//Button »ý¼º
	float fX = 98.f;
	float fY = 139.4f;

	float fCX = 15.f;
	float fCY = 82.6f;

	D3DXVECTOR3 vPos(0.f, 0.f, 0.f);

	for(int i = 0; i < 3; ++i)
	{
		fY = 139.4f + (i * fCY);
		vPos.x = fX;
		vPos.y = fY;

		ENGINE::CButton* pButton = ENGINE::CButton::Create(this, vPos, fCX, fCY);

		m_vecLeftButton.push_back(pButton);
	}

	fX = 272.8f;
	fY = 84.5f;

	fCX = 77.6f;
	fCY = 29.f;

	for(int i = 0; i < 5; ++i)
	{
		fX = 272.8f + (i * fCX);

		vPos.x = fX;
		vPos.y = fY;

		ENGINE::CButton* pButton = ENGINE::CButton::Create(this, vPos, fCX, fCY, (eButtonType)i);

		m_vecTopButton.push_back(pButton);
	}

	ENGINE::GetInfoSubject()->AddData(MESSAGE_MAINUI_LEFT, &m_iLeftMenuIndex);
	ENGINE::GetInfoSubject()->Notify(MESSAGE_MAINUI_LEFT);

	ENGINE::GetInfoSubject()->AddData(MESSAGE_MAINUI_SWITCH, &m_bUISwitch);
	ENGINE::GetInfoSubject()->Notify(MESSAGE_MAINUI_SWITCH);

	m_pSubObserver = ENGINE::CSubPageObserver::Create(this);
	ENGINE::GetInfoSubject()->Subscribe(m_pSubObserver);
	m_bUISwitch = true;

	return S_OK;
}

int CMainMenu::Update(void)
{
	if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_F2))
	{
		if(m_bUISwitch)
		{
			m_bUISwitch = false;
			ENGINE::GetInfoSubject()->Notify(MESSAGE_MAINUI_SWITCH);
		}
		else
		{
			m_bUISwitch = true;
			ENGINE::GetInfoSubject()->Notify(MESSAGE_MAINUI_SWITCH);
		}
	}

	if(m_bUISwitch)
	{
		ENGINE::GetInfoSubject()->Notify(MESSAGE_MAINUI_SWITCH);
		return 0;
	}

	POINT ptMouse;// = CMouse::GetMousePoint();
	ENGINE::GetInputManager()->GetMousePos(&ptMouse);

	if(ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
	{
		int iSize = m_vecLeftButton.size();

		for(int i = 0; i < iSize; ++i)
		{
			m_vecLeftButton[i]->SetMousePos(ptMouse);

			if(m_vecLeftButton[i]->Update() == 1)
			{
				m_iLeftMenuIndex = i;
				m_iTopMenuIndex = 0;
				ENGINE::GetInfoSubject()->Notify(MESSAGE_MAINUI_LEFT);

				break;
			}
		}

		iSize = m_vecPage[m_iLeftMenuIndex].size();

		for(int i = 0; i < iSize; ++i)
		{
			m_vecTopButton[i]->SetMousePos(ptMouse);
			if(m_vecTopButton[i]->Update() == 1)
			{
				m_iTopMenuIndex = i;
				break;
			}
		}
	}

	m_pSubPage->SetMousePos(ptMouse);
	m_pSubPage->Update();

	eCharacterID eCharID = m_pSubObserver->GetCharCur();

	if(eCharID == CHARACTER_MARIA && m_iTopMenuIndex == 3)
	{
		m_iTopMenuIndex = 4;
	}
	else if(eCharID == CHARACTER_SIZZ && m_iTopMenuIndex == 4)
	{
		m_iTopMenuIndex = 3;
	}
	else if(eCharID == CHARACTER_ELLUARD && m_iTopMenuIndex == 3)
	{
		m_iTopMenuIndex = 4;
	}
	else if(eCharID == CHARACTER_TENZI && m_iTopMenuIndex == 3)
	{
		m_iTopMenuIndex = 4;
	}

	m_vecPage[m_iLeftMenuIndex][m_iTopMenuIndex]->SetMousePos(ptMouse);
	m_vecPage[m_iLeftMenuIndex][m_iTopMenuIndex]->Update();

	return 0;
}

void CMainMenu::Render(void)
{
	if(m_bUISwitch)
	{
		return;
	}

	ENGINE::GetDevice()->EndScene();

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, WINCX / 2.f, WINCY / 2.f, 0.f);

	m_pSprite->SetTransform(&matTrans);

	TEXINFO* pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"MainMenuBackGround", 0);

	float fX = pTexInfo->ImgInfo.Width / 2.f;
	float fY = pTexInfo->ImgInfo.Height / 2.f;

	D3DXVECTOR3 vCenter(fX, fY, 0.f);

	m_pSprite->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//BackGround

	pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"LeftMenu", m_iLeftMenuIndex);

	fX = pTexInfo->ImgInfo.Width / 2.f;
	fY = pTexInfo->ImgInfo.Height / 2.f;

	vCenter.x = fX;
	vCenter.y = fY;

	D3DXMatrixTranslation(&matTrans, 98.f, 222.f, 0.f);

	m_pSprite->SetTransform(&matTrans);
	m_pSprite->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//Left Menu

	pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"TopMenu", m_iTopMenuIndex);

	fX = pTexInfo->ImgInfo.Width / 2.f;
	fY = pTexInfo->ImgInfo.Height / 2.f;

	vCenter.x = fX;
	vCenter.y = fY;

	D3DXMatrixTranslation(&matTrans, 428.f, 84.5f, 0.f);

	m_pSprite->SetTransform(&matTrans);
	m_pSprite->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//Top Menu

	m_vecPage[m_iLeftMenuIndex][m_iTopMenuIndex]->Render();
	m_pSubPage->Render();

	for(size_t i = 0; i < m_vecTopButton.size(); ++i)
	{
		m_vecTopButton[i]->Render();
	}

	m_pSprite->End();

	ENGINE::GetDevice()->BeginScene();
}

void CMainMenu::Release(void)
{	
	for(int i = 0; i < MENU_END; ++i)
	{
		for(size_t j = 0; j < m_vecPage[i].size(); ++j)
		{
			SAFE_DELETE(m_vecPage[i][j]);
		}
		m_vecPage[i].clear();
	}

	for(size_t i = 0; i < m_vecLeftButton.size(); ++i)
	{
		SAFE_DELETE(m_vecLeftButton[i]);
	}
	m_vecLeftButton.clear();

	for(size_t i = 0; i < m_vecTopButton.size(); ++i)
	{
		SAFE_DELETE(m_vecTopButton[i]);
	}
	m_vecTopButton.clear();

	SAFE_DELETE(m_pSubPage);

	SAFE_DELETE(m_pSubObserver);
}

bool CMainMenu::GetUISwitch(void)
{
	return m_bUISwitch;
}