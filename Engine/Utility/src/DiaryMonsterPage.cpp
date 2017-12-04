#include "DiaryMonsterPage.h"

#include "Export_Function.h"

ENGINE::CDiaryMonsterPage::CDiaryMonsterPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
:CDiaryPage(_pOwner, pSprite)
{

}

ENGINE::CDiaryMonsterPage::~CDiaryMonsterPage(void)
{
	Release();
}

ENGINE::CDiaryMonsterPage* ENGINE::CDiaryMonsterPage::Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
{
	CDiaryMonsterPage* pPage = new CDiaryMonsterPage(_pOwner, pSprite);

	if(FAILED(pPage->Init()))
	{
		SAFE_DELETE(pPage);
	}

	return pPage;
}

HRESULT ENGINE::CDiaryMonsterPage::Init(void)
{
	return S_OK;
}

void ENGINE::CDiaryMonsterPage::Release(void)
{

}

int ENGINE::CDiaryMonsterPage::Update(void)
{
	return 0;
}	

void ENGINE::CDiaryMonsterPage::Render(void)
{
	TEXINFO* pTexInfo = NULL;

	pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"DiaryMonsterPage", 0);

	float fX = pTexInfo->ImgInfo.Width / 2.f;
	float fY = pTexInfo->ImgInfo.Height / 2.f;

	D3DXVECTOR3 vCenter(fX, fY, 0.f);

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 472.f, 293.f, 0.f);

	m_pSprite->SetTransform(&matTrans);

	m_pSprite->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}