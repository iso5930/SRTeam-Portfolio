// C:\Users\Administrator\Desktop\srproject1\trunk\SRTeam1\Tools\Tool_Object\src\LeftSheet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "../home/Tool_Object.h"
#include "LeftSheet.h"


// CLeftSheet

IMPLEMENT_DYNAMIC(CLeftSheet, CPropertySheet)

CLeftSheet::CLeftSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CLeftSheet::CLeftSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CLeftSheet::CLeftSheet(void)
{
	AddPage(&m_ObjectPage);
}

CLeftSheet::~CLeftSheet()
{
}


BEGIN_MESSAGE_MAP(CLeftSheet, CPropertySheet)
END_MESSAGE_MAP()


// CLeftSheet 메시지 처리기입니다.

BOOL CLeftSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  여기에 특수화된 코드를 추가합니다.
	SetActivePage(&m_ObjectPage);

	return bResult;
}
