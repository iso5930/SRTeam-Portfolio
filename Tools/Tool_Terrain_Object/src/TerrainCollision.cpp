#include "StdAfx.h"
#include "TerrainCollision.h"

CTerrainCollision::CTerrainCollision(const void* _pOwner)
:CCollision(_pOwner)
{
}

CTerrainCollision::~CTerrainCollision(void)
{
}

CTerrainCollision*	CTerrainCollision::Create(const void* _pOwner)
{
	return new CTerrainCollision(_pOwner);
}

int CTerrainCollision::Update(void)
{
	return 0;
}

void CTerrainCollision::Release(void)
{

}

void CTerrainCollision::SetCollisionInfo(D3DXVECTOR3* _pPos, const VERTEX_TEXTURE* _pTerrainVertex)
{
	m_pvPos = _pPos;
	m_pTerrainVertex = _pTerrainVertex;
}