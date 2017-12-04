/*!
 * \file TerrainCollision.h
 * \date 2016/06/07 18:44
 *
 * \author ¼­ÇÏ´Ã
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#pragma once

#include "Collision.h"

class CTerrainCollision : public ENGINE::CCollision
{
private:
	D3DXVECTOR3*	m_pvPos;
	const	VERTEX_TEXTURE*	m_pTerrainVertex;

public:
	static CTerrainCollision*	Create(const void* _pOwner);
	virtual int	Update(void);

private:
	void Release(void);

public:
	void SetCollisionInfo(D3DXVECTOR3* _pPos, const VERTEX_TEXTURE* _pTerrainVertex);
public:
	CTerrainCollision(const void* _pOwner);
	virtual ~CTerrainCollision(void);
};
