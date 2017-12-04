#include "Texture.h"

#include "Export_Function.h"

ENGINE::CTexture::CTexture(void)
:m_iContainerSize(0)
{

}

ENGINE::CTexture::~CTexture(void)
{
	Release();
}

ENGINE::CTexture* ENGINE::CTexture::Create(eTextureType _eTextureType, const wstring& _strFilePath, DWORD _dwCnt)
{
	CTexture* pInstance = new CTexture;
	HRESULT hr = pInstance->LoadTexture(_eTextureType, _strFilePath, _dwCnt);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

void ENGINE::CTexture::Render(int _iIndex /*= -1*/)
{
	if (_iIndex >= m_iContainerSize || _iIndex < 0)
		return;

	ENGINE::GetDevice()->SetTexture(0, m_TextureVec[_iIndex]);
}

ENGINE::CGraphicResource* ENGINE::CTexture::CloneResource(ENGINE::CGameObject* _pOwner)
{
	++(*m_pReferenceCount);

	CTexture* pInstance = new CTexture(*this);
	pInstance->SetOwner(_pOwner);
	return pInstance;
}

HRESULT ENGINE::CTexture::LoadTexture(eTextureType _eTextureType, const wstring& _strFilePath, DWORD _dwCnt)
{
	m_TextureVec.reserve(_dwCnt);

	TCHAR szFullPath[MAX_PATH] = {0};
	for (DWORD i = 0; i < _dwCnt; ++i)
	{
		wsprintf(szFullPath, _strFilePath.c_str(), i);

		LPDIRECT3DBASETEXTURE9 pTexture = NULL;
		HRESULT hr = NULL;
		switch (_eTextureType)
		{
		case TEXTURE_TYPE_NORMAL:
			hr = D3DXCreateTextureFromFile(
				ENGINE::GetDevice(),
				szFullPath,
				(LPDIRECT3DTEXTURE9*)&pTexture);
			break;

		case TEXTURE_TYPE_CUBE:
			hr = D3DXCreateCubeTextureFromFile(
				ENGINE::GetDevice(),
				szFullPath,
				(LPDIRECT3DCUBETEXTURE9*)&pTexture);
			break;
		}
		if FAILED(hr)
		{
			UTIL::SHOW_ERROR(hr, L"D3DXCreateTextureFromFile() Failed!");
			return hr;
		}

		m_TextureVec.push_back(pTexture);
	}

	m_iContainerSize = m_TextureVec.size();

	return S_OK;
}

void ENGINE::CTexture::Release(void)
{
	if ((*m_pReferenceCount) == 0)
	{
		for (int i = 0; i < m_iContainerSize; ++i)
		{
			SAFE_RELEASE(m_TextureVec[i]);
		}
		m_TextureVec.clear();

		CGraphicResource::Release();
	}
	else
	{
		--(*m_pReferenceCount);
	}
}
