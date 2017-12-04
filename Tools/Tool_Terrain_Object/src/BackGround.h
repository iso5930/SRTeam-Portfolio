/*!
 * \file BackGround.h
 * \date 2016/06/01 23:04
 *
 * \author 서하늘
 * Contact: user@company.com
 *
 * \brief 터레인과 오브젝트를 띄운다.
 *
 * TODO: long description
 *
 * \note
*/

#pragma once

namespace ENGINE
{
	class CTransform;
	class CGameObject;
}

class CStaticCamera;
class CToolView;
class CMouseCollision;
class CBackGround
{
public:	
	ENGINE::CTransform*		m_pInfo;
	CMouseCollision*		m_pMouseCollision;
	ENGINE::CGameObject*	m_pGameObject;

public:
	CStaticCamera*		m_pStaticCamera;
	VERTEX_COLOR*		m_pVertexColor;
	VERTEX_TEXTURE*		m_pVertexTexture;

public:
	bool			m_bTerrainFix;
	bool			m_bTextureFix;
	bool			m_bCreateTerrain;
	int				m_iTextureIndex;
	float			m_fHeightValue;
	eVertexDirect		m_eVertexDirect;
	eTextureRotation	m_eTextureRotation;

public:
	CToolView*		m_pMainView;

public:
	void	SetMainView(CToolView*	_pView);
	void	KeyCheck(void);
	void	SetCollsionMouse(int _iVertexCountX, int _iVertexCountZ);
	void	SetDirection(void);
	void	SetReadVertexColor(int	_iCountX, int	_iCountZ,  wstring _wstrKey);
	void	SetVertexColorHeight(int iVertexIndex);
	void	SetTextureHeight(void);
	void	SetTextureHeight(int	_iCountX, int	_iCountZ);

public:
	void	Initialize(void);
	void	Update(void);
	void	Render(void);
	void	Release(void);

public:
	CBackGround(void);
	~CBackGround(void);
};
