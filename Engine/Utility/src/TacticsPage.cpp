#include "TacticsPage.h"

#include "Export_Function.h"

ENGINE::CTacticsPage::CTacticsPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
:CPage(_pOwner, pSprite)
{

}

ENGINE::CTacticsPage::~CTacticsPage(void)
{
	Release();
}

ENGINE::CTacticsPage* ENGINE::CTacticsPage::Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
{
	CTacticsPage* pPage = new CTacticsPage(_pOwner, pSprite);

	if(FAILED(pPage->Init()))
	{
		SAFE_DELETE(pPage);
	}

	return pPage;
}

int ENGINE::CTacticsPage::Update(void)
{
	return 0;
}

void ENGINE::CTacticsPage::Render(void)
{
	TEXINFO* pTexInfo = NULL;

	pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"TacticsPage", 0);

	float fX = pTexInfo->ImgInfo.Width / 2.f;
	float fY = pTexInfo->ImgInfo.Height / 2.f;

	D3DXVECTOR3 vCenter(fX, fY, 0.f);

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 472.f, 293.f, 0.f);

	m_pSprite->SetTransform(&matTrans);

	m_pSprite->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT ENGINE::CTacticsPage::Init(void)
{
	return S_OK;
}

void ENGINE::CTacticsPage::Release(void)
{

}