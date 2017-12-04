/*!
 * \file Texture.h
 * \date 2016/05/27 8:32
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
//! �ؽ����� ������ ��� �� ���ΰ�?
// �̱� - ��Ƽ �ؽ����� ����?
// ���͸� �� Ű ���� ������ ��� �� ���ΰ�..

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