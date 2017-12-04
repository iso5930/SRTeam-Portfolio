/*!
 * \file Tile.h
 * \date 2016/06/09 22:33
 *
 * \author ¼­ÇÏ´Ã
 * Contact: user@company.com
 *
 * \brief TileTerrainÀÌ °ü¸®ÇÏ´Â Tile°´Ã¼.
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Tile_h__
#define Tile_h__

#include "GameObject.h"

namespace ENGINE
{
	class CRectangleTexture;
	class CTexture;
}

class CTile : public ENGINE::CGameObject
{
public:
	ENGINE::CRectangleTexture*		m_pRcTex;
	ENGINE::CTexture*				m_pTexture;
	VERTEX_TEXTURE*					m_pVertex;

	int								m_iTextureIndex;
	eTextureRotation				m_eTextureRotation;

public:
	static CTile*	Create(eObjectType _eObjectType, VERTEX_TEXTURE*	_pVertexTexture);

public:
	HRESULT			Initialize(VERTEX_TEXTURE*	_pVertexTexture);
	virtual	HRESULT	Initialize(void);

	virtual int	Update(void);
	virtual	void	Render(void);
	void	Release(void);
	void	SetTileTexture(int _iTextureIndex, eTextureRotation _eTextureRotation);

public:
	void	LoadTile(VERTEX_TEXTURE*	_pTexture, int	_iTextureIndex);

public:
	explicit	CTile(eObjectType _eObjectType);
	virtual		~CTile(void);
};


#endif // Tile_h__
