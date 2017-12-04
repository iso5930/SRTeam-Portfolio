#include "TerrainInfo.h"

ENGINE::CTerrainInfo::CTerrainInfo(ENGINE::CGameObject* _pOwner)
:CComponent(_pOwner)
,m_pVertexColor(NULL)
,m_dwVertexCountX(0)
,m_dwVertexCountZ(0)
{
	
}

ENGINE::CTerrainInfo::~CTerrainInfo(void)
{
	SAFE_DELETE_ARRAY(m_pVertexColor);
}

ENGINE::CTerrainInfo* ENGINE::CTerrainInfo::Create(ENGINE::CGameObject* _pOwner, DWORD _dwVertexCountX, DWORD _dwVertexCountZ)
{
	CTerrainInfo* pInstance = new CTerrainInfo(_pOwner);
	HRESULT hr = pInstance->Initialize(_dwVertexCountX, _dwVertexCountZ);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

HRESULT ENGINE::CTerrainInfo::Initialize(DWORD _dwVertexCountX, DWORD _dwVertexCountZ)
{
	m_dwVertexCountX = _dwVertexCountX;
	m_dwVertexCountZ = _dwVertexCountZ;

	m_pVertexColor = new VERTEX_COLOR[m_dwVertexCountX * m_dwVertexCountZ];
	ZeroMemory(m_pVertexColor, sizeof(m_pVertexColor));

	return S_OK;
}
