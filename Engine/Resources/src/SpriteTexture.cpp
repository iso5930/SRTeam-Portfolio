#include "SpriteTexture.h"

#include "Export_Function.h"

ENGINE::CSpriteTexture::CSpriteTexture(void)
{

}

ENGINE::CSpriteTexture::~CSpriteTexture(void)
{
	Release();
}

ENGINE::CSpriteTexture* ENGINE::CSpriteTexture::Create(const wstring& _strFilePath, const DWORD& _dwCount, D3DCOLOR _Color/* = NULL*/)
{
	CSpriteTexture* pSpriteTexture = new CSpriteTexture;

	if(FAILED(pSpriteTexture->LoadSpriteTexture(_strFilePath, _dwCount, _Color)))
	{
		SAFE_DELETE(pSpriteTexture);
	}

	return pSpriteTexture;
}

void ENGINE::CSpriteTexture::Render(int _iIndex /*= -1*/){ }

ENGINE::CGraphicResource* ENGINE::CSpriteTexture::CloneResource(ENGINE::CGameObject* _pOwner)
{
	return NULL;
}

HRESULT ENGINE::CSpriteTexture::LoadSpriteTexture(const wstring& _strFilePath, const DWORD& _dwCount, D3DCOLOR _Color/* = NULL*/)
{
	LPDIRECT3DDEVICE9 pDevice = ENGINE::GetDevice();

	m_vecSprite.reserve(_dwCount);

	TCHAR szFullPath[MAX_PATH] = L"";

	for(size_t i = 0; i < _dwCount; ++i)
	{
		TEXINFO* pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		wsprintf(szFullPath, _strFilePath.c_str(), i);

		D3DXGetImageInfoFromFile(szFullPath, &pTexInfo->ImgInfo);

		D3DXCreateTextureFromFileEx(pDevice, szFullPath, pTexInfo->ImgInfo.Width, pTexInfo->ImgInfo.Height, pTexInfo->ImgInfo.MipLevels, 0, pTexInfo->ImgInfo.Format, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, _Color, &pTexInfo->ImgInfo, NULL, &pTexInfo->pTexture);

		m_vecSprite.push_back(pTexInfo);
	}

	return S_OK;
}

void ENGINE::CSpriteTexture::Release(void)
{
	for(size_t i = 0; i < m_vecSprite.size(); ++i)
	{
		SAFE_RELEASE(m_vecSprite[i]->pTexture);
		delete m_vecSprite[i];
		m_vecSprite[i] = NULL;
	}
	m_vecSprite.clear();

	CGraphicResource::Release();
}

TEXINFO* ENGINE::CSpriteTexture::GetTexInfo(const DWORD& _dwCount)
{
	return m_vecSprite[_dwCount];
}