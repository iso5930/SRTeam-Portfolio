/*!
 * \file Device.h
 * \date 2016/06/01 19:13
 *
 * \author ���ϴ�
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note 
	Ŭ���̾�Ʈ������ Renderer���� Render_Begin�� Render_End�� ������
	�������� MFC���� ���� Device�� Render_Begin�� Render_End�� ��.
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
