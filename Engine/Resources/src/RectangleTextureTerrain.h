/*!
 * \file RectangleTextureTerrain.h
 * \date 2016/06/05 17:22
 *
 * \author 서하늘
 * Contact: user@company.com
 *
 * \brief Rectangle Texture를 내부에서 생성시켜 터레인으로 만듬.
 *
 * TODO: long description
 *
 * \note
*/

#ifndef RectangleTextureTerrain_h__
#define RectangleTextureTerrain_h__

#include "Engine_Include.h"
#include "VIBuffer.h"
#include "RectangleTexture.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CRectangleTextureTerrain : public CVIBuffer
{
	// member variable
private:
	vector<CRectangleTexture*>	m_vecTile;

	// member function
public:
	static CRectangleTextureTerrain* Create(DWORD _dwCountX, DWORD _dwCountZ, DWORD _dwInterval);
private:
	HRESULT Initialize(DWORD _dwCountX, DWORD _dwCountZ, DWORD _dwInterval);
	// getter & setter
public:
	// -
	virtual void Render(int _iIndex = -1);

	// constructor & destructor
private:
	explicit CRectangleTextureTerrain(void);
public:
	virtual ~CRectangleTextureTerrain(void);
	virtual CGraphicResource* CloneResource(void);

	//MAKE_UNCOPYABLE(CTextureTerrain)
};
END_NAMESPACE

#endif // RectangleTextureTerrain_h__