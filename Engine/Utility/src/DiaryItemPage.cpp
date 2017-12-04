#include "DiaryItemPage.h"

#include "Export_Function.h"

ENGINE::CDiaryItemPage::CDiaryItemPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
:CDiaryPage(_pOwner, pSprite)
{

}

ENGINE::CDiaryItemPage::~CDiaryItemPage(void)
{
	Release();
}

ENGINE::CDiaryItemPage* ENGINE::CDiaryItemPage::Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
{
	CDiaryItemPage* pPage = new CDiaryItemPage(_pOwner, pSprite);

	if(FAILED(pPage->Init()))
	{
		SAFE_DELETE(pPage);
	}

	return pPage;
}

HRESULT ENGINE::CDiaryItemPage::Init(void)
{
	return S_OK;
}

void ENGINE::CDiaryItemPage::Release(void)
{

}

int ENGINE::CDiaryItemPage::Update(void)
{
	return 0;
}

void ENGINE::CDiaryItemPage::Render(void)
{
	TEXINFO* pTexInfo = NULL;

	pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"DiaryItemPage", 0);

	float fX = pTexInfo->ImgInfo.Width / 2.f;
	float fY = pTexInfo->ImgInfo.Height / 2.f;

	D3DXVECTOR3 vCenter(fX, fY, 0.f);

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 472.f, 293.f, 0.f);

	m_pSprite->SetTransform(&matTrans);

	m_pSprite->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}