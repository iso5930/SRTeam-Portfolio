// C:\Users\Administrator\Desktop\srproject1\trunk\SRTeam1\Tools\Tool_Object\src\LeftSheet.cpp : ���� �����Դϴ�.
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


// CLeftSheet �޽��� ó�����Դϴ�.

BOOL CLeftSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  ���⿡ Ư��ȭ�� �ڵ带 �߰��մϴ�.
	SetActivePage(&m_ObjectPage);

	return bResult;
}
