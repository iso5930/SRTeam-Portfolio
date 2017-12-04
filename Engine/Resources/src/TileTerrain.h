/*!
 * \file TileTerrain.h
 * \date 2016/06/06 15:01
 *
 * \author 서하늘
 * Contact: user@company.com
 *
 * \brief 지형을 만들기 위한 타일 터레인
 *
 * TODO: long description
 *
 * \note
*/

#ifndef TileTerrain_h__
#define TileTerrain_h__

#include "GameObject.h"
#include "Tile.h"

namespace ENGINE
{
	class CRectangleTexture;
	class CTexture;
}

class CTileTerrain : public ENGINE::CGameObject
{
public:
	vector<CTile*>			m_vecTile;
	VERTEX_TEXTURE*			m_pVertexTexture;
	VERTEX_TEXTURE*			m_pTileVertex;

public:
	int						m_iCountX;
	int						m_iCountZ;

public:
	void	SetTileTexture(int _iTileIndex, int _iTextureIndex, eTextureRotation _eTextureRotation);

public:
	static CTileTerrain* Create(eObjectType _eObjectType, const DWORD& _dwCountX, const DWORD& _dwCountZ, const DWORD& _dwInterval, const wstring& _wstrKey);
	
private:
	HRESULT	Initialize(const DWORD& _dwCountX, const DWORD& _dwCountZ, const DWORD& _dwInterval, const wstring& _wstrKey);

	virtual HRESULT Initialize(void);

public:
	virtual int Update(void);
	virtual void Render(void);
	void	Release(void);


private:
	explicit CTileTerrain(eObjectType _eObjectType);

public:
	virtual ~CTileTerrain(void);

};


#endif // TileTerrain_h__