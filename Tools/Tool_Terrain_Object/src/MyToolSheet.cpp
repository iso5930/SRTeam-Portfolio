// MyToolSheet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "../home/Tool.h"
#include "MyToolSheet.h"


// CMyToolSheet

IMPLEMENT_DYNAMIC(CMyToolSheet, CPropertySheet)

CMyToolSheet::CMyToolSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CMyToolSheet::CMyToolSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CMyToolSheet::CMyToolSheet(void)
{
	AddPage(&m_TerrainPage);
	AddPage(&m_ObjectPage);
}

CMyToolSheet::~CMyToolSheet()
{
}


BEGIN_MESSAGE_MAP(CMyToolSheet, CPropertySheet)
END_MESSAGE_MAP()


// CMyToolSheet 메시지 처리기입니다.

BOOL CMyToolSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  여기에 특수화된 코드를 추가합니다.

	SetActivePage(&m_TerrainPage);
	SetActivePage(&m_ObjectPage);
	SetActivePage(&m_TerrainPage);

	return bResult;
}
