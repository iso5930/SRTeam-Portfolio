/*!
 * \file GraphicDevice.h
 * \date 2016/05/23 21:04
 *
 * \author 박정민
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 //! 폰트 객체를 여러개 띄울 일이 생긴다?
 map으로 폰트를 여러개 저장해두고, initfont 인터페이스는 빼뒀으니, 생성은 쉽다.
 그럼 가져올떄 getter를 만들고,
 (기본 키를 두고 기본 매개변수를 두면 기존 코드랑 호환성도 생길 것이다)
 font 키값을 넘겨받는 식으로 만들자.
*/

#ifndef GraphicDevice_h__
#define GraphicDevice_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CGraphicDevice
{
	DECLARE_SINGLETON(CGraphicDevice)

public:
	enum eWindowed
	{
		WINDOWED_FALSE,
		WINDOWED_TRUE
	};

	// member variable
private:
	LPDIRECT3D9			m_pD3D9;
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXSPRITE		m_pSprite;
	LPD3DXFONT			m_pFont;

	// member function
public:
	HRESULT InitDevice(
		eWindowed _eWindowed,
		HWND _hWnd,
		unsigned int _uWinCX,
		unsigned int _uWinCY);

	HRESULT InitFont(
		TCHAR* _szFontName,
		DWORD _dwHeight,
		DWORD _dwWidth,
		DWORD _dwWeight);
private:
	void SetParameters(
		D3DPRESENT_PARAMETERS& _tD3DPP,
		eWindowed _eWindowed,
		HWND _hWnd,
		unsigned int _uWinCX,
		unsigned int _uWinCY);
	void Release(void);

	// getter & setter
public:
	const LPDIRECT3DDEVICE9 GetDevice(void) const;
	const LPD3DXSPRITE		GetSprite(void);
	const LPD3DXFONT		GetFont(void);

	// constructor & destructor
private:
	explicit CGraphicDevice(void);
	~CGraphicDevice(void);
};
END_NAMESPACE

#endif // GraphicDevice_h__