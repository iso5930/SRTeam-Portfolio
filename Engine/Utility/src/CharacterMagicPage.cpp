#include "CharacterMagicPage.h"

#include "Export_Function.h"

#include "GroupObserver.h"
#include "SubPageObserver.h"
#include "CharacterGroup.h"
#include "Character.h"
#include "Ability.h"
#include "AbilityGroup.h"

ENGINE::CCharacterMagicPage::CCharacterMagicPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
:CCharacterPage(_pOwner, pSprite), m_pGroupObserver(NULL)
{

}

ENGINE::CCharacterMagicPage::~CCharacterMagicPage(void)
{	
	Release();
}

ENGINE::CCharacterMagicPage* ENGINE::CCharacterMagicPage::Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
{
	CCharacterMagicPage* pPage = new CCharacterMagicPage(_pOwner, pSprite);

	if(FAILED(pPage->Init()))
	{
		SAFE_DELETE(pPage);
	}

	return pPage;
}

HRESULT ENGINE::CCharacterMagicPage::Init(void)
{
	m_pGroupObserver = ENGINE::CGroupObserver::Create(m_pOwner);

	ENGINE::GetInfoSubject()->Subscribe(m_pGroupObserver);

	return S_OK;
}

void ENGINE::CCharacterMagicPage::Release(void)
{
	SAFE_DELETE(m_pGroupObserver);
}	

int ENGINE::CCharacterMagicPage::Update(void)
{
	eCharacterID eCharID = dynamic_cast<CSubPageObserver*>(m_pSubObserver)->GetCharCur();
	eAbilityID eAbilID = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetAbilityID();
	
	if(eAbilID == ABILITYID_SKILL)
	{
		return 0;
	}
	
	return 0;
}

void ENGINE::CCharacterMagicPage::Render(void)
{
	CPage::DrawSprite(RESOURCE_TYPE_STATIC, L"CharItemPage", 472.f, 293.f, 0, NULL);

	eCharacterID eCharID = dynamic_cast<CSubPageObserver*>(m_pSubObserver)->GetCharCur();
	eAbilityID eAbilID = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetAbilityID();
	CHARACTER_STATE* pCharState = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetCharacterState();
	
	if(eAbilID == ABILITYID_SKILL)
	{
		return;
	}

	switch(eCharID)
	{
	case CHARACTER_SIZZ:
		DrawText(L"시즈의 상태", D3DCOLOR_ARGB(255, 0, 0, 0), 400 - 68, 300 - 188);
		break;
	}

	DrawFont("Barrier Point", 439.f, 300 - 174, 8.f, 0.f);
	DrawFont("Hit Point", 439.f, 300 - 148, 8.f, 0.f);

	DrawSprite(RESOURCE_TYPE_STATIC, L"BarFrame", 513.f, 130.f, 0, NULL); //Barrier Point
	DrawSprite(RESOURCE_TYPE_STATIC, L"BarFrame", 513.f, 156.f, 0, NULL);

	RECT rcBP = {0, 0, 0, 3};
	RECT rcHP = {0, 0, 0, 3};

	float fPersent = float(pCharState->iBarrierPoint) / float(pCharState->iMaxBarrierPoint) * 100;
	float fLenget = (float)142 * fPersent / 100;

	rcBP.right = (long)fLenget;

	DrawSprite(RESOURCE_TYPE_STATIC, L"Gauge", 513.f, 130.f, 0, &rcBP); //Barrier Point

	fPersent = float(pCharState->iHitPoint) / float(pCharState->iMaxHitPoint) * 100;
	fLenget = (float)142 * fPersent / 100;

	rcHP.right = (long)fLenget;

	DrawSprite(RESOURCE_TYPE_STATIC, L"Gauge", 513.f, 156.f, 1, &rcHP); //Hit Point

	vector<eAbilityType>* vecAbilitype = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetAbilityType();

	for(size_t i = 0; i < vecAbilitype->size(); ++i)
	{
		switch((*vecAbilitype)[i])
		{
		case ABILITY_FIRE:
			CPage::DrawFont("Fire", 590.f, 125.f + (i * 17.f), 8.f, 0.f);
			break;

		case ABILITY_WATER:
			CPage::DrawFont("Water", 590.f, 125.f + (i * 17.f), 8.f, 0.f);
			break;

		case ABILITY_WIND:
			CPage::DrawFont("W ind", 590.f, 125.f + (i * 17.f), 8.f, 0.f);
			break;

		case ABILITY_EARTH:
			CPage::DrawFont("Earth", 590.f, 125.f + (i * 17.f), 8.f, 0.f);
			break;

		case ABILITY_ISP:
			CPage::DrawFont("I.S.P", 590.f, 125.f + (i * 17.f), 8.f, 0.f);
			break;

		case ABILITY_ESP:
			CPage::DrawFont("E.S.P", 590.f, 125.f + (i * 17.f), 8.f, 0.f);
			break;

		case ABILITY_PSP:
			CPage::DrawFont("P.S.P", 590.f, 125.f + (i * 17.f), 8.f, 0.f);
			break;
		}
	}
	
	CPage::BarTextDraw(pCharState->iAbility1, pCharState->iMaxAbility1, 635.f, 125.f, 7.f, 0.f);
	CPage::BarTextDraw(pCharState->iAbility2, pCharState->iMaxAbility2, 635.f, 142.f, 7.f, 0.f);
	CPage::BarTextDraw(pCharState->iAbility3, pCharState->iMaxAbility3, 635.f, 159.f, 7.f, 0.f);

	vector<ENGINE::CAbility*>* vecAbility = m_pGroupObserver->GetCharacterGroup()->GetCharacter(eCharID)->GetAbilityGroup()->GetAbility();
	
	m_iScrollY = 0;

	if(vecAbility->size() > 12)
	{
		m_iScrollY = vecAbility->size() - 12;
	}

	for(size_t i = 0; i < vecAbility->size() - m_iScrollY; ++i) //위의 값들은 스크롤이 추가되면 수정...
	{
		(*vecAbility)[i]->DrawAbility(181.f + (i * 20.f)); //이렇게 주면 내부적으로 돌면서 알아서 출력...
	}
}