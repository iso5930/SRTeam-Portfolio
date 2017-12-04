// C:\Users\Administrator\Desktop\srproject1\trunk\SRTeam1\Tools\Tool_Object\src\LeftForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "../home/Tool_Object.h"
#include "LeftForm.h"

#include "LeftSheet.h"


// CLeftForm

IMPLEMENT_DYNCREATE(CLeftForm, CFormView)

CLeftForm::CLeftForm()
	: CFormView(CLeftForm::IDD)
	, m_LeftSheet(NULL)
{

}

CLeftForm::~CLeftForm()
{
	SAFE_DELETE(m_LeftSheet);
}

void CLeftForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLeftForm, CFormView)
END_MESSAGE_MAP()


// CLeftForm 진단입니다.

#ifdef _DEBUG
void CLeftForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftForm 메시지 처리기입니다.

void CLeftForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_LeftSheet = new CLeftSheet;
	m_LeftSheet->Create(this, WS_CHILD | WS_VISIBLE);
	m_LeftSheet->MoveWindow(0, 0, WINCX, WINCY);
	//! 아니 그니까, 뷰나 시트, 페이지 같은 것들 크기는 어떻게 조정해야 하는 건가?
}
