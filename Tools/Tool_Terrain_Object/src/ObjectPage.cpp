// ObjectPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "../home/Tool.h"
#include "ObjectPage.h"


// CObjectPage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CObjectPage, CPropertyPage)

CObjectPage::CObjectPage()
	: CPropertyPage(CObjectPage::IDD)
{

}

CObjectPage::~CObjectPage()
{
}

void CObjectPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CObjectPage, CPropertyPage)
END_MESSAGE_MAP()


// CObjectPage �޽��� ó�����Դϴ�.
