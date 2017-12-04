/*!
 * \file Device.h
 * \date 2016/06/01 19:13
 *
 * \author 서하늘
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note 
	클라이언트에서는 Renderer에서 Render_Begin과 Render_End를 하지만
	툴에서는 MFC때와 같이 Device가 Render_Begin과 Render_End를 함.
*/

#pragma once

class CDevice
{
	DECLARE_SINGLETON(CDevice)

private:
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pDevice;

public:
	HRESULT				InitDevice(void);
	void				SetParameters(D3DPRESENT_PARAMETERS& d3dpp);
	LPDIRECT3DDEVICE9	GetDevice(void);
	void				Render_Begin(void);
	void				Render_End(void);
	void				Release(void);

public:
	CDevice(void);
	~CDevice(void);
};
