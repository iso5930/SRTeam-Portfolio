#include "stdafx.h"
#include "Tile.h"
#include "RectangleTexture.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Export_Function.h"
#include "Texture.h"

CTile::CTile(eObjectType _eObjectType)
: CGameObject(_eObjectType)
, m_iTextureIndex(86)
, m_pRcTex(NULL)
, m_pTexture(NULL)
, m_eTextureRotation(TEXTURE_ROTATION_UP)
{
	m_pVertex = NULL;
}

CTile::~CTile(void)
{
	Release();
}

int CTile::Update(void)
{
	return 0;
}

CTile*	CTile::Create(eObjectType _eObjectType, VERTEX_TEXTURE* _pVertexTexture)
{
	CTile*		pTile = new CTile(_eObjectType);

	HRESULT hr = pTile->Initialize(_pVertexTexture);

	if FAILED(hr)
		SAFE_DELETE(pTile);

	return pTile;
}

HRESULT	CTile::Initialize(VERTEX_TEXTURE* _pVertexTexture)
{
	m_pRcTex = ENGINE::CRectangleTexture::Create();
	m_pRcTex->WriteVerticies(_pVertexTexture);
	//m_pRcTex->SetBuffer(_pVertexTexture);
	//
	m_pVertex = _pVertexTexture;

	ENGINE::CComponent*	pComponent = NULL;
	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Tile");
	m_pTexture = dynamic_cast<ENGINE::CTexture*>(pComponent);
	//

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

void CTile::Release(void)
{
	SAFE_DELETE(m_pVertex);
	SAFE_DELETE(m_pRcTex);
	SAFE_DELETE(m_pTexture);
}

void CTile::SetTileTexture(int _iTextureIndex, eTextureRotation _eTextureRotation)
{
	switch(_eTextureRotation)
	{
	case TEXTURE_ROTATION_UP :
		SetD3DXVector2(&m_pVertex[0].vTex, 0.f, 0.f);
		SetD3DXVector2(&m_pVertex[1].vTex, 1.f, 0.f);
		SetD3DXVector2(&m_pVertex[2].vTex, 1.f, 1.f);
		SetD3DXVector2(&m_pVertex[3].vTex, 0.f, 1.f);
		break;

	case TEXTURE_ROTATION_RIGHT :
		SetD3DXVector2(&m_pVertex[0].vTex, 0.f, 1.f);
		SetD3DXVector2(&m_pVertex[1].vTex, 0.f, 0.f);
		SetD3DXVector2(&m_pVertex[2].vTex, 1.f, 0.f);
		SetD3DXVector2(&m_pVertex[3].vTex, 1.f, 1.f);
		break;

	case TEXTURE_ROTATION_DOWN :
		SetD3DXVector2(&m_pVertex[0].vTex, 1.f, 1.f);
		SetD3DXVector2(&m_pVertex[1].vTex, 0.f, 1.f);
		SetD3DXVector2(&m_pVertex[2].vTex, 0.f, 0.f);
		SetD3DXVector2(&m_pVertex[3].vTex, 1.f, 0.f);
		break;

	case TEXTURE_ROTATION_LEFT :
		SetD3DXVector2(&m_pVertex[0].vTex, 1.f, 0.f);
		SetD3DXVector2(&m_pVertex[1].vTex, 1.f, 1.f);
		SetD3DXVector2(&m_pVertex[2].vTex, 0.f, 1.f);
		SetD3DXVector2(&m_pVertex[3].vTex, 0.f, 0.f);
		break;
	}
	m_pRcTex->WriteVerticies(m_pVertex);
	m_iTextureIndex = _iTextureIndex;
	m_eTextureRotation = _eTextureRotation;
}

void CTile::LoadTile(VERTEX_TEXTURE* _pTexture, int _iTextureIndex)
{
	m_pVertex = _pTexture;
	m_iTextureIndex = _iTextureIndex;
	//m_eTextureRotation = _eRotationType;

	m_pRcTex = ENGINE::CRectangleTexture::Create();
	m_pRcTex->WriteVerticies(m_pVertex);

	ENGINE::CComponent*	pComponent = NULL;
	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Tile");
	m_pTexture = dynamic_cast<ENGINE::CTexture*>(pComponent);
}
