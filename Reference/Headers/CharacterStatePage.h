/*!
 * \file CharacterStatePage.h
 * \date 2016/06/04 23:16
 *
 * \author ÀÌÁøÇü
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef CharacterStatePage_h__
#define CharacterStatePage_h__

#include "CharacterPage.h"

BEGIN_NAMESPACE(ENGINE)

class CGroupObserver;

class ENGINE_DLL_SPECIFIER CCharacterStatePage : public CCharacterPage
{
private:
	CGroupObserver* m_pGroupObserver;

//test
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DVERTEXBUFFER9 m_pVB2;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	DWORD					m_dwVtxSize;
	DWORD					m_dwVtxCnt;
	DWORD					m_dwVtxFVF;
	DWORD					m_dwTriCnt;
	DWORD					m_dwIdxSize;
	D3DFORMAT				m_IdxFmt;

	VERTEX_COLOR_RHW*		m_pVtxRHW;
	VERTEX_COLOR_RHW*		m_pVtxRHW2;
	VERTEX_COLOR_RHW*		m_pOriginVtxRHW;

public:
	static CCharacterStatePage* Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

private:
	HRESULT Init(void);
	void	Release(void);

public:
	virtual int Update(void);
	virtual void Render(void);

private:
	explicit CCharacterStatePage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CCharacterStatePage(void);

};

END_NAMESPACE

#endif // CharacterStatePage_h__