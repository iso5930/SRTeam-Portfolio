// ObjectPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "../home/Tool.h"
#include "ObjectPage.h"


// CObjectPage 대화 상자입니다.

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


// CObjectPage 메시지 처리기입니다.
