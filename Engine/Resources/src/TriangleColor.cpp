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
	// ���̶�?
	// MSDN������, ���� �ɰ� �����͸� ���´�.. ������ �Ұ��Ѵٸ�,
	// ���� ���� ���� �ٸ� �ֵ�(���������?)�� ������ ���� ��, ���� �����̶�� ���� �� ��..
	// MSDN ���������� �̸� set�Ǿ��ִ� ����ü �迭 ���� �ְ� �̸� memcpy�� ������..
	// �׸��� ��û �����ٰ� �Ѵ�.

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
