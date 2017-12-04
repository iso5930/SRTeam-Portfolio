#include "RectangleTexture.h"

ENGINE::CRectangleTexture::CRectangleTexture(void)
{

}

ENGINE::CRectangleTexture::~CRectangleTexture(void)
{
	
}

ENGINE::CRectangleTexture* ENGINE::CRectangleTexture::Create(void)
{
	CRectangleTexture* pInstance = new CRectangleTexture;
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

HRESULT ENGINE::CRectangleTexture::Initialize(void)
{
	m_dwVertexSize = sizeof(VERTEX_TEXTURE);
	m_dwVertexCount = 4;
	m_dwVertexFVF = VERTEX_TEXTURE_FVF;
	m_dwTriangleCount = 2;

	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	HRESULT hr = CVIBuffer::Initialize();
	if FAILED(hr)
		return hr;

	VERTEX_TEXTURE* pVertexTexture = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertexTexture, 0);
	
	SetD3DXVector3(&pVertexTexture[0].vPos, -1.f, 1.f, 0.f);
	SetD3DXVector2(&pVertexTexture[0].vTex, 0.f, 0.f);

	SetD3DXVector3(&pVertexTexture[1].vPos, 1.f, 1.f, 0.f);
	SetD3DXVector2(&pVertexTexture[1].vTex, 1.f, 0.f);

	SetD3DXVector3(&pVertexTexture[2].vPos, 1.f, -1.f, 0.f);
	SetD3DXVector2(&pVertexTexture[2].vTex, 1.f, 1.f);

	SetD3DXVector3(&pVertexTexture[3].vPos, -1.f, -1.f, 0.f);
	SetD3DXVector2(&pVertexTexture[3].vTex, 0.f, 1.f);

	m_pVertexBuffer->Unlock();

	INDEX32* pIndex = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	SetIndex32(&pIndex[0], 0, 1, 2);
	SetIndex32(&pIndex[1], 0, 2, 3);

	m_pIndexBuffer->Unlock();

	return S_OK;
}
