#include "TriangleColor.h"

ENGINE::CTriangleColor::CTriangleColor(void)
{

}

ENGINE::CTriangleColor::~CTriangleColor(void)
{
	
}

ENGINE::CTriangleColor* ENGINE::CTriangleColor::Create(void)
{
	CTriangleColor* pInstance = new CTriangleColor;
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

HRESULT ENGINE::CTriangleColor::Initialize(void)
{
	m_dwVertexSize = sizeof(VERTEX_COLOR);
	m_dwVertexCount = 3;
	m_dwVertexFVF = VERTEX_COLOR_FVF;
	m_dwTriangleCount = 1;

	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	// create vertex buffer & index buffer
	HRESULT hr = CVIBuffer::Initialize();
	if FAILED(hr)
		return hr;

	// get ptr to buffer and..
	VERTEX_COLOR* pVertexColor = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertexColor, 0);
	// 락이란?
	// MSDN에서는, 락을 걸고 포인터를 얻어온다.. 정도로 소개한다만,
	// 내가 쓰는 동안 다른 애들(렌더라던가?)이 못쓰게 막는 것, 같은 느낌이라고 보면 될 듯..
	// MSDN 예제에서는 미리 set되어있는 구조체 배열 등이 있고 이를 memcpy로 보낸다..
	// 그리고 엄청 느리다고 한다.

	// fill..
	SetD3DXVector3(&pVertexColor[0].vPos, 0.f, 1.f, 0.f);
	pVertexColor[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	SetD3DXVector3(&pVertexColor[1].vPos, 1.f, -1.f, 0.f);
	pVertexColor[1].dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	SetD3DXVector3(&pVertexColor[2].vPos, -1.f, -1.f, 0.f);
	pVertexColor[2].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	m_pVertexBuffer->Unlock();

	INDEX32* pIndex = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	SetIndex32(&pIndex[0], 0, 1, 2);

	m_pIndexBuffer->Unlock();

	return S_OK;
}
