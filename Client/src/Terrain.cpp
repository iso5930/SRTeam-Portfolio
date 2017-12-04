#include "stdafx.h"
#include "Terrain.h"

#include "Transform.h"
#include "Export_Function.h"
#include "Tile.h"
#include "TerrainInfo.h"

CTerrain::CTerrain(eObjectType _eObjectType)
:CGameObject(_eObjectType)
,m_pInfo(NULL)
,m_pVIBuffer(NULL)
,m_pTerrainInfo(NULL)
{

}

CTerrain::~CTerrain(void)
{
	Release();
}

CTerrain* CTerrain::Create(eObjectType _eObjectType, wstring _wstrFilePath, wstring _wstrKey)
{
	CTerrain* pInstance = new CTerrain(_eObjectType);
	HRESULT hr = pInstance->Initialize(_wstrFilePath, _wstrKey);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CTerrain::Update(void)
{
	ENGINE::CGameObject::Update();

	return 0;
}

void CTerrain::Render(void)
{
	ENGINE::GetDevice()->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	
	for(DWORD i = 0; i < m_vecTile.size(); ++i)
	{
		m_vecTile[i]->Render();
	}
}

HRESULT CTerrain::Initialize(wstring _wstrFilePath, wstring _wstrKey)
{
	m_strResourceKey = _wstrKey;

	LoadMapBuffer(_wstrFilePath, _wstrKey);

	HRESULT hr = AddComponent();
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CTerrain::Initialize(void)
{
	return S_OK;
}

HRESULT CTerrain::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_DYNAMIC, m_strResourceKey);
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(m_strResourceKey, pComponent));

	return S_OK;
}

void CTerrain::Release(void)
{
	vector<CTile*>::iterator iter = m_vecTile.begin();
	vector<CTile*>::iterator iter_end = m_vecTile.end();

	for(iter; iter != m_vecTile.end(); ++iter)
	{
		delete *iter;
	}
	m_vecTile.clear();

	//SAFE_DELETE(m_pVertexColor);
}

void CTerrain::LoadMapBuffer(wstring	_wstrFilePath, wstring	_wstrKey)
{
	DWORD		dwByte = 0;
	HANDLE		hFile = CreateFile(_wstrFilePath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	int iCountX, iCountZ; 

	ReadFile(hFile, &iCountX, sizeof(int), &dwByte, NULL);
	ReadFile(hFile, &iCountZ, sizeof(int), &dwByte, NULL);

	m_pTerrainInfo = ENGINE::CTerrainInfo::Create(this, iCountX, iCountZ);
	if (m_pTerrainInfo == NULL)
		return;
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Terrain_Info", m_pTerrainInfo));

	//m_dwVertexCountX = iCountX;
	//m_dwVertexCountZ = iCountZ;

	//m_pVertexColor = new VERTEX_COLOR[iCountX * iCountZ];

	for(int i = 0; i < iCountX * iCountZ; ++i)
	{
		ReadFile(hFile, &(m_pTerrainInfo->m_pVertexColor[i]), sizeof(VERTEX_COLOR), &dwByte, NULL);
	}

	ENGINE::GetResourceManager()->AddBuffer(RESOURCE_TYPE_DYNAMIC, ENGINE::CVIBuffer::BUFFER_TYPE_RECTANGLE_TERRAIN,
		_wstrKey, iCountX, iCountZ);

	ENGINE::GetResourceManager()->WriteVerticies(RESOURCE_TYPE_DYNAMIC, _wstrKey, m_pTerrainInfo->m_pVertexColor);

	while(true)
	{
		VERTEX_TEXTURE*	pVertexTexture = new VERTEX_TEXTURE[4];

		int	iTextureIndex = 0;
		
		ReadFile(hFile, pVertexTexture, sizeof(VERTEX_TEXTURE) * 4, &dwByte, NULL);
		ReadFile(hFile, &iTextureIndex, sizeof(int), &dwByte, NULL);
		
		CTile*	pTile = CTile::Create(OBJECT_TYPE_DYNAMIC, pVertexTexture, iTextureIndex);

		if(dwByte == 0)
		{
			delete pTile;
			break;
		}

		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
}
