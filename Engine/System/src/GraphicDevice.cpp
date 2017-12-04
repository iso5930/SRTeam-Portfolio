#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(ENGINE::CGraphicDevice)

ENGINE::CGraphicDevice::CGraphicDevice(void)
:m_pD3D9(NULL)
,m_pDevice(NULL)
,m_pFont(NULL)
,m_pSprite(NULL)
{

}

ENGINE::CGraphicDevice::~CGraphicDevice(void)
{
	Release();
}

HRESULT ENGINE::CGraphicDevice::InitDevice(
	eWindowed _eWindowed,
	HWND _hWnd,
	unsigned int _uWinCX,
	unsigned int _uWinCY)
{
	HRESULT hr = NULL;

	// 1. get IDirect3D9 interface
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	// 2. check hardware vertex processing
	D3DCAPS9 tCaps;
	ZeroMemory(&tCaps, sizeof(D3DCAPS9));
	hr = m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &tCaps);
	if FAILED(hr)
	{
		UTIL::SHOW_ERROR(hr, L"GetDeviceCaps() Failed!");
		return hr;
	}

	int iVP = 0;
	if (tCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		iVP = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		iVP = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	iVP |= D3DCREATE_MULTITHREADED;

	// 3. fill d3dpp
	D3DPRESENT_PARAMETERS tD3DPP;
	ZeroMemory(&tD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	SetParameters(tD3DPP, _eWindowed, _hWnd, _uWinCX, _uWinCY);

	// 4. create IDirect3DDevice9
	hr = m_pD3D9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		iVP,
		&tD3DPP,
		&m_pDevice);
	if FAILED(hr)
	{
		UTIL::SHOW_ERROR(hr, L"CreateDevice() Failed!");
		return hr;
	}

	// 5. create ID3DXSprite
	hr = D3DXCreateSprite(m_pDevice, &m_pSprite);
	if FAILED(hr)
	{
		UTIL::SHOW_ERROR(hr, L"D3DXCreateSprite() Failed!");
		return hr;
	}

	return S_OK;
}

HRESULT ENGINE::CGraphicDevice::InitFont(TCHAR* _szFontName,
										 DWORD _dwHeight,
										 DWORD _dwWidth,
										 DWORD _dwWeight)
{
	D3DXFONT_DESCW	FontInfo;
	ZeroMemory(&FontInfo, sizeof(D3DXFONT_DESCW));

	FontInfo.Height = _dwHeight;
	FontInfo.Width = _dwWidth;
	FontInfo.Weight = _dwWeight;
	lstrcpy(FontInfo.FaceName, _szFontName);

	HRESULT hr = D3DXCreateFontIndirect(m_pDevice, &FontInfo, &m_pFont);
	if FAILED(hr)
		return E_FAIL;

	return S_OK;
}

void ENGINE::CGraphicDevice::SetParameters(
	D3DPRESENT_PARAMETERS& _tD3DPP,
	eWindowed _eWindowed,
	HWND _hWnd,
	unsigned int _uWinCX,
	unsigned int _uWinCY)
{
	_tD3DPP.BackBufferWidth = _uWinCX;
	_tD3DPP.BackBufferHeight = _uWinCY;
	_tD3DPP.BackBufferFormat = D3DFMT_A8R8G8B8;
	_tD3DPP.BackBufferCount = 1;

	_tD3DPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	_tD3DPP.MultiSampleQuality = 0;

	_tD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;

	_tD3DPP.hDeviceWindow = _hWnd;
	_tD3DPP.Windowed = _eWindowed;

	_tD3DPP.EnableAutoDepthStencil = TRUE;
	_tD3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;

	_tD3DPP.Flags = NULL;

	_tD3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	_tD3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

void ENGINE::CGraphicDevice::Release(void)
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3D9);
}

const LPDIRECT3DDEVICE9 ENGINE::CGraphicDevice::GetDevice(void) const
{
	return m_pDevice;
}

const LPD3DXSPRITE ENGINE::CGraphicDevice::GetSprite(void)
{	
	return m_pSprite;
}

const LPD3DXFONT ENGINE::CGraphicDevice::GetFont(void)
{
	return m_pFont;
}