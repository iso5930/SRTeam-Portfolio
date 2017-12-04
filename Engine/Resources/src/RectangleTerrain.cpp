#include "RectangleTerrain.h"

ENGINE::CRectangleTerrain::CRectangleTerrain(void)
{

}

ENGINE::CRectangleTerrain::~CRectangleTerrain(void)
{
	
}

ENGINE::CRectangleTerrain* ENGINE::CRectangleTerrain::Create(
	DWORD _dwCountX,
	DWORD _dwCountZ,
	DWORD _dwInterval)
{
	CRectangleTerrain* pInstance = new CRectangleTerrain;
	HRESULT hr = pInstance->Initialize(_dwCountX, _dwCountZ, _dwInterval);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

HRESULT ENGINE::CRectangleTerrain::Initialize(
	DWORD _dwCountX,
	DWORD _dwCountZ,
	DWORD _dwInterval)
{
	m_dwVertexSize = sizeof(VERTEX_COLOR);
	m_dwVertexCount = _dwCountX * _dwCountZ;
	m_dwVertexFVF = VERTEX_COLOR_FVF;
	m_dwTriangleCount = (_dwCountX - 1) * (_dwCountZ - 1) * 2;

	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	HRESULT hr = CVIBuffer::Initialize();
	if FAILED(hr)
		return hr;

	VERTEX_COLOR* pVertexColor = NULL;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertexColor, 0);
	
	int iIndex = 0;
	for (DWORD z = 0; z < _dwCountZ; ++z)
	{
		for (DWORD x = 0; x < _dwCountX; ++x)
		{
			iIndex = z * _dwCountX + x;

			SetD3DXVector3(&pVertexColor[iIndex].vPos, float(x * _dwInterval), 0.f, float(z * _dwInterval));
			pVertexColor[iIndex].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
		}
	}

	m_pVertexBuffer->Unlock();

	INDEX32* pIndex = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	iIndex = 0;
	int iTriangleCount = 0;
	for (DWORD z = 0; z < _dwCountZ - 1; ++z)
	{
		for (DWORD x = 0; x < _dwCountX - 1; ++x)
		{
			iIndex = z * _dwCountX + x;

			SetIndex32(&pIndex[iTriangleCount], iIndex + _dwCountX, iIndex + _dwCountX + 1, iIndex + 1);
			++iTriangleCount;

			SetIndex32(&pIndex[iTriangleCount], iIndex + _dwCountX, iIndex + 1, iIndex);
			++iTriangleCount;
		}
	}

	m_pIndexBuffer->Unlock();

	return S_OK;
}
