/*!
 * \file Texture.h
 * \date 2016/05/27 8:32
 *
 * \author 박정민
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
//! 텍스쳐의 관리는 어떻게 할 것인가?
// 싱글 - 멀티 텍스쳐의 구분?
// 디렉터리 및 키 관리 구조는 어떻게 할 것인가..

#ifndef Texture_h__
#define Texture_h__

#include "Engine_Include.h"
#include "GraphicResource.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CTexture : public CGraphicResource
{
private:
	typedef vector<LPDIRECT3DBASETEXTURE9> TEXTURE_VECTOR;

	// member variable
private:
	TEXTURE_VECTOR m_TextureVec;
	int m_iContainerSize;

	// member function
public:
	static CTexture* Create(eTextureType _eTextureType, const wstring& _strFilePath, DWORD _dwCnt);
	virtual void Render(int _iIndex = -1);
	virtual CGraphicResource* CloneResource(ENGINE::CGameObject* _pOwner);
private:
	HRESULT LoadTexture(eTextureType _eTextureType, const wstring& _strFilePath, DWORD _dwCnt);
	void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CTexture(void);
public:
	virtual ~CTexture(void);
};
END_NAMESPACE

#endif // Texture_h__