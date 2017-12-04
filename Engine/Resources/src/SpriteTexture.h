/*!
 * \file SpriteTexture.h
 * \date 2016/06/04 22:04
 *
 * \author ������
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
//! ����� �ּ�ȭ�ϸ鼭, �ؽ��Ķ� ���� ���.. ������, ������?
// �ƴϸ� �̴�� ���δ°� �´°�.

#ifndef SpriteTexture_h__
#define SpriteTexture_h__

#include "Engine_Include.h"
#include "GraphicResource.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CSpriteTexture : public CGraphicResource
{
private:
	vector<TEXINFO*>	m_vecSprite;
	DWORD				m_dwCount;

public:
	static	CSpriteTexture* Create(const wstring& _strFilePath, const DWORD& _dwCount, D3DCOLOR _Color = NULL);
	virtual void Render(int _iIndex = -1);
	virtual CGraphicResource* CloneResource(ENGINE::CGameObject* _pOwner);

private:
	HRESULT LoadSpriteTexture(const wstring& _strFilePath, const DWORD& _dwCount, D3DCOLOR _Color = NULL);
	void Release(void);

public:
	TEXINFO* GetTexInfo(const DWORD& _dwCount);

private:
	explicit CSpriteTexture(void);

public:
	virtual ~CSpriteTexture(void);
};

END_NAMESPACE

#endif // SpriteTexture_h__