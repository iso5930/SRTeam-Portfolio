#include "StdAfx.h"
#include "Tile.h"
#include "Terrain.h"
#include "Pipeline.h"
#include "Texture.h"

CTile::CTile(void)
{
}

CTile::~CTile(void)
{
	Release();
}

int CTile::Update(void)
{
	return 0;
}

void CTile::Render(void)
{
}

HRESULT CTile::Initialize(void)
{
	return S_OK;
}

void CTile::Release(void)
{
}
