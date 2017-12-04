#include "CharacterItemPage.h"

#include "Export_Function.h"

#include "SubPageObserver.h"
#include "GroupObserver.h"
#include "CharacterGroup.h"
#include "Character.h"
#include "Export_System.h"
#include "Inventory.h"
#include "Item.h"

ENGINE::CCharacterItemPage::CCharacterItemPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
:CCharacterPage(_pOwner, pSprite)
, m_iItem(0)
, m_fScroll(0.f)
, m_bKeyInput(false)
, iX(0)
, iY(0)
, iYBackUp(0)
, m_bScrollOut(false)
, m_bUpScrollNow(false)
, m_bDownScrollNow(false)
, m_bMoveScrollNow(false)
, m_iKeyInput(SCROLL_START)
, fMouseX(0.f)
, fMouseY(0.f)
, m_bMessage(false)
, bButton(false)
, m_iSelectMouse(0)
, eCharID(CHARACTER_SIZZ)
{
}

ENGINE::CCharacterItemPage::~CCharacterItemPage(void)
{
	Release();
}

ENGINE::CCharacterItemPage* ENGINE::CCharacterItemPage::Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
{
	CCharacterItemPage* pPage = new CCharacterItemPage(_pOwner, pSprite);

	if(FAILED(pPage->Init()))
	{
		SAFE_DELETE(pPage);
	}

	return pPage;
}

HRESULT ENGINE::CCharacterItemPage::Init(void)
{
	m_pGroupObserver = ENGINE::CGroupObserver::Create(m_pOwner);

	ENGINE::GetInfoSubject()->Subscribe(m_pGroupObserver);

	return S_OK;
}

void ENGINE::CCharacterItemPage::Release(void)
{
	SAFE_DELETE(m_pGroupObserver);
}

int ENGINE::CCharacterItemPage::Update(void)
{
	eCharID = dynamic_cast<CSubPageObserver*>(m_pSubObserver)->GetCharCur();
	m_pInven = static_cast<CInventory*>(ENGINE::GetManagement()->GetGameObject(L"Inventory"));
		//m_pGroupObserver->GetCharacterGroup()->GetCharacter(CHARACTER_SIZZ)->GetInven();
	CInventory* pInven = static_cast<CInventory*>(ENGINE::GetManagement()->GetGameObject(L"Inventory"));
	vecInven = m_pInven->GetvecInven();

	m_bUpScrollNow = false;
	m_bDownScrollNow = false;
	m_bMoveScrollNow = false;

	iX = (vecInven->size() % 2);
	iY = (vecInven->size() / 2);

	if(m_ptMouse.x >= 685.f && m_ptMouse.x <= 725.f && iX + iY > 12 && m_ptMouse.y > 174.f && m_ptMouse.y < 455.f)
	{
		if(GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
		{
			if(m_ptMouse.y < 232.f + m_fScroll && m_ptMouse.y > 212.f + m_fScroll && m_iKeyInput != SCROLL_PLUS && m_iKeyInput != SCROLL_MINU)
			{
				if(m_bKeyInput == false)
					m_iKeyInput = SCROLL_DRAG;
				m_bKeyInput = true;
			}

			else if(m_ptMouse.y < 232.f + m_fScroll && m_iKeyInput != SCROLL_DRAG)
			{
				if(m_bKeyInput == false)
					m_iKeyInput = SCROLL_MINU;
				m_bKeyInput = true;
			}
			else if(m_ptMouse.y > 232.f + m_fScroll && m_iKeyInput != SCROLL_DRAG)
			{
				if(m_bKeyInput == false)
					m_iKeyInput = SCROLL_PLUS;
				m_bKeyInput = true;
			}
		}

		if(m_iKeyInput == SCROLL_DRAG
			&& m_fScroll >= 0.f && m_fScroll <= 195.f)
		{
			m_fScroll = m_ptMouse.y - 222.f;
			m_bMoveScrollNow = true;
		}

		if(m_iKeyInput == SCROLL_MINU
			&& m_fScroll > 0.f && m_ptMouse.y < 222.f + m_fScroll)
		{
			m_fScroll -= 12.f / (iY + iX);
			m_bUpScrollNow = true;
			m_bMoveScrollNow = true;
		}

		if(m_iKeyInput == SCROLL_PLUS
			&& m_fScroll < 195.f && m_ptMouse.y > 222.f + m_fScroll)
		{
			m_fScroll += 12.f / (iY + iX);
			m_bDownScrollNow = true;
			m_bMoveScrollNow = true;
		}
	}

	if(m_fScroll > 195.f)
	{
		m_fScroll = 195.f;
		m_bDownScrollNow = true;
	}
	if(m_fScroll < 0.f)
	{
		m_fScroll = 0.f;
		m_bUpScrollNow = true;
	}

	iYBackUp = iY;

	if(GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON));
	else if(GetInputManager()->IsKeyDown(KEY_STATE_RBUTTON));
	else
	{
		if(m_bKeyInput == false)
			m_iKeyInput = SCROLL_START;
		m_bKeyInput = false;
	}

	return 0;
}

void ENGINE::CCharacterItemPage::Render(void)
{
	TEXINFO* pTexInfo = NULL;

	pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"CharItemPage", 0);

	float fX = pTexInfo->ImgInfo.Width / 2.f;
	float fY = pTexInfo->ImgInfo.Height / 2.f;

	D3DXVECTOR3 vCenter(fX, fY, 0.f);

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 472.f, 293.f, 0.f);

	m_pSprite->SetTransform(&matTrans);

	m_pSprite->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	CPage::DrawFont("Barrier Point", 440.f, 124.f, 8.f, 0.f);
	//CPage::DrawFont("999/999", 544.f, 124.f, 8.f, 0.f);
	CPage::DrawFont("Hit Point", 440.f, 150.f, 8.f, 0.f);
	//CPage::DrawFont("999/999", 544.f, 150.f, 8.f, 0.f);
 
	CPage::DrawFont("Fire", 590.f, 124.f, 8.f, 0.f);
	CPage::DrawFont("Wind", 590.f, 141.f, 8.f, 0.f);
	CPage::DrawFont("Earth", 590.f, 158.f, 8.f, 0.f);

	m_bScrollOut = false;

	if(iY + iX > 12) // 이하 스크롤 출력
	{
		for(int i = 0; i < 12; ++i)
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 200.f + (i * 20), 3, NULL); // 밧줄?

		if(m_bUpScrollNow == false)
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 200.f, 4, NULL);
		else
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 200.f, 5, NULL); // 스크롤 시작

		if(m_bDownScrollNow == false)
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 440.f, 0, NULL);
		else
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 440.f, 1, NULL); // 스크롤 끝

		if(m_bMoveScrollNow == false)
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 222.f + m_fScroll, 7, NULL);
		else
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 222.f + m_fScroll, 8, NULL); // 스크롤 위치를 나타내는 텍스쳐
	}

	int iOut = 0, iIter = 0;
	TCHAR szNum[FULL_STRING];
	m_iSelectMouse = 0;

	for(size_t i = 0; i < vecInven->size(); ++i)
	{
		(*vecInven)[i]->m_bCursorOn = false;
		bButton = false;

		if(m_bMessage == true)
		{
			if(m_ptMouse.x > fMouseX - 17.f &&
				m_ptMouse.x < fMouseX + 163 &&
				m_ptMouse.y > fMouseY - 15.f &&
				m_ptMouse.y < fMouseY + 95.f)
				bButton = true;
			else if(GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON) || GetInputManager()->IsKeyDown(KEY_STATE_RBUTTON))
				m_bMessage = false;
		}
		
		if(m_bMessage == true && m_bKeyInput == false && (*vecInven)[i]->m_bSelect == true)
		{
			if(m_ptMouse.x > fMouseX &&
				m_ptMouse.x < fMouseX + 163 &&
				m_ptMouse.y > fMouseY + 10.f &&
				m_ptMouse.y < fMouseY + 30.f)
			{
				m_iSelectMouse = 1;
				if(GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
					(*vecInven)[i]->m_iNum -= 1;
			}
			if(m_ptMouse.x > fMouseX &&
				m_ptMouse.x < fMouseX + 163 &&
				m_ptMouse.y > fMouseY + 30.f &&
				m_ptMouse.y < fMouseY + 50.f)
			{
				m_iSelectMouse = 2;
				if(GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
					(*vecInven)[i]->m_iNum -= 1;
			}
			if(m_ptMouse.x > fMouseX &&
				m_ptMouse.x < fMouseX + 163 &&
				m_ptMouse.y > fMouseY + 50.f &&
				m_ptMouse.y < fMouseY + 70.f)
			{
				m_iSelectMouse = 3;
				if(GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
					(*vecInven)[i]->m_iNum -= 5;
			}
			if(m_ptMouse.x > fMouseX &&
				m_ptMouse.x < fMouseX + 163 &&
				m_ptMouse.y > fMouseY + 70.f &&
				m_ptMouse.y < fMouseY + 90.f)
			{
				m_iSelectMouse = 4;
				if(GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
					(*vecInven)[i]->m_iNum -= 10;
			}

			if(GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
			{
				if((*vecInven)[i]->m_iNum <= 0)
					(*vecInven)[i]->m_bFree = true;

				m_bKeyInput = true;
				m_bMessage = false;
				(*vecInven)[i]->m_bSelect = false;
			}
		}

		if(20.f * (iOut / 2) < 240.f + (((iX + iY - 12) / 195.f) * 20 * m_fScroll)
			&& 20.f * (iOut / 2) >= 0.f + (((iX + iY - 12) / 195.f) * 20 * m_fScroll)) // 스크롤 밖이면 출력 안함
		{
			if(m_bKeyInput == false
				&& m_ptMouse.x > 196.f * float(iOut % 2) + 270.f
				&& m_ptMouse.x < 196.f * float(iOut % 2) + 460.f
				&& m_ptMouse.y > 20.f * float(iOut / 2) + 180.f - (((iX + iY - 12) / 195.f) * 20 * m_fScroll)
				&& m_ptMouse.y < 20.f * float(iOut / 2) + 200.f - (((iX + iY - 12) / 195.f) * 20 * m_fScroll)
				)
			{	bool	bStop = false;

				if(m_bMessage == false)
					(*vecInven)[i]->m_bCursorOn = true;

				if(GetInputManager()->IsKeyDown(KEY_STATE_RBUTTON) && bButton == false)
				{
					(*vecInven)[i]->m_iNum -= 1;
					m_bKeyInput = true;

					for(size_t j = 0; j < vecInven->size(); ++j)
						(*vecInven)[j]->m_bSelect = false;
				}
				if(GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON) && bButton == false)
				{
					if((*vecInven)[i]->m_bFree == false && m_bKeyInput == false && (*vecInven)[i]->m_bSelect == true && m_bMessage == false)
					{
						m_bKeyInput = true;
						m_bMessage = true;

						break;
					}

					for(size_t j = 0; j < vecInven->size(); ++j)
						(*vecInven)[j]->m_bSelect = false;

					(*vecInven)[i]->m_bSelect = true;

					fMouseX = float(m_ptMouse.x);
					fMouseY = float(m_ptMouse.y);

					m_bKeyInput = true;
				}
			}

			int iR = 0;
			if((*vecInven)[i]->m_bCursorOn == true)
				iR = 255;

			if((*vecInven)[i]->m_bSelect == true)
			{
				DrawSprite(RESOURCE_TYPE_STATIC, L"SlotCheak", 196.f * float(iOut % 2) + 265.f, 20.f * float(iOut / 2) + 190.f - (((iX + iY - 12) / 195.f) * 20 * m_fScroll), 0, NULL);

				for(int jOut = 0; jOut < 8; ++jOut)
					DrawSprite(RESOURCE_TYPE_STATIC, L"SlotCheak", 196.f * float(iOut % 2) + 285.f + (jOut * 20.f), 20.f * float(iOut / 2) + 190.f - (((iX + iY - 12) / 195.f) * 20 * m_fScroll), 1, NULL);

				DrawSprite(RESOURCE_TYPE_STATIC, L"SlotCheak", 196.f * float(iOut % 2) + 445.f, 20.f * float(iOut / 2) + 190.f - (((iX + iY - 12) / 195.f) * 20 * m_fScroll), 2, NULL);
			}
			DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 196.f * float(iOut % 2) + 270.f, 20.f * float(iOut / 2) + 190.f - (((iX + iY - 12) / 195.f) * 20 * m_fScroll), 0, NULL); //아이템 출력 테스트


			wsprintf(szNum, L"%d", (*vecInven)[i]->m_iNum);

			CPage::DrawText((*vecInven)[i]->m_szName, D3DCOLOR_ARGB(255, iR, 0, 0), 196.f * float(iOut % 2) + 300.f, 20.f * float(iOut / 2) + 180.f - (((iX + iY - 12) / 195.f) * 20 * m_fScroll));
			CPage::DrawText(szNum, D3DCOLOR_ARGB(255, iR, 0, 0), 196.f * float(iOut % 2) + 440.f, 20.f * float(iOut / 2) + 180.f - (((iX + iY - 12) / 195.f) * 20 * m_fScroll));

			//if((*iter).bSelect == true)
				//m_bMessage = true;
		}
		++iOut;

		if((*vecInven)[i]->m_bSelect == false)
			++iIter;
	}

	for(size_t i = 0; i < vecInven->size(); ++i)
		if((*vecInven)[i]->m_iNum <= 0)
		{
			vecInven->erase(vecInven->begin() + i);
		}

	iOut = 0;

	if(m_bMessage == true)
	{
		for(; iOut < 5; ++iOut)
		{
			if(iOut == 0)
				DrawSprite(RESOURCE_TYPE_STATIC, L"MessagePice", fMouseX, fMouseY, 0, NULL);
			else if(iOut == 4)
				DrawSprite(RESOURCE_TYPE_STATIC, L"MessagePice", fMouseX, fMouseY + (20 * iOut), 6, NULL);
			else
				DrawSprite(RESOURCE_TYPE_STATIC, L"MessagePice", fMouseX, fMouseY + (20 * iOut), 3, NULL);

			if(iOut == 0)
				for(int jOut = 0; jOut < 3; ++jOut)
					DrawSprite(RESOURCE_TYPE_STATIC, L"MessagePice", fMouseX + (jOut * 40.f) + 32.f, fMouseY, 1, NULL);
			else if(iOut == 4)
				for(int jOut = 0; jOut < 3; ++jOut)
					DrawSprite(RESOURCE_TYPE_STATIC, L"MessagePice", fMouseX + (jOut * 40.f) + 32.f, fMouseY + (20 * iOut), 7, NULL);
			else
				for(int jOut = 0; jOut < 3; ++jOut)
					DrawSprite(RESOURCE_TYPE_STATIC, L"MessagePice", fMouseX + (jOut * 40.f) + 32.f, fMouseY + (20 * iOut), 4, NULL);

			if(iOut == 0)
				DrawSprite(RESOURCE_TYPE_STATIC, L"MessagePice", fMouseX + 148.f, fMouseY, 2, NULL);
			else if(iOut == 4)
				DrawSprite(RESOURCE_TYPE_STATIC, L"MessagePice", fMouseX + 148.f, fMouseY + (20 * iOut), 8, NULL);
			else
				DrawSprite(RESOURCE_TYPE_STATIC, L"MessagePice", fMouseX + 148.f, fMouseY + (20 * iOut), 5, NULL);
		}


		if(m_iSelectMouse > 0)
		{
			DrawSprite(RESOURCE_TYPE_STATIC, L"SlotCheak", fMouseX, fMouseY + (float(m_iSelectMouse) * 20.f), 0, NULL);

			for(int jOut = 0; jOut < 6; ++jOut)
				DrawSprite(RESOURCE_TYPE_STATIC, L"SlotCheak", fMouseX + (jOut * 20.f) + 20.f, fMouseY + (float(m_iSelectMouse) * 20.f), 1, NULL);

			DrawSprite(RESOURCE_TYPE_STATIC, L"SlotCheak", fMouseX + 140.f, fMouseY + (float(m_iSelectMouse) * 20.f), 2, NULL);
		}

		DrawSprite(RESOURCE_TYPE_STATIC, L"MessagePice", fMouseX + 77.f, fMouseY + 3.f, 34, NULL);
		CPage::DrawText(L"사용하기", D3DCOLOR_ARGB(255, 0, 0, 0), fMouseX,  fMouseY + 10.f);
		CPage::DrawText(L"1개 버리기", D3DCOLOR_ARGB(255, 0, 0, 0), fMouseX,  fMouseY + 30.f);
		CPage::DrawText(L"5개 버리기", D3DCOLOR_ARGB(255, 0, 0, 0), fMouseX,  fMouseY + 50.f);
		CPage::DrawText(L"10개 버리기", D3DCOLOR_ARGB(255, 0, 0, 0), fMouseX,  fMouseY + 70.f);
	}

	DrawSprite(RESOURCE_TYPE_STATIC, L"UIBar", 512.f, 130.f, 0, NULL); //Barrier Point
	DrawSprite(RESOURCE_TYPE_STATIC, L"UIBar", 512.f, 156.f, 1, NULL); //Hit Point

	if(eCharID == CHARACTER_SIZZ)
		CPage::DrawText(L"시즈의 상태", D3DCOLOR_ARGB(255, 0, 0, 0), 330.f, 110.f);
	if(eCharID == CHARACTER_MARIA)
		CPage::DrawText(L"마리아의 상태", D3DCOLOR_ARGB(255, 0, 0, 0), 314.f, 110.f);
	if(eCharID == CHARACTER_ELLUARD)
		CPage::DrawText(L"엘류어드의 상태", D3DCOLOR_ARGB(255, 0, 0, 0), 298.f, 110.f);
	if(eCharID == CHARACTER_TENZI)
		CPage::DrawText(L"텐지의 상태", D3DCOLOR_ARGB(255, 0, 0, 0), 330.f, 110.f);
}