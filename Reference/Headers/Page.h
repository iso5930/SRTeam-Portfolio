/*!
 * \file Page.h
 * \date 2016/06/04 23:05
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

#ifndef Page_h__
#define Page_h__

#include "Engine_Include.h"
#include "Component.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CPage : public CComponent
{
protected:
	LPD3DXSPRITE	m_pSprite;
	POINT			m_ptMouse;

public:
	void SetMousePos(POINT _ptMouse);
	void DrawFont(char* _pName, float _fX, float _fY, float _fIntervalX, float _fIntervalY);
	void DrawFont_Int(int _iText, float _fX, float _fY, float _fIntervalX, float _fIntervalY);
	void DrawSprite(eResourceType _eResourceType, const TCHAR* _ResourceKey, float _fX, float _fY, const int _iCnt, const RECT* _rcRect);
	void DrawText(TCHAR* _pText, D3DCOLOR _Color, float _fX, float _fY);
	void BarTextDraw(int _iPoint, int _iMaxPoint, float _fX, float _fY, float _fIntervalX, float _fIntervalY);
	
public:
	virtual int		Update(void);
	virtual void	Render(void);

protected:
	explicit CPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CPage(void);
};

END_NAMESPACE

#endif // Page_h__