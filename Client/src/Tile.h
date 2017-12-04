/*!
 * \file Tile.h
 * \date 2016/06/14 21:56
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief ¼­ÇÏ´Ã
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
private:
	ENGINE::CRectangleTexture*	m_pRcTex;
	ENGINE::CTexture*			m_pTexture;
	VERTEX_TEXTURE*				m_pVertex;

	int							m_iTextureIndex;

public:
	static CTile*	Create(eObjectType _eObjectType, VERTEX_TEXTURE*		_pVertexTexture, int _iTextureIndex);

private:
	HRESULT			Initialize(VERTEX_TEXTURE*		_pVertexTexture, int _iTextureIndex);
	virtual	HRESULT	Initialize(void);
	virtual void	Release(void);

public:
	virtual int		Update(void);
	virtual	void	Render(void);

private:
	explicit	CTile(eObjectType _eObjectType);

public:
	virtual ~CTile(void);

};

#endif // Tile_h__