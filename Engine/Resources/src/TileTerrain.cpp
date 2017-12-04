#include "stdafx.h"
#include "TileTerrain.h"
#include "RectangleTexture.h"
#include "ResourceManager.h"
#include "Export_Function.h"

CTileTerrain::CTileTerrain(eObjectType _eObjectType)
: CGameObject(_eObjectType)
, m_pVertexTexture(NULL)
, m_pTileVertex(NULL)
, m_iCountX(0)
, m_iCountZ(0)
{

}

CTileTerrain::~CTileTerrain(void)
{
	Release();
}

int CTileTerrain::Update(void)
{
	return 0;
}

CTileTerrain* CTileTerrain::Create(eObjectType _eObjectType, const DWORD& _dwCountX, const DWORD& _dwCountZ, const DWORD& _dwInterval, const wstring& _wstrKey)
{
	CTileTerrain*	pTileTerrain = new CTileTerrain(_eObjectType);
	
	HRESULT hr = pTileTerrain->Initialize(_dwCountX, _dwCountZ, _dwInterval, _wstrKey);

	if FAILED(hr)
		SAFE_DELETE(pTileTerrain);

	return  pTileTerrain;
}

HRESULT CTileTerrain::Initialize(const DWORD& _dwCountX, const DWORD& _dwCountZ, const DWORD& _dwInterval, const wstring& _wstrKey)
{
	m_iCountX = _dwCountX;
	m_iCountZ = _dwCountZ;

	//m_pVertexColor = new VERTEX_COLOR[_dwCountX * _dwCountZ];
	
	//ENGINE::GetResourceManager()->ReadVerticies(RESOURCE_TYPE_DYNAMIC, _wstrKey.c_str(), m_pVertexColor);

	m_pVertexTexture = new VERTEX_TEXTURE[_dwCountX * _dwCountZ];

	ZeroMemory(m_pVertexTexture, sizeof(VERTEX_TEXTURE) * (_dwCountX * _dwCountZ));
	
	int iIndex = 0;
	
	for(DWORD z = 0; z < _dwCountZ; ++z)
	{
		for(DWORD x = 0; x < _dwCountX; ++x)
		{
			iIndex = z * _dwCountX + x;
			SetD3DXVector3(&m_pVertexTexture[iIndex].vPos, float(x * _dwInterval), 0.f, float(z * _dwInterval));
		}
	}

	iIndex = 0;
	
	for(DWORD z = 0; z < _dwCountZ - 1; ++z)
	{
		for(DWORD x = 0; x < _dwCountX - 1; ++x)
		{
			iIndex = z * _dwCountX + x;

			m_pTileVertex = new VERTEX_TEXTURE[4];

			m_pTileVertex[0] = m_pVertexTexture[iIndex + _dwCountX];
			SetD3DXVector2(&m_pTileVertex[0].vTex, 0.f, 0.f);

			m_pTileVertex[1] = m_pVertexTexture[iIndex + _dwCountX + 1];
			SetD3DXVector2(&m_pTileVertex[1].vTex , 1.f, 0.f);

			m_pTileVertex[2] = m_pVertexTexture[iIndex + 1];
			SetD3DXVector2(&m_pTileVertex[2].vTex , 1.f, 1.f);

			m_pTileVertex[3] = m_pVertexTexture[iIndex];
			SetD3DXVector2(&m_pTileVertex[3].vTex, 0.f, 1.f);

			CTile*	pTile = CTile::Create(OBJECT_TYPE_DYNAMIC, m_pTileVertex);
			m_vecTile.push_back(pTile);
		}
	}

	return S_OK;
}

HRESULT CTileTerrain::Initialize(void)
{
	return S_OK;
}

void CTileTerrain::Render(void)
{
	for(DWORD i = 0; i < m_vecTile.size(); ++i)
	{
		m_vecTile[i]->Render();
	}
}

void CTileTerrain::Release(void)
{
	vector<CTile*>::iterator iter = m_vecTile.begin();

	for(iter; iter != m_vecTile.end(); ++iter)
	{
		delete *iter;
	}
	m_vecTile.clear();

	if(m_pVertexTexture != NULL)
	{
		SAFE_DELETE_ARRAY(m_pVertexTexture);
	}

	//if(m_pTileVertex != NULL)
	//{
	//	SAFE_DELETE_ARRAY(m_pTileVertex);
	//}

}

void CTileTerrain::SetTileTexture(int _iTileIndex, int _iTextureIndex, eTextureRotation _eTextureRotation)
{
	m_vecTile[_iTileIndex]->SetTileTexture(_iTextureIndex, _eTextureRotation);
}