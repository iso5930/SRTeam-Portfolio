/*!
 * \file MouseCollision.h
 * \date 2016/06/07 20:14
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

class CMouseCollision : public ENGINE::CCollision
{
public:
	D3DXVECTOR3	m_vPivotPos;
	D3DXVECTOR3	m_vRayDir;
	int			m_iVertexCountX;
	int			m_iVertexCountZ;

public:
	static CMouseCollision*	Create(ENGINE::CGameObject* _pOwner, int _iVertexCountX, int _iVertexCountZ);
	int PickTerrainTexture(const VERTEX_TEXTURE*	_pTerrainVertex);
	int	PickTerrainHeight(const VERTEX_COLOR*		_pTerrainVertex, eVertexDirect _eVertexDirect);

public:
	HRESULT	Initialize(int _iVertexCountX, int _iVertexCountZ);
	void	TranslationViewspace(void);
	void	TranslationLocal(const D3DXMATRIX*	_pWorld);
	void	Release(void);

public:
	CMouseCollision(ENGINE::CGameObject* _pOwner);
	virtual ~CMouseCollision(void);
};
