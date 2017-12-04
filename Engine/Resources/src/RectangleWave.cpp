#include "RectangleWave.h"

ENGINE::CRectangleWave::CRectangleWave(void)
: m_fHight(20.f)
{

}

ENGINE::CRectangleWave::~CRectangleWave(void)
{
	
}

ENGINE::CRectangleWave* ENGINE::CRectangleWave::Create(
	DWORD _dwCountX,
	DWORD _dwCountZ,
	DWORD _dwInterval)
{
	CRectangleWave* pInstance = new CRectangleWave;
	HRESULT hr = pInstance->Initialize(_dwCountX, _dwCountZ, _dwInterval);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

HRESULT ENGINE::CRectangleWave::Initialize(DWORD _dwCountX, DWORD _dwCountZ, DWORD _dwInterval)
{
	m_dwVertexSize = sizeof(VERTEX_TEXTURE);
	m_dwVertexCount = _dwCountX * _dwCountZ;
	m_dwVertexFVF = VERTEX_TEXTURE_FVF;
	m_dwTriangleCount = (_dwCountX - 1) * (_dwCountZ - 1) * 2;
	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	HRESULT hr = CVIBuffer::Initialize();
	if FAILED(hr)
		return hr;

	VERTEX_TEXTURE* pVertexTexture = NULL;

	m_pVertexBuffer->Lock(0, 0, (void**)&pVertexTexture, 0);
	
	int		iIndex = 0;
	float	fUp = 0.f;
	float	fBox[33][33] = {0.f, 0.f};
	float	fBoxTex[33][33] = {0.f, 0.f};

	for(unsigned int z = 0; z < _dwCountZ; ++z)
	{
		for(unsigned int x = 0; x < _dwCountX; ++x)
		{
			if(x + z < 33)
			{
				if(z == 0)
					fBox[x][z] = 0.f;
				else if(x == 0)
					fBox[x][z] = 0.f;
				else if(fBox[x - 1][z - 1] == fBox[x - 1][z])
					fBox[x][z] = fBox[x - 1][z] + 1.f;
				else if(fBox[x - 1][z - 1] != fBox[x - 1][z])
					fBox[x][z] = fBox[x - 1][z];
			}
			else
			{
				if(z <= (_dwCountZ - 1) / 2)
					fBox[x][z] = fBox[x - 1][z] - 1.f;
				else
				{
					fBox[x][z] = fBox[x][(_dwCountZ/ 2) - (z - (_dwCountZ/ 2))];
				}
			}

			fBoxTex[x][z] = fBox[x][z];
		}
	}

	for(unsigned int z = 0; z < _dwCountZ; ++z)
	{
		for(unsigned int x = 0; x < _dwCountX; ++x)
		{
			fBox[x][z] = sinf((fBoxTex[x][z] / 16384.f) * 90.f * 3.1415f);
		}
	}

	for(int z = 0; z < int(_dwCountZ); ++z)
	{
		for(int x = 0; x < int(_dwCountX); ++x)
		{
			iIndex = z * int(_dwCountX) + x;

			SetD3DXVector3(&pVertexTexture[iIndex].vPos, float(x) * _dwInterval, fBox[x][z] * m_fHight, float(z) * _dwInterval);
			pVertexTexture[iIndex].vTex = D3DXVECTOR2((x / (_dwCountX - 1.f)), (z / (_dwCountZ - 1.f)));
		}
	}

	m_pVertexBuffer->Unlock();

	INDEX32* pIndex = NULL;
	int iTriangleCount = 0;

	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	//iIndex = 0;

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
