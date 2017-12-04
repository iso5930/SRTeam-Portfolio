#include "RectangleColor.h"

ENGINE::CRectangleColor::CRectangleColor(void)
{

}

ENGINE::CRectangleColor::~CRectangleColor(void)
{
	
}

ENGINE::CRectangleColor* ENGINE::CRectangleColor::Create(void)
{
	CRectangleColor* pInstance = new CRectangleColor;
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

HRESULT ENGINE::CRectangleColor::Initialize(void)
{
	m_dwVertexSize = sizeof(VERTEX_COLOR);
	m_dwVertexCount = 4;
	m_dwVertexFVF = VERTEX_COLOR_FVF;
	m_dwTriangleCount = 2;

	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	HRESULT hr = CVIBuffer::Initialize();
	if FAILED(hr)
		return hr;

	VERTEX_COLOR* pVertexColor = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertexColor, 0);
	
	SetD3DXVector3(&pVertexColor[0].vPos, -1.f, 1.f, 0.f);
	pVertexColor[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	SetD3DXVector3(&pVertexColor[1].vPos, 1.f, 1.f, 0.f);
	pVertexColor[1].dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	SetD3DXVector3(&pVertexColor[2].vPos, 1.f, -1.f, 0.f);
	pVertexColor[2].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	SetD3DXVector3(&pVertexColor[3].vPos, -1.f, -1.f, 0.f);
	pVertexColor[3].dwColor = D3DCOLOR_ARGB(255, 255, 255, 0);

	m_pVertexBuffer->Unlock();

	INDEX32* pIndex = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	SetIndex32(&pIndex[0], 0, 1, 2);
	SetIndex32(&pIndex[1], 0, 2, 3);

	m_pIndexBuffer->Unlock();

	return S_OK;
}
