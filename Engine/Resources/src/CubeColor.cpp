#include "CubeColor.h"

ENGINE::CCubeColor::CCubeColor(void)
{

}

ENGINE::CCubeColor::~CCubeColor(void)
{

}

ENGINE::CCubeColor* ENGINE::CCubeColor::Create(void)
{
	CCubeColor* pInstance = new CCubeColor;
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

HRESULT ENGINE::CCubeColor::Initialize(void)
{
	m_dwVertexSize = sizeof(VERTEX_COLOR);
	m_dwVertexCount = 8;
	m_dwVertexFVF = VERTEX_COLOR_FVF;
	m_dwTriangleCount = 12;

	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	HRESULT hr = CVIBuffer::Initialize();
	if FAILED(hr)
		return hr;

	VERTEX_COLOR* pVertexCube = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertexCube, 0);

	pVertexCube[0].vPos = D3DXVECTOR3(-1.f, 1.f, -1.f);
	pVertexCube[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertexCube[1].vPos = D3DXVECTOR3(1.f, 1.f, -1.f);
	pVertexCube[1].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertexCube[2].vPos = D3DXVECTOR3(1.f, -1.f, -1.f);
	pVertexCube[2].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertexCube[3].vPos = D3DXVECTOR3(-1.f, -1.f, -1.f);
	pVertexCube[3].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertexCube[4].vPos = D3DXVECTOR3(-1.f, 1.f, 1.f);
	pVertexCube[4].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	pVertexCube[5].vPos = D3DXVECTOR3(1.f, 1.f, 1.f);
	pVertexCube[5].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	pVertexCube[6].vPos = D3DXVECTOR3(1.f, -1.f, 1.f);
	pVertexCube[6].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	pVertexCube[7].vPos = D3DXVECTOR3(-1.f, -1.f, 1.f);
	pVertexCube[7].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_pVertexBuffer->Unlock();

	INDEX32* pIndex32 = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex32, 0);

	// x+
	pIndex32[0]._1 = 1;
	pIndex32[0]._2 = 5;
	pIndex32[0]._3 = 6;

	pIndex32[1]._1 = 1;
	pIndex32[1]._2 = 6;
	pIndex32[1]._3 = 2;

	// x-
	pIndex32[2]._1 = 4;
	pIndex32[2]._2 = 0;
	pIndex32[2]._3 = 3;

	pIndex32[3]._1 = 4;
	pIndex32[3]._2 = 3;
	pIndex32[3]._3 = 7;

	// y+
	pIndex32[4]._1 = 4;
	pIndex32[4]._2 = 5;
	pIndex32[4]._3 = 1;

	pIndex32[5]._1 = 4;
	pIndex32[5]._2 = 1;
	pIndex32[5]._3 = 0;

	// y-
	pIndex32[6]._1 = 3;
	pIndex32[6]._2 = 2;
	pIndex32[6]._3 = 6;

	pIndex32[7]._1 = 3;
	pIndex32[7]._2 = 6;
	pIndex32[7]._3 = 7;

	// z+
	pIndex32[8]._1 = 7;
	pIndex32[8]._2 = 6;
	pIndex32[8]._3 = 5;

	pIndex32[9]._1 = 7;
	pIndex32[9]._2 = 5;
	pIndex32[9]._3 = 4;

	// z-
	pIndex32[10]._1 = 0;
	pIndex32[10]._2 = 1;
	pIndex32[10]._3 = 2;

	pIndex32[11]._1 = 0;
	pIndex32[11]._2 = 2;
	pIndex32[11]._3 = 3;

	m_pIndexBuffer->Unlock();

	return S_OK;
}
