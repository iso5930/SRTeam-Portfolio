#include "SmartText.h"

#include "GraphicDevice.h"

ENGINE::CSmartText::CSmartText(void)
:m_vPos(0.f, 0.f)
{
	memset(&m_szContent, 0, sizeof(m_szContent));
	memset(&m_rcBox, 0, sizeof(RECT));
}

ENGINE::CSmartText::CSmartText(TCHAR* _szText, float _fX, float _fY)
:m_vPos(_fX, _fY)
{
	lstrcpy(m_szContent, _szText);

	m_rcBox.left = (LONG)(m_vPos.x) - 10;
	m_rcBox.top = (LONG)(m_vPos.y) - 10;
	m_rcBox.right = (LONG)(m_vPos.x) + 10;
	m_rcBox.bottom = (LONG)(m_vPos.y) + 10;
}

ENGINE::CSmartText::~CSmartText(void)
{

}

void ENGINE::CSmartText::Draw(DWORD _dwColor /*= D3DCOLOR_ARGB(255, 255, 255, 255)*/)
{
	ENGINE::CGraphicDevice::GetInstance()->GetFont()->DrawText(
		NULL,
		m_szContent,
		lstrlen(m_szContent),
		&m_rcBox,
		DT_CENTER | DT_NOCLIP | DT_VCENTER,
		_dwColor);
}

void ENGINE::CSmartText::TalkboxDraw(DWORD _dwColor /*= D3DCOLOR_ARGB(255, 255, 255, 255)*/)
{
	SetPos(WINCX * 0.5f, WINCY * 0.8f);
	m_rcBox.left = (LONG)(m_vPos.x - (WINCX * 0.375f));
	m_rcBox.top = (LONG)(m_vPos.y - (WINCY * 0.09f));
	m_rcBox.right = (LONG)(m_vPos.x + (WINCX * 0.375f));
	m_rcBox.bottom = (LONG)(m_vPos.y + (WINCY * 0.09f));

	ENGINE::CGraphicDevice::GetInstance()->GetFont()->DrawText(
		NULL,
		m_szContent,
		lstrlen(m_szContent),
		&m_rcBox,
		0, //DT_CENTER | DT_NOCLIP /*| DT_VCENTER*/,
		_dwColor);
}

void ENGINE::CSmartText::SetPos(float _fX, float _fY)
{
	SetD3DXVector2(&m_vPos, _fX, _fY);

	m_rcBox.left = (LONG)(m_vPos.x) - 10;
	m_rcBox.top = (LONG)(m_vPos.y) - 10;
	m_rcBox.right = (LONG)(m_vPos.x) + 10;
	m_rcBox.bottom = (LONG)(m_vPos.y) + 10;
}
