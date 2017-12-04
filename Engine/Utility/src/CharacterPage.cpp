#include "CharacterPage.h"

#include "Export_Function.h"
#include "SubPageObserver.h"

ENGINE::CCharacterPage::CCharacterPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
:CPage(_pOwner, pSprite), m_pSubObserver(NULL)
{
	m_pSubObserver = CSubPageObserver::Create(m_pOwner);

	ENGINE::GetInfoSubject()->Subscribe(m_pSubObserver);
}

ENGINE::CCharacterPage::~CCharacterPage(void)
{
	Release();
}

int ENGINE::CCharacterPage::Update(void)
{
	return 0;
}

void ENGINE::CCharacterPage::Render(void)
{

}

void ENGINE::CCharacterPage::Release(void)
{
	SAFE_DELETE(m_pSubObserver);
}