#include "stdafx.h"
#include "Tile.h"
#include "RectangleTexture.h"
#include "Export_Function.h"
#include "Texture.h"

CTile::CTile(eObjectType _eObjectType)
: CGameObject(_eObjectType)
, m_iTextureIndex(0)
, m_pRcTex(NULL)
, m_pTexture(NULL)
{
	
}

CTile::~CTile(void)
{
	Release();
}

CTile*	CTile::Create(eObjectType _eObjectType, VERTEX_TEXTURE* _pVertexTexture, int _iTextureIndex)
{
	CTile*		pTile = new CTile(_eObjectType);

	HRESULT hr = pTile->Initialize(_pVertexTexture, _iTextureIndex);

	if FAILED(hr)
		SAFE_DELETE(pTile);

	return pTile;
}

HRESULT	CTile::Initialize(VERTEX_TEXTURE*	_pVertexTexture, int _iTextureIndex)
{
	m_pRcTex = ENGINE::CRectangleTexture::Create();
	m_pRcTex->WriteVerticies(_pVertexTexture);

	m_pVertex = _pVertexTexture;
	m_iTextureIndex = _iTextureIndex;

	ENGINE::CComponent*	pComponent = NULL;
	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_DYNAMIC, L"Tile");
	m_pTexture = dynamic_cast<ENGINE::CTexture*>(pComponent);

	return S_OK;
}

HRESULT CTile::Initialize(void)
{
	return S_OK;
}

void CTile::Render(void)
{
	m_pTexture->Render(m_iTextureIndex);
	m_pRcTex->Render(0);
}

int CTile::Update(void)
{

	return 0;
}

void CTile::Release(void)
{
	SAFE_DELETE(m_pVertex);
	SAFE_DELETE(m_pRcTex);
	SAFE_DELETE(m_pTexture);
}