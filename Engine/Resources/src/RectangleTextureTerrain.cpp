#include "RectangleTextureTerrain.h"
#include "ResourceManager.h"
#include "Texture.h"

ENGINE::CRectangleTextureTerrain::CRectangleTextureTerrain(void)
{

}

ENGINE::CRectangleTextureTerrain::~CRectangleTextureTerrain(void)
{

}

ENGINE::CRectangleTextureTerrain* ENGINE::CRectangleTextureTerrain::Create(DWORD _dwCountX, DWORD _dwCountZ, DWORD _dwInterval)
{
	CRectangleTextureTerrain* pInstance = new CRectangleTextureTerrain;

	HRESULT hr = pInstance->Initialize(_dwCountX, _dwCountZ, _dwInterval);

	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

HRESULT ENGINE::CRectangleTextureTerrain::Initialize(DWORD _dwCountX, DWORD _dwCountZ, DWORD _dwInterval)
{
	m_dwVertexSize = sizeof(VERTEX_TEXTURE);
	m_dwVertexCount = _dwCountX * _dwCountZ;
	m_dwVertexFVF = VERTEX_TEXTURE_FVF;
	m_dwTriangleCount = (_dwCountX - 1) * (_dwCountZ - 1) * 2;

	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	m_vecTile.reserve(_dwCountX * _dwCountZ);


	HRESULT hr = CVIBuffer::Initialize();
	if FAILED(hr)
		return hr;

	VERTEX_TEXTURE* pVertexTexture = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertexTexture, 0);

	int iIndex = 0;

	for(DWORD z = 0; z < _dwCountZ; ++z)
	{
		for(DWORD x = 0; x < _dwCountX; ++x)
		{
			iIndex = z * _dwCountX + x;

			SetD3DXVector3(&pVertexTexture[iIndex].vPos, float(x * _dwInterval), 0.f, float(z * _dwInterval));
			//CRectangleTexture*	pRectangleTexture = new CRectangleTexture;
			//pRectangleTexture->Create();

			//m_pvecTile->push_back(pRectangleTexture);
		}
	}


	VERTEX_TEXTURE*	pVertexTexture2 = NULL;

	//m_pVertexBuffer->Lock(0, 0, (void**)*pVertexTexture2, 0);

	iIndex = 0;
	int iTriangleCount = 0;
	
	for(DWORD z = 0; z < _dwCountZ - 1; ++z)
	{
		for(DWORD x = 0; x < _dwCountX - 1; ++x)
		{
			iIndex = z * _dwCountX + x;

			pVertexTexture2 = new VERTEX_TEXTURE[4];

			pVertexTexture2[0] = pVertexTexture[iIndex + _dwCountX];
			SetD3DXVector2(&pVertexTexture2[0].vTex, 0.f, 0.f);

			pVertexTexture2[1] = pVertexTexture[iIndex + _dwCountX + 1];
			SetD3DXVector2(&pVertexTexture2[1].vTex , 1.f, 0.f);

			pVertexTexture2[2] = pVertexTexture[iIndex + 1];
			SetD3DXVector2(&pVertexTexture2[2].vTex , 1.f, 1.f);

			pVertexTexture2[3] = pVertexTexture[iIndex];
			SetD3DXVector2(&pVertexTexture2[3].vTex, 0.f, 1.f);

			CRectangleTexture* pRcTex = CRectangleTexture::Create();
			pRcTex->SetBuffer(pVertexTexture2);

			//ENGINE::CComponent*	pComponent = NULL;

			m_vecTile.push_back(pRcTex);
		}
	}

	m_pVertexBuffer->Unlock();

	return S_OK;
}

void ENGINE::CRectangleTextureTerrain::Render(int _iIndex /*= -1*/)
{
	for(DWORD i = 0; i < m_vecTile.size(); ++i)
	{
		m_vecTile[i]->Render(0);
	}
}

ENGINE::CGraphicResource* ENGINE::CRectangleTextureTerrain::CloneResource(void)
{
	++(*m_pReferenceCount);

	return new CRectangleTextureTerrain(*this);
}
