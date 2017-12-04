#include "Item.h"

ENGINE::CItem::CItem(eObjectType _eObjectType)
:CGameObject(_eObjectType)
, m_iNum(0)
, m_bFree(false)
, m_eID(CHARACTER_END)
, m_iType(TYPE_STRAT)
, m_iImgCode(0)
, m_iItemCode(0)
, m_bSelect(false)
, m_bCursorOn(false)
, m_iBP(0)
, m_iAtk(0)
, m_iDef(0)
, m_iSpd(0)
, m_iMag(0)
, m_iCri(0)

{
	wsprintf(m_szName, L"이름없음");
}

ENGINE::CItem::~CItem(void)
{

}

HRESULT ENGINE::CItem::Initialize(void)
{
	return S_OK;
}

HRESULT ENGINE::CItem::Initialize(eObjectType _eObjectType)
{
	return S_OK;
}

int ENGINE::CItem::Update(void)
{
	return 0;
}

ENGINE::CItem* ENGINE::CItem::Create(eObjectType _eObjectType)
{
	CItem* pItem = new CItem(_eObjectType);

	return pItem;
}

void ENGINE::CItem::Render(void)
{

}