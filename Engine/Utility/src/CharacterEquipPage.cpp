#include "CharacterEquipPage.h"

#include "Export_Function.h"

#include "SubPageObserver.h"
#include "GroupObserver.h"
#include "CharacterGroup.h"
#include "Character.h"
#include "Export_System.h"
#include "Equip.h"
#include "Item.h"

ENGINE::CCharacterEquipPage::CCharacterEquipPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
:CCharacterPage(_pOwner, pSprite)
, m_iItem(0)
, m_fScroll(0.f)
, m_bKeyInput(false)
, iX(0)
, iY(0)
, m_fScrollOut(0.f)
, m_fScrollClo(0.f)
, m_bScrollOut(false)
, m_bUpScrollNow(false)
, m_bDownScrollNow(false)
, m_bMoveScrollNow(false)
, m_iKeyInput(SCROLL_START)
, eNowCheakType(TYPE_STRAT)
, eEquipCheak(TYPE_STRAT)
, eCharID(CHARACTER_SIZZ)
, iContinue(0)
{
	wsprintf(szEquip, L"");
}

ENGINE::CCharacterEquipPage::~CCharacterEquipPage(void)
{
	Release();
}

ENGINE::CCharacterEquipPage* ENGINE::CCharacterEquipPage::Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
{
	CCharacterEquipPage* pPage = new CCharacterEquipPage(_pOwner, pSprite);

	if(FAILED(pPage->Init()))
	{
		SAFE_DELETE(pPage);
	}

	return pPage;
}	

HRESULT ENGINE::CCharacterEquipPage::Init(void)
{
	m_pGroupObserver = ENGINE::CGroupObserver::Create(m_pOwner);

	ENGINE::GetInfoSubject()->Subscribe(m_pGroupObserver);

	return S_OK;
}

void ENGINE::CCharacterEquipPage::Release()
{
	SAFE_DELETE(m_pGroupObserver);
}

int ENGINE::CCharacterEquipPage::Update(void)
{
	eCharID = dynamic_cast<CSubPageObserver*>(m_pSubObserver)->GetCharCur();
	m_pEquip = m_pGroupObserver->GetCharacterGroup()->GetCharacter(CHARACTER_SIZZ)->GetEquip();
	vecEquip = m_pEquip->GetvecEquip();


	//m_tTempState = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetCharacterState();

	m_bUpScrollNow = false;
	m_bDownScrollNow = false;
	m_bMoveScrollNow = false;

	iX = ((int(vecEquip->size()) - iContinue) % 2);
	iY = ((int(vecEquip->size()) - iContinue) / 2);

	if(GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
	{
		if(m_ptMouse.x >= 685.f && m_ptMouse.x <= 725.f && iX + iY > 10 && m_ptMouse.y > 204.f && m_ptMouse.y < 455.f)
		{
			if(m_ptMouse.y < 273.f + m_fScroll && m_ptMouse.y > 251.f + m_fScroll && m_iKeyInput != SCROLL_PLUS && m_iKeyInput != SCROLL_MINU)
			{
				if(m_bKeyInput == false)
					m_iKeyInput = SCROLL_DRAG;
				m_bKeyInput = true;
			}

			else if(m_ptMouse.y < 262.f + m_fScroll && m_iKeyInput != SCROLL_DRAG)
			{
				if(m_bKeyInput == false)
					m_iKeyInput = SCROLL_MINU;
				m_bKeyInput = true;
			}
			else if(m_ptMouse.y > 262.f + m_fScroll && m_iKeyInput != SCROLL_DRAG)
			{
				if(m_bKeyInput == false)
					m_iKeyInput = SCROLL_PLUS;
				m_bKeyInput = true;
			}
		}

		if(m_iKeyInput == SCROLL_DRAG
			&& m_fScroll >= 0.f && m_fScroll <= 175.f)
		{
			m_fScroll = m_ptMouse.y - 262.f;
			m_bMoveScrollNow = true;
		}

		if(m_iKeyInput == SCROLL_MINU
			&& m_fScroll > 0.f && m_ptMouse.y < 262.f + m_fScroll)
		{
			m_fScroll -= 10.f / (iY + iX);
			m_bUpScrollNow = true;
			m_bMoveScrollNow = true;
		}

		if(m_iKeyInput == SCROLL_PLUS
			&& m_fScroll < 175.f && m_ptMouse.y > 262.f + m_fScroll)
		{
			m_fScroll += 10.f / (iY + iX);
			m_bDownScrollNow = true;
			m_bMoveScrollNow = true;
		}
	}
	else if(GetInputManager()->IsKeyDown(KEY_STATE_RBUTTON));
	else
	{
		if(m_bKeyInput == false)
			m_iKeyInput = SCROLL_START;
		m_bKeyInput = false;
	}

	if(m_fScroll > 175.f)
	{
		m_fScroll = 175.f;
		m_bDownScrollNow = true;
	}
	if(m_fScroll < 0.f)
	{
		m_fScroll = 0.f;
		m_bUpScrollNow = true;
	}


	return 0;
}

void ENGINE::CCharacterEquipPage::Render(void)
{
	TEXINFO* pTexInfo = NULL;

	pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"CharEquipPage", eCharID);

	float fX = pTexInfo->ImgInfo.Width / 2.f;
	float fY = pTexInfo->ImgInfo.Height / 2.f;

	D3DXVECTOR3 vCenter(fX, fY, 0.f);

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 472.f, 293.f, 0.f);

	m_pSprite->SetTransform(&matTrans);

	m_pSprite->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	bool	bCap = false, bWea = false, bArm = false, bSho = false, bWear = false, bShi = false, bAcc1 = false, bAcc2 = false;

	for(size_t i = 0; i < vecEquip->size(); ++i)
	{
		if((*vecEquip)[i]->m_iType == TYPE_CAP && (*vecEquip)[i]->m_eID == eCharID)
		{
			if(eEquipCheak == TYPE_CAP)
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 255, 0, 0), 251.f, 114.f);
			else
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 251.f, 114.f);

			DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 353.f, 122.f, (*vecEquip)[i]->m_iImgCode, NULL); //모자
			bCap = true;
		}
		if(eNowCheakType == TYPE_CAP)
			DrawSprite(RESOURCE_TYPE_STATIC, L"OKButton", 353.f, 122.f, 0, NULL);

		if((*vecEquip)[i]->m_iType == TYPE_WEAPON && (*vecEquip)[i]->m_eID == eCharID)
		{
			if(eEquipCheak == TYPE_WEAPON)
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 255, 0, 0), 251.f, 142.f);
			else
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 251.f, 142.f);

			DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 353.f, 150.f, (*vecEquip)[i]->m_iImgCode, NULL); //무기
			bWea = true;
		}
		if(eNowCheakType == TYPE_WEAPON)
			DrawSprite(RESOURCE_TYPE_STATIC, L"OKButton", 353.f, 150.f, 0, NULL);

		if((*vecEquip)[i]->m_iType == TYPE_ARMOUR && (*vecEquip)[i]->m_eID == eCharID)
		{
			if(eEquipCheak == TYPE_ARMOUR)
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 255, 0, 0), 251.f, 168.f);
			else
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 251.f, 168.f);
			DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 353.f, 178.f, (*vecEquip)[i]->m_iImgCode, NULL); //갑옷
			bArm = true;
		}
		if(eNowCheakType == TYPE_ARMOUR)
			DrawSprite(RESOURCE_TYPE_STATIC, L"OKButton", 353.f, 178.f, 0, NULL);

		if((*vecEquip)[i]->m_iType == TYPE_SHOES && (*vecEquip)[i]->m_eID == eCharID)
		{
			if(eEquipCheak == TYPE_SHOES)
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 255, 0, 0), 251.f, 194.f);
			else
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 251.f, 194.f);
			DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 353.f, 206.f, (*vecEquip)[i]->m_iImgCode, NULL); //신발
			bSho = true;
		}
		if(eNowCheakType == TYPE_SHOES)
			DrawSprite(RESOURCE_TYPE_STATIC, L"OKButton", 353.f, 206.f, 0, NULL);

		if((*vecEquip)[i]->m_iType == TYPE_WEAR && (*vecEquip)[i]->m_eID == eCharID)
		{
			if(eEquipCheak == TYPE_WEAR)
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 255, 0, 0), 460.f, 114.f);
			else
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 460.f, 114.f);

			DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 435.f, 122.f, (*vecEquip)[i]->m_iImgCode, NULL); //걸칠것
			bWear = true;
		}
		if(eNowCheakType == TYPE_WEAR)
			DrawSprite(RESOURCE_TYPE_STATIC, L"OKButton", 435.f, 122.f, 0, NULL);

		if((*vecEquip)[i]->m_iType == TYPE_SHIELD && (*vecEquip)[i]->m_eID == eCharID)
		{
			if(eEquipCheak == TYPE_SHIELD)
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 255, 0, 0), 460.f, 142.f);
			else
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 460.f, 142.f);
			DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 435.f, 150.f, (*vecEquip)[i]->m_iImgCode, NULL); //방패
			bShi = true;
		}
		if(eNowCheakType == TYPE_SHIELD)
			DrawSprite(RESOURCE_TYPE_STATIC, L"OKButton", 435.f, 150.f, 0, NULL);

		if((*vecEquip)[i]->m_iType == TYPE_ACCESSORY1 && (*vecEquip)[i]->m_eID == eCharID)
		{
			if(eEquipCheak == TYPE_ACCESSORY1)
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 255, 0, 0), 460.f, 168.f);
			else
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 460.f, 168.f);
			DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 435.f, 178.f, (*vecEquip)[i]->m_iImgCode, NULL); //악세
			bAcc1 = true;
		}

		if((*vecEquip)[i]->m_iType == TYPE_ACCESSORY2 && (*vecEquip)[i]->m_eID == eCharID)
		{
			if(eEquipCheak == TYPE_ACCESSORY2)
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 255, 0, 0), 460.f, 194.f);
			else
				CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 460.f, 194.f);

			DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 435.f, 206.f, (*vecEquip)[i]->m_iImgCode, NULL); //악세
			bAcc2 = true;
		}
		if(eNowCheakType == TYPE_ACCESSORY1 || eNowCheakType == TYPE_ACCESSORY2)
		{
			DrawSprite(RESOURCE_TYPE_STATIC, L"OKButton", 435.f, 178.f, 0, NULL);
			DrawSprite(RESOURCE_TYPE_STATIC, L"OKButton", 435.f, 206.f, 0, NULL);
		}
	}
		if(bCap == false)
			CPage::DrawText(L"(모자없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 251.f, 114.f);
		if(bWea == false)
			CPage::DrawText(L"(무기없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 251.f, 142.f);
		if(bArm == false)
			CPage::DrawText(L"(갑옷없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 251.f, 168.f);
		if(bSho == false)
			CPage::DrawText(L"(신발없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 251.f, 194.f);
		if(bWear == false)
			CPage::DrawText(L"(걸칠것없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 460.f, 114.f);
		if(bShi == false)
			CPage::DrawText(L"(방패없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 460.f, 142.f);
		if(bAcc1 == false)
			CPage::DrawText(L"(악세사리없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 460.f, 168.f);
		if(bAcc2 == false)
			CPage::DrawText(L"(악세사리없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 460.f, 194.f);

	//CHARACTER_STATE* pCharState = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetCharacterState();
	CHARACTER_STATE tCharState = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetOriginStatus();

	//여기서 오리지날 값을 받아오고 실시간으로 계산을 해주자..
	// 스텟
	CPage::DrawFont("BP", 572.f, 130.f, 8.f, 0.f);
	CPage::DrawFont("ATK", 572.f, 146.f, 8.f, 0.f);
	CPage::DrawFont("DEF", 572.f, 162.f, 8.f, 0.f);
	CPage::DrawFont("SPD", 572.f, 178.f, 8.f, 0.f);
	CPage::DrawFont("MAG", 572.f, 194.f, 8.f, 0.f);
	CPage::DrawFont("CRI", 572.f, 210.f, 8.f, 0.f);
	
	int iBp = 0;
	int iAtk = 0;
	int iDef = 0;
	int iSpd = 0;
	int iMag = 0;
	int iCri = 0;

	for(size_t i = 0; i < vecEquip->size(); ++i)
	{
		if((*vecEquip)[i]->m_eID != eCharID)
		{
			continue;
		}

		iBp += (*vecEquip)[i]->m_iBP;				
		iAtk += (*vecEquip)[i]->m_iAtk;
		iDef += (*vecEquip)[i]->m_iDef;
		iSpd += (*vecEquip)[i]->m_iSpd;
		iMag += (*vecEquip)[i]->m_iMag;
		iCri += (*vecEquip)[i]->m_iCri;
	}
	
	CPage::DrawFont_Int(tCharState.iBarrierPoint + iBp, 623.f, 129.f, 8.f, 0.f);
	CPage::DrawFont_Int(tCharState.iATK + iAtk, 622.f, 146.f, 8.f, 0.f);
	CPage::DrawFont_Int(tCharState.iDEF + iDef, 622.f, 162.f, 8.f, 0.f);
	CPage::DrawFont_Int(tCharState.iSPD + iSpd, 622.f, 178.f, 8.f, 0.f);
	CPage::DrawFont_Int(tCharState.iMAG + iMag, 622.f, 194.f, 8.f, 0.f);
	CPage::DrawFont_Int(tCharState.iCRI + iCri, 622.f, 210.f, 8.f, 0.f);

	m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->SetState(iBp, iAtk, iDef, iSpd, iMag, iCri);

	m_bScrollOut = false;

	int iItemScroll = 0;
	iContinue = 0;
	TCHAR	szNum[FULL_STRING];

	wsprintf(szNum, L"%d", 1);
	for(size_t i = 0; i < vecEquip->size(); ++i)
	{
		if((*vecEquip)[i]->m_eID != eCharID && (*vecEquip)[i]->m_eID != CHARACTER_END)
		{
			iContinue++;
			continue;
		}

		(*vecEquip)[i]->m_bCursorOn = false;
		int		iA;
		int		iR = 0;
		int		iB = 0;

		if(20.f * ((i - iContinue) / 2) < 190.f + (((iX + iY - 10) / 195.f) * 20 * m_fScroll)
			&& 20.f * ((i - iContinue) / 2) >= 0.f + (((iX + iY - 10) / 195.f) * 20 * m_fScroll)) // 스크롤 밖이면 출력 안함
		{
			if(m_bKeyInput == false && GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON)
				&& m_ptMouse.x > 251.f && m_ptMouse.x < 373.f
				&& m_ptMouse.y > 114.f && m_ptMouse.y < 142.f)
			{
				if(eEquipCheak != TYPE_CAP)
				{
					eEquipCheak = TYPE_CAP;
					m_bKeyInput = true;
					break;
				}
				else
				{
					for(size_t j = 0; j < vecEquip->size(); ++j)
						if((*vecEquip)[j]->m_iType == TYPE_CAP && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
						{
							(*vecEquip)[j]->m_bFree = false;
							(*vecEquip)[j]->m_eID = CHARACTER_END;
							(*vecEquip)[j]->m_iNum += 1;
						}

					eEquipCheak = TYPE_STRAT;
					m_bKeyInput = true;
				}
			}

			else if(m_bKeyInput == false && GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON)
				&& m_ptMouse.x > 251.f && m_ptMouse.x < 373.f
				&& m_ptMouse.y > 142.f && m_ptMouse.y < 168.f)
			{
				if(eEquipCheak != TYPE_WEAPON)
				{
					eEquipCheak = TYPE_WEAPON;
					m_bKeyInput = true;
					break;
				}
				else
				{
					for(size_t j = 0; j < vecEquip->size(); ++j)
						if((*vecEquip)[j]->m_iType == TYPE_WEAPON && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
						{
							(*vecEquip)[j]->m_bFree = false;
							(*vecEquip)[j]->m_eID = CHARACTER_END;
							(*vecEquip)[j]->m_iNum += 1;
						}
					eEquipCheak = TYPE_STRAT;
					m_bKeyInput = true;
				}
			} 

			else if(m_bKeyInput == false && GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON)
				&& m_ptMouse.x > 251.f && m_ptMouse.x < 373.f
				&& m_ptMouse.y > 168.f && m_ptMouse.y < 194.f)
			{
				if(eEquipCheak != TYPE_ARMOUR)
				{
					eEquipCheak = TYPE_ARMOUR;
					m_bKeyInput = true;
					break;
				}
				else
				{
					for(size_t j = 0; j < vecEquip->size(); ++j)
						if((*vecEquip)[j]->m_iType == TYPE_ARMOUR && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
						{
							(*vecEquip)[j]->m_bFree = false;
							(*vecEquip)[j]->m_iNum += 1;
							(*vecEquip)[j]->m_eID = CHARACTER_END;
						}
					eEquipCheak = TYPE_STRAT;
					m_bKeyInput = true;
				}
			}

			else if(m_bKeyInput == false && GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON)
				&& m_ptMouse.x > 251.f && m_ptMouse.x < 373.f
				&& m_ptMouse.y > 194.f && m_ptMouse.y < 216.f)
			{
				if(eEquipCheak != TYPE_SHOES)
				{
					eEquipCheak = TYPE_SHOES;
					m_bKeyInput = true;
					break;
				}
				else
				{
					for(size_t j = 0; j < vecEquip->size(); ++j)
						if((*vecEquip)[j]->m_iType == TYPE_SHOES && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
						{
							(*vecEquip)[j]->m_bFree = false;
							(*vecEquip)[j]->m_iNum += 1;
							(*vecEquip)[j]->m_eID = CHARACTER_END;
						}
					eEquipCheak = TYPE_STRAT;
					m_bKeyInput = true;
				}
			}

			else if(m_bKeyInput == false && GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON)
				&& m_ptMouse.x > 415.f && m_ptMouse.x < 547.f
				&& m_ptMouse.y > 114.f && m_ptMouse.y < 142.f)
			{
				if(eEquipCheak != TYPE_WEAR)
				{
					eEquipCheak = TYPE_WEAR;
					m_bKeyInput = true;
					break;
				}
				else
				{
					for(size_t j = 0; j < vecEquip->size(); ++j)
						if((*vecEquip)[j]->m_iType == TYPE_WEAR && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
						{
							(*vecEquip)[j]->m_bFree = false;
							(*vecEquip)[j]->m_iNum += 1;
							(*vecEquip)[j]->m_eID = CHARACTER_END;
						}
					eEquipCheak = TYPE_STRAT;
					m_bKeyInput = true;
				}
			}

			else if(m_bKeyInput == false && GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON)
				&& m_ptMouse.x > 415.f && m_ptMouse.x < 547.f
				&& m_ptMouse.y > 142.f && m_ptMouse.y < 168.f)
			{
				if(eEquipCheak != TYPE_SHIELD)
				{
					eEquipCheak = TYPE_SHIELD;
					m_bKeyInput = true;
					break;
				}
				else
				{
					for(size_t j = 0; j < vecEquip->size(); ++j)
						if((*vecEquip)[j]->m_iType == TYPE_SHIELD && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
						{
							(*vecEquip)[j]->m_bFree = false;
							(*vecEquip)[j]->m_iNum += 1;
							(*vecEquip)[j]->m_eID = CHARACTER_END;
						}
					eEquipCheak = TYPE_STRAT;
					m_bKeyInput = true;
				}
			}

			else if(m_bKeyInput == false && GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON)
				&& m_ptMouse.x > 415.f && m_ptMouse.x < 547.f
				&& m_ptMouse.y > 168.f && m_ptMouse.y < 194.f)
			{
				if(eEquipCheak != TYPE_ACCESSORY1)
				{
					eEquipCheak = TYPE_ACCESSORY1;
					m_bKeyInput = true;
					break;
				}
				else
				{
					for(size_t j = 0; j < vecEquip->size(); ++j)
						if((*vecEquip)[j]->m_iType == TYPE_ACCESSORY1 && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
						{
							(*vecEquip)[j]->m_bFree = false;
							(*vecEquip)[j]->m_iNum += 1;
							(*vecEquip)[j]->m_eID = CHARACTER_END;
						}
					eEquipCheak = TYPE_STRAT;
					m_bKeyInput = true;
				}
			}

			else if(m_bKeyInput == false && GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON)
				&& m_ptMouse.x > 415.f && m_ptMouse.x < 547.f
				&& m_ptMouse.y > 194.f && m_ptMouse.y < 216.f)
			{
				if(eEquipCheak != TYPE_ACCESSORY2)
				{
					eEquipCheak = TYPE_ACCESSORY2;
					m_bKeyInput = true;
					break;
				}
				else
				{
					for(size_t j = 0; j < vecEquip->size(); ++j)
						if((*vecEquip)[j]->m_iType == TYPE_ACCESSORY2 && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
						{
							(*vecEquip)[j]->m_bFree = false;
							(*vecEquip)[j]->m_iNum += 1;
							(*vecEquip)[j]->m_eID = CHARACTER_END;
							(*vecEquip)[j]->m_iType = TYPE_ACCESSORY1;
						}
					eEquipCheak = TYPE_STRAT;
					m_bKeyInput = true;
				}
			}

			else if(m_bKeyInput == false && GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
				eEquipCheak = TYPE_STRAT;

			if(m_bKeyInput == false
				&& m_ptMouse.x > 196.f * float((i - iContinue) % 2) + 270.f
				&& m_ptMouse.x < 196.f * float((i - iContinue) % 2) + 460.f
				&& m_ptMouse.y > 20.f * float((i - iContinue) / 2) + 230.f - (((iX + iY - 10) / 195.f) * 20 * m_fScroll)
				&& m_ptMouse.y < 20.f * float((i - iContinue) / 2) + 250.f - (((iX + iY - 10) / 195.f) * 20 * m_fScroll)
				)// 장비를 장착하는? 과정, 한 캐릭터로 장비를 장착했으면 다른 캐릭터로는 장비를 장착하거나 해제할 수 없음
			{
				(*vecEquip)[i]->m_bCursorOn = true;

				if(GetInputManager()->IsKeyDown(KEY_STATE_RBUTTON))
				{
					if((*vecEquip)[i]->m_bFree == false && m_bKeyInput == false)
					{
						if(EquipCheak((*vecEquip)[i]->m_iType, (*vecEquip)[i]->m_iImgCode, (*vecEquip)[i]->m_iItemCode, eCharID) == true)
						{
							(*vecEquip)[i]->m_iNum -= 1;
							(*vecEquip)[i]->m_eID = eCharID;
							(*vecEquip)[i]->m_bSelect = false;
							eNowCheakType = TYPE_STRAT;

							for(size_t j = 0; j < vecEquip->size(); ++j)
								(*vecEquip)[j]->m_bSelect = false;

							if((*vecEquip)[i]->m_iNum <= 0)
								(*vecEquip)[i]->m_bFree = true;
						}
					}
					else if((*vecEquip)[i]->m_bFree == true && m_bKeyInput == false && (*vecEquip)[i]->m_eID == eCharID)
					{
						if(EquipCheak((*vecEquip)[i]->m_iType, (*vecEquip)[i]->m_iImgCode, (*vecEquip)[i]->m_iItemCode, eCharID) == true)
						{
							(*vecEquip)[i]->m_bFree = false;
							(*vecEquip)[i]->m_eID = CHARACTER_END;
							(*vecEquip)[i]->m_iNum += 1;
							eNowCheakType = TYPE_STRAT;
						}
					}
					m_bKeyInput = true;
				}
				if(GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
				{
					if((*vecEquip)[i]->m_bFree == false && m_bKeyInput == false && (*vecEquip)[i]->m_bSelect == true)
					{
						if(EquipCheak((*vecEquip)[i]->m_iType, (*vecEquip)[i]->m_iImgCode, (*vecEquip)[i]->m_iItemCode, eCharID) == true)
						{
							(*vecEquip)[i]->m_iNum -= 1;
							(*vecEquip)[i]->m_eID = eCharID;
							(*vecEquip)[i]->m_bSelect = false;
							m_bKeyInput = true;
							eNowCheakType = TYPE_STRAT;

							if((*vecEquip)[i]->m_iNum <= 0)
								(*vecEquip)[i]->m_bFree = true;

							break;
						}
					}
					else if((*vecEquip)[i]->m_bFree == true && m_bKeyInput == false && (*vecEquip)[i]->m_eID == eCharID && (*vecEquip)[i]->m_bSelect == true)
					{
						if(EquipCheak((*vecEquip)[i]->m_iType, (*vecEquip)[i]->m_iImgCode, (*vecEquip)[i]->m_iItemCode, eCharID) == true)
						{
							if((*vecEquip)[i]->m_iType == TYPE_ACCESSORY2 && (*vecEquip)[i]->m_bFree == true && (*vecEquip)[i]->m_eID == eCharID)
							{
								(*vecEquip)[i]->m_iNum += 1;
								(*vecEquip)[i]->m_iType = TYPE_ACCESSORY1;
							}

							(*vecEquip)[i]->m_bFree = false;
							(*vecEquip)[i]->m_eID = CHARACTER_END;
							m_bKeyInput = true;
							(*vecEquip)[i]->m_bSelect = false;
							eNowCheakType = TYPE_STRAT;

							break;
						}
						else
						{
							(*vecEquip)[i]->m_bSelect = false;
							m_bKeyInput = true;

							break;
						}
					}

					for(size_t j = 0; j < vecEquip->size(); ++j)
						(*vecEquip)[j]->m_bSelect = false;

					(*vecEquip)[i]->m_bSelect = true;
					eNowCheakType = (*vecEquip)[i]->m_iType;

					m_bKeyInput = true;
				}
			}

			if((*vecEquip)[i]->m_bFree == true)
				iA = 127;
			else
				iA = 255;

			wsprintf(szNum, L"%d", (*vecEquip)[i]->m_iNum);

			if((*vecEquip)[i]->m_bCursorOn == true)
			{
				if((*vecEquip)[i]->m_bFree == false)
					iR = 255;
				else
				{
					iB = 255;
					iA = 255;
				}
			}

			if((*vecEquip)[i]->m_bSelect == true)
			{
				DrawSprite(RESOURCE_TYPE_STATIC, L"SlotCheak", 196.f * float((i - iContinue) % 2) + 265.f, 20.f * float((i - iContinue) / 2) + 240.f - (((iX + iY - 10) / 195.f) * 20 * m_fScroll), 0, NULL);

				for(int j = 0; j < 8; ++j)
					DrawSprite(RESOURCE_TYPE_STATIC, L"SlotCheak", 196.f * float((i - iContinue) % 2) + 285.f + (j * 20.f), 20.f * float((i - iContinue) / 2) + 240.f - (((iX + iY - 10) / 195.f) * 20 * m_fScroll), 1, NULL);

				DrawSprite(RESOURCE_TYPE_STATIC, L"SlotCheak", 196.f * float((i - iContinue) % 2) + 445.f, 20.f * float((i - iContinue) / 2) + 240.f - (((iX + iY - 10) / 195.f) * 20 * m_fScroll), 2, NULL);
			}

			DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 196.f * float(iItemScroll % 2) + 270.f
				, 20.f * float(iItemScroll / 2) + 240.f - (((iX + iY - 10) / 195.f) * 20 * m_fScroll)
				, (*vecEquip)[i]->m_iImgCode, NULL);

			CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(iA, iR, 0, iB)
				, 196.f * float(iItemScroll % 2) + 300.f
				, 20.f * float(iItemScroll / 2) + 230.f - (((iX + iY - 10) / 195.f) * 20 * m_fScroll));

			CPage::DrawText(szNum, D3DCOLOR_ARGB(iA, iR, 0, iB), 196.f * float(iItemScroll % 2) + 440.f
				, 20.f * float(iItemScroll / 2) + 230.f - (((iX + iY - 10) / 195.f) * 20 * m_fScroll));
		}
		++iItemScroll;
	}

	if(iY + iX > 10) // 이하 스크롤 출력
	{
		for(int i = 0; i < 11; ++i)
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 240.f + (i * 20), 3, NULL); // 밧줄?

		if(m_bUpScrollNow == false)
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 240.f, 4, NULL);
		else
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 240.f, 5, NULL); // 스크롤 시작

		if(m_bDownScrollNow == false)
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 460.f, 0, NULL);
		else
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 460.f, 1, NULL); // 스크롤 끝

		if(m_bMoveScrollNow == false)
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 262.f + m_fScroll, 7, NULL);
		else
			DrawSprite(RESOURCE_TYPE_STATIC, L"Scroll", 695.f, 262.f + m_fScroll, 8, NULL); // 스크롤 위치를 나타내는 텍스쳐
	}
}

bool ENGINE::CCharacterEquipPage::EquipCheak(int eEquip, int iImgCode, int iItemCode, eCharacterID eCharID) // 같은 슬롯에 장비가 있는지 확인하는 함수
{
	for(size_t i = 0; i < vecEquip->size(); ++i)
	{
		if(eEquip == TYPE_CAP)
		{
			for(size_t j = 0; j < vecEquip->size(); ++j)
				if((*vecEquip)[j]->m_iType == TYPE_CAP && (*vecEquip)[i]->m_iItemCode == iItemCode && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
				{
					(*vecEquip)[j]->m_bFree = false;
					(*vecEquip)[j]->m_iNum += 1;
					(*vecEquip)[j]->m_eID = CHARACTER_END;
				}
		}

		if(eEquip == TYPE_WEAPON)
		{
			for(size_t j = 0; j < vecEquip->size(); ++j)
				if((*vecEquip)[j]->m_iType == TYPE_WEAPON && (*vecEquip)[i]->m_iItemCode == iItemCode && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
				{
					(*vecEquip)[j]->m_bFree = false;
					(*vecEquip)[j]->m_iNum = +1;
					(*vecEquip)[j]->m_eID = CHARACTER_END;
				}
		}

		if(eEquip == TYPE_ARMOUR)
		{
			for(size_t j = 0; j < vecEquip->size(); ++j)
				if((*vecEquip)[j]->m_iType == TYPE_ARMOUR && (*vecEquip)[i]->m_iItemCode == iItemCode && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
				{
					(*vecEquip)[j]->m_bFree = false;
					(*vecEquip)[j]->m_iNum += 1;
					(*vecEquip)[j]->m_eID = CHARACTER_END;
				}
		}

		if(eEquip == TYPE_SHOES)
		{
			for(size_t j = 0; j < vecEquip->size(); ++j)
				if((*vecEquip)[j]->m_iType == TYPE_SHOES && (*vecEquip)[i]->m_iItemCode == iItemCode && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
				{
					(*vecEquip)[j]->m_bFree = false;
					(*vecEquip)[j]->m_iNum += 1;
					(*vecEquip)[j]->m_eID = CHARACTER_END;
				}
		}

		if(eEquip == TYPE_WEAR)
		{
			for(size_t j = 0; j < vecEquip->size(); ++j)
				if((*vecEquip)[j]->m_iType == TYPE_WEAR && (*vecEquip)[i]->m_iItemCode == iItemCode && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
				{
					(*vecEquip)[j]->m_bFree = false;
					(*vecEquip)[j]->m_iNum += 1;
					(*vecEquip)[j]->m_eID = CHARACTER_END;
				}
		}

		if(eEquip == TYPE_SHIELD)
		{
			for(size_t j = 0; j < vecEquip->size(); ++j)
				if((*vecEquip)[j]->m_iType == TYPE_SHIELD && (*vecEquip)[i]->m_iItemCode == iItemCode && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
				{
					(*vecEquip)[j]->m_bFree = false;
					(*vecEquip)[j]->m_iNum += 1;
					(*vecEquip)[j]->m_eID = CHARACTER_END;
				}
		}

		if(eEquip >= TYPE_ACCESSORY1)
		{
			bool		bCheak1 = false, bCheak2 = false;
			for(size_t j = 0; j < vecEquip->size(); ++j)
				if((*vecEquip)[j]->m_iType == TYPE_ACCESSORY1 && (*vecEquip)[j]->m_eID == eCharID && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
					bCheak1 = true;

			for(size_t j = 0; j < vecEquip->size(); ++j)
				if((*vecEquip)[j]->m_iType == TYPE_ACCESSORY2 && (*vecEquip)[j]->m_eID == eCharID && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[j]->m_eID == eCharID)
					bCheak2 = true;

			if(bCheak1 == true && bCheak2 == false)
			{
				for(size_t j = 0; j < vecEquip->size(); ++j)
				{
					if((*vecEquip)[j]->m_iItemCode == iItemCode && (*vecEquip)[j]->m_iType == TYPE_ACCESSORY1)
						(*vecEquip)[j]->m_iType = TYPE_ACCESSORY2;
				}
				return true;
			}

			if(bCheak1 == true && bCheak2 == true)
			{
				for(size_t j = 0; j < vecEquip->size(); ++j)
					if((*vecEquip)[j]->m_iType == TYPE_ACCESSORY1 && (*vecEquip)[i]->m_iType != TYPE_ACCESSORY2 && (*vecEquip)[j]->m_bFree == true && (*vecEquip)[i]->m_iItemCode == iItemCode)
					{
						(*vecEquip)[j]->m_bFree = false;
						(*vecEquip)[j]->m_iNum += 1;
						(*vecEquip)[j]->m_eID = CHARACTER_END;

						return true;
					}
			}
		}
	}
	return true;
}

int ENGINE::CCharacterEquipPage::ImgCheak(int eEquip, eCharacterID eCharID) // 이제 필요없음
{
	wsprintf(szEquip, L"????");

	return 1;
}