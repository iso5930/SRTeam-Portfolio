#include "CharacterStatePage.h"

#include "Export_Function.h"
#include "SubPageObserver.h"
#include "GroupObserver.h"
#include "CharacterGroup.h"
#include "Character.h"
#include "Item.h"
#include "Equip.h"

ENGINE::CCharacterStatePage::CCharacterStatePage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
:CCharacterPage(_pOwner, pSprite)
{

}

ENGINE::CCharacterStatePage::~CCharacterStatePage(void)
{
	Release();
}

HRESULT ENGINE::CCharacterStatePage::Init(void)
{
	m_pGroupObserver = ENGINE::CGroupObserver::Create(m_pOwner);

	ENGINE::GetInfoSubject()->Subscribe(m_pGroupObserver);

	//버퍼 생성...
	m_dwVtxSize = sizeof(VERTEX_COLOR_RHW);
	m_dwVtxCnt = 6;
	m_dwVtxFVF = VERTEX_COLOR_RHW_FVF;
	m_dwTriCnt = 5;
	m_dwIdxSize = sizeof(INDEX32);

	ENGINE::GetDevice()->CreateVertexBuffer(m_dwVtxSize * m_dwVtxCnt, 0, m_dwVtxFVF, D3DPOOL_MANAGED, &m_pVB, NULL);
	ENGINE::GetDevice()->CreateVertexBuffer(m_dwVtxSize * m_dwVtxCnt, 0, m_dwVtxFVF, D3DPOOL_MANAGED, &m_pVB2, NULL);
	ENGINE::GetDevice()->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIB, NULL);

	m_pVtxRHW = new VERTEX_COLOR_RHW[m_dwVtxCnt];
	m_pVtxRHW2 = new VERTEX_COLOR_RHW[m_dwVtxCnt];
	m_pOriginVtxRHW = new VERTEX_COLOR_RHW[m_dwVtxCnt];

	m_pVtxRHW[0].vPos = D3DXVECTOR3(377.f, 313.f, 0.f);
	m_pVtxRHW[0].fRHW = 1.f;
	m_pVtxRHW[0].dwColor = D3DCOLOR_ARGB(255, 214, 223, 228);

	m_pVtxRHW[1].vPos = D3DXVECTOR3(377.f, 269.f, 0.f);
	m_pVtxRHW[1].fRHW = 1.f;
	m_pVtxRHW[1].dwColor = D3DCOLOR_ARGB(255, 214, 223, 228);

	m_pVtxRHW[2].vPos = D3DXVECTOR3(419.f, 300.f, 0.f);
	m_pVtxRHW[2].fRHW = 1.f;
	m_pVtxRHW[2].dwColor = D3DCOLOR_ARGB(255, 214, 223, 228);

	m_pVtxRHW[3].vPos = D3DXVECTOR3(403.f, 348.f, 0.f);
	m_pVtxRHW[3].fRHW = 1.f;
	m_pVtxRHW[3].dwColor = D3DCOLOR_ARGB(255, 214, 223, 228);

	m_pVtxRHW[4].vPos = D3DXVECTOR3(351.f, 348.f, 0.f);
	m_pVtxRHW[4].fRHW = 1.f;
	m_pVtxRHW[4].dwColor = D3DCOLOR_ARGB(255, 214, 223, 228);

	m_pVtxRHW[5].vPos = D3DXVECTOR3(337.f, 300.f, 0.f);
	m_pVtxRHW[5].fRHW = 1.f;
	m_pVtxRHW[5].dwColor = D3DCOLOR_ARGB(255, 214, 223, 228);

	for(int i = 0; i < 5; ++i)
	{
		m_pOriginVtxRHW[i] = m_pVtxRHW[i];
		m_pVtxRHW2[i] = m_pOriginVtxRHW[i];

		m_pVtxRHW2[i].dwColor = D3DCOLOR_ARGB(255, 170, 182, 220);
	}

	INDEX32* pIndex = NULL;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._1 = 0;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 2;

	pIndex[1]._1 = 0;
	pIndex[1]._2 = 2;
	pIndex[1]._3 = 3;

	pIndex[2]._1 = 0;
	pIndex[2]._2 = 3;
	pIndex[2]._3 = 4;

	pIndex[3]._1 = 0;
	pIndex[3]._2 = 4;
	pIndex[3]._3 = 5;

	pIndex[4]._1 = 0;
	pIndex[4]._2 = 5;
	pIndex[4]._3 = 1;

	m_pIB->Unlock();

	return S_OK;
}

int ENGINE::CCharacterStatePage::Update(void)
{
	eCharacterID eCharID = dynamic_cast<ENGINE::CSubPageObserver*>(m_pSubObserver)->GetCharCur();
	CHARACTER_STATE* pCharState = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetCharacterState();
	
	int iMaxState = 0;

	int* pState = &pCharState->iSTR;

	for(int i = 0; i < 10; ++i)
	{
		if(iMaxState < (*pState))
		{
			iMaxState = (*pState);
		}
		++pState;
	}

	pState = &pCharState->iSTR;

	for(int i = 0; i < 5; ++i)
	{
		float fPersent = (float)(*pState) / (float)iMaxState * 100; //몇퍼센트인지 구하기

		float fLength = (float)44 * fPersent / 100; //전체의 길이에서 몇퍼센트인지 구하기

		D3DXVECTOR3 vDist = m_pOriginVtxRHW[i + 1].vPos - m_pVtxRHW[0].vPos;

		D3DXVec3Normalize(&vDist, &vDist);

		vDist *= fLength;

		m_pVtxRHW[i + 1].vPos = m_pVtxRHW[0].vPos + vDist;

		++pState;
	}

	for(int i = 0; i < 5; ++i)
	{
		float fPersent = (float)(*pState) / (float)iMaxState * 100;

		float fLength = (float)44 * fPersent / 100;

		D3DXVECTOR3 vDist = m_pOriginVtxRHW[i + 1].vPos - m_pVtxRHW2[0].vPos;

		D3DXVec3Normalize(&vDist, &vDist);

		vDist *= fLength;

		m_pVtxRHW2[i + 1].vPos = m_pVtxRHW2[0].vPos + vDist;
		m_pVtxRHW2[i + 1].dwColor = D3DCOLOR_ARGB(255, 170, 182, 220);

		++pState;
	}

	VERTEX_COLOR_RHW*		pVtxRHW = NULL;

	m_pVB->Lock(0, 0, (void**)&pVtxRHW, 0);

	memcpy(pVtxRHW, m_pVtxRHW, sizeof(VERTEX_COLOR_RHW) * m_dwVtxCnt);

	m_pVB->Unlock();

	VERTEX_COLOR_RHW* pVtxRHW2 = NULL;

	m_pVB2->Lock(0, 0, (void**)&pVtxRHW2, 0);

	memcpy(pVtxRHW2, m_pVtxRHW2, sizeof(VERTEX_COLOR_RHW) * m_dwVtxCnt);

	m_pVB2->Unlock();

	return 0;
}

void ENGINE::CCharacterStatePage::Render(void)
{
	eCharacterID eCharID = dynamic_cast<ENGINE::CSubPageObserver*>(m_pSubObserver)->GetCharCur();

	DrawSprite(RESOURCE_TYPE_STATIC, L"CharStatePage", 472.f, 293.f, eCharID, NULL); //BackGround

	CPage::DrawFont("Level", 240.f, 169.f, 8.f, 0.f);
	CPage::DrawFont("Exp", 240.f, 186.f, 8.f, 0.f);
	CPage::DrawFont("Next", 313.f, 186.f, 8.f, 0.f);
	CPage::DrawFont("Barrier Point", 240.f, 205.f, 8.f, 0.f);
	CPage::DrawFont("Hit Point", 240.f, 240.f, 8.f, 0.f);

	CPage::DrawFont("STR", 240.f, 282.f, 8.f, 0.f);
	CPage::DrawFont("VIT", 240.f, 300.f, 8.f, 0.f);
	CPage::DrawFont("INT", 240.f, 318.f, 8.f, 0.f);
	CPage::DrawFont("AGI", 240.f, 336.f, 8.f, 0.f);
	CPage::DrawFont("LUK", 240.f, 354.f, 8.f, 0.f);

	CPage::DrawFont("ATK", 448.f, 282.f, 8.f, 0.f);
	CPage::DrawFont("DEF", 448.f, 300.f, 8.f, 0.f);
	CPage::DrawFont("MAG", 448.f, 318.f, 8.f, 0.f);
	CPage::DrawFont("SPD", 448.f, 336.f, 8.f, 0.f);
	CPage::DrawFont("CRI", 448.f, 354.f, 8.f, 0.f);

	//Default 값

	CHARACTER_STATE* pCharState = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetCharacterState();

	DrawSprite(RESOURCE_TYPE_STATIC, L"BarFrame", 350.f, 213.f, 0, NULL); //Barrier Point
	DrawSprite(RESOURCE_TYPE_STATIC, L"BarFrame", 350.f, 249.f, 0, NULL); //Hit Point

	RECT rcBP = {0, 0, 0, 3};
	RECT rcHP = {0, 0, 0, 3};

	float fPersent = float(pCharState->iBarrierPoint) / float(pCharState->iMaxBarrierPoint) * 100;
	float fLenget = (float)142 * fPersent / 100;

	rcBP.right = (long)fLenget;

	DrawSprite(RESOURCE_TYPE_STATIC, L"Gauge", 350.f, 213.f, 0, &rcBP); //Barrier Point

	fPersent = float(pCharState->iHitPoint) / float(pCharState->iMaxHitPoint) * 100;
	fLenget = (float)142 * fPersent / 100;

	rcHP.right = (long)fLenget;

	DrawSprite(RESOURCE_TYPE_STATIC, L"Gauge", 350.f, 249.f, 1, &rcHP); //Hit Point

	vector<eAbilityType>* vecAbilitype = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetAbilityType();

	for(size_t i = 0; i < vecAbilitype->size(); ++i)
	{
		switch((*vecAbilitype)[i])
		{
		case ABILITY_FIRE:
			CPage::DrawFont("Fire", 427.f, 205.f + (i * 24.f), 8.f, 0.f);
			break;

		case ABILITY_WATER:
			CPage::DrawFont("Water", 427.f, 205.f + (i * 24.f), 8.f, 0.f);
			break;

		case ABILITY_WIND:
			CPage::DrawFont("W ind", 427.f, 205.f + (i * 24.f), 8.f, 0.f);
			break;

		case ABILITY_EARTH:
			CPage::DrawFont("Earth", 427.f, 205.f + (i * 24.f), 8.f, 0.f);
			break;

		case ABILITY_ISP:
			CPage::DrawFont("I.S.P", 427.f, 205.f + (i * 24.f), 8.f, 0.f);
			break;

		case ABILITY_ESP:
			CPage::DrawFont("E.S.P", 427.f, 205.f + (i * 24.f), 8.f, 0.f);
			break;

		case ABILITY_PSP:
			CPage::DrawFont("P.S.P", 427.f, 205.f + (i * 24.f), 8.f, 0.f);
			break;
		}
	}

	CPage::DrawFont_Int(pCharState->iLevel, 287.f, 167.f, 8.f, 0.f);
	CPage::DrawFont_Int(pCharState->iExp, 287.f, 186.f, 8.f, 0.f);
	CPage::DrawFont_Int(pCharState->iNextExp, 350.f, 186.f, 8.f, 0.f);

	int* pState = &pCharState->iSTR;

	for(int i = 0; i < 5; ++i)
	{
		DrawFont_Int((*pState), 291.f, 280.f + (i * 18.5f), 8.f, 0.f);
		++pState;
	}

	pState = &pCharState->iATK;

	for(int i = 0; i < 5; ++i)
	{
		DrawFont_Int((*pState), 500.f, 280.f + (i * 18.5f), 8.f, 0.f);
		++pState;
	}
	
	int* pAbility = &pCharState->iAbility1;
	int* pAbilityMax = &pCharState->iMaxAbility1;
	
	for(int i = 0; i < 3; ++i)
	{
		DrawSprite(RESOURCE_TYPE_STATIC, L"AbilityFrame", 482.f, 193.f + (i * 24.f), 0, NULL);

		float fPersent = (float)(*pAbility) / (float)(*pAbilityMax) * 100;
		float fLength = (float)28 * fPersent / 100;

		RECT rcAbility = {0, 0, (long)fLength, 22};

		DrawSprite(RESOURCE_TYPE_STATIC, L"Ability", 482.f, 193.f + (i * 24.f), i, &rcAbility);

		++pAbility;
		++pAbilityMax;
	}

	CPage::BarTextDraw(pCharState->iBarrierPoint, pCharState->iMaxBarrierPoint, 371.f, 204.f, 7.f, 0.f);
	CPage::BarTextDraw(pCharState->iHitPoint, pCharState->iMaxHitPoint, 371.f, 240.f, 7.f, 0.f);

	CPage::BarTextDraw(pCharState->iAbility1, pCharState->iMaxAbility1, 506.f, 204.f, 7.f, 0.f);
	CPage::BarTextDraw(pCharState->iAbility2, pCharState->iMaxAbility2, 506.f, 228.f, 7.f, 0.f);
	CPage::BarTextDraw(pCharState->iAbility3, pCharState->iMaxAbility3, 506.f, 252.f, 7.f, 0.f);

	//오각형 렌더 시작!!
	m_pSprite->End();

	ENGINE::GetDevice()->BeginScene();

	ENGINE::GetDevice()->SetTexture(0, NULL);

	ENGINE::GetDevice()->SetStreamSource(0, m_pVB2, 0, m_dwVtxSize);

	ENGINE::GetDevice()->SetFVF(m_dwVtxFVF);

	ENGINE::GetDevice()->SetIndices(m_pIB); 

	ENGINE::GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);

	ENGINE::GetDevice()->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);

	ENGINE::GetDevice()->SetFVF(m_dwVtxFVF);

	ENGINE::GetDevice()->SetIndices(m_pIB);

	ENGINE::GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);

	ENGINE::GetDevice()->EndScene();

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//=========================

	//장비창으로 부터 정보를 받아와서 출력을 하자...
	vector<ENGINE::CItem*>* vecEquip = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetEquip()->GetvecEquip();

	bool	bCap = false, bWea = false, bArm = false, bSho = false, bWear = false, bShi = false, bAcc1 = false, bAcc2 = false;
	for(size_t i = 0; i < vecEquip->size(); ++i)
	{
		if(eCharID != ((*vecEquip)[i])->m_eID)
		{
			continue;
		}

		switch((*vecEquip)[i]->m_iType)
		{
		case 1:
			if(eCharID == ((*vecEquip)[i])->m_eID)
			{
				CPage::DrawText(((*vecEquip)[i])->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 240.f, 375.f);
				bCap = true;
				DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 341.f, 385.f, (*vecEquip)[i]->m_iImgCode, NULL);
				//이미지도 같이
			}
			break;

		case 2:
			if(eCharID == ((*vecEquip)[i])->m_eID)
			{
				CPage::DrawText(((*vecEquip)[i])->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 240.f, 404.f);
				bWea = true;
				DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 341.f, 413.f, (*vecEquip)[i]->m_iImgCode, NULL);
			}
			break;

		case 3:
			if(eCharID == ((*vecEquip)[i])->m_eID)
			{
				CPage::DrawText(((*vecEquip)[i])->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 240.f, 433.f);
				bArm = true;
				DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 341.f, 441.f, (*vecEquip)[i]->m_iImgCode, NULL);
			}
			break;

		case 4:
			if(eCharID == ((*vecEquip)[i])->m_eID)
			{
				CPage::DrawText(((*vecEquip)[i])->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 240.f, 462.f);
				bSho = true;
				DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 341.f, 469.f, (*vecEquip)[i]->m_iImgCode, NULL);
			}
			break;

		case 5:
			if(eCharID == ((*vecEquip)[i])->m_eID)
			{
				CPage::DrawText(((*vecEquip)[i])->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 438.f, 375.f);
				bWear = true;
				DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 424.f, 385.f, (*vecEquip)[i]->m_iImgCode, NULL);
			}
			break;

		case 6:
			if(eCharID == ((*vecEquip)[i])->m_eID)
			{
				CPage::DrawText(((*vecEquip)[i])->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 438.f, 404.f);
				bShi = true;
				DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 424.f, 413.f, (*vecEquip)[i]->m_iImgCode, NULL);
			}
			break;

		case 7:
			if(eCharID == ((*vecEquip)[i])->m_eID)
			{
				CPage::DrawText(((*vecEquip)[i])->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 438.f, 433.f);
				DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 424.f, 441.f, (*vecEquip)[i]->m_iImgCode, NULL);
			}
			else
			{
				CPage::DrawText(L"(악세사리없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 438.f, 433.f);
			}
			break;

		case 8:
			if(eCharID == ((*vecEquip)[i])->m_eID)
			{
				CPage::DrawText(((*vecEquip)[i])->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 438.f, 462.f);
				DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 424.f, 469.f, (*vecEquip)[i]->m_iImgCode, NULL);
			}
			else
			{
				CPage::DrawText(L"(악세사리없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 438.f, 462.f);
			}
			break;
		}
	}
	if(bCap == false)
		CPage::DrawText(L"(모자없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 240.f, 375.f);
	if(bWea == false)
		CPage::DrawText(L"(무기없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 240.f, 404.f);
	if(bArm == false)
		CPage::DrawText(L"(갑옷없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 240.f, 433.f);
	if(bSho == false)
		CPage::DrawText(L"(신발없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 240.f, 462.f);
	if(bWear == false)
		CPage::DrawText(L"(걸칠것없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 438.f, 375.f);
	if(bShi == false)
		CPage::DrawText(L"(방패없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 438.f, 404.f);

	CPage::DrawText(L"(악세사리없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 438.f, 433.f);
	CPage::DrawText(L"(악세사리없음)", D3DCOLOR_ARGB(255, 0, 0, 0), 438.f, 462.f);

	//일단은 위치만 잡아 놓자..
}

void ENGINE::CCharacterStatePage::Release(void)
{
	SAFE_DELETE(m_pGroupObserver);

	SAFE_DELETE_ARRAY(m_pVtxRHW);
	SAFE_DELETE_ARRAY(m_pVtxRHW2);
	SAFE_DELETE_ARRAY(m_pOriginVtxRHW);
}

ENGINE::CCharacterStatePage* ENGINE::CCharacterStatePage::Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
{
	CCharacterStatePage* pPage = new CCharacterStatePage(_pOwner, pSprite);

	if(FAILED(pPage->Init()))
	{
		SAFE_DELETE(pPage);
	}

	return pPage;
}