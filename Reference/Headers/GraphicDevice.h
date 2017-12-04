/*!
 * \file GraphicDevice.h
 * \date 2016/05/23 21:04
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 //! ��Ʈ ��ü�� ������ ��� ���� �����?
 map���� ��Ʈ�� ������ �����صΰ�, initfont �������̽��� ��������, ������ ����.
 �׷� �����Ë� getter�� �����,
 (�⺻ Ű�� �ΰ� �⺻ �Ű������� �θ� ���� �ڵ�� ȣȯ���� ���� ���̴�)
 font Ű���� �Ѱܹ޴� ������ ������.
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