// MyToolView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "../home/Tool.h"
#include "MyToolView.h"
#include "MyToolSheet.h"


// CMyToolView

IMPLEMENT_DYNCREATE(CMyToolView, CView)

CMyToolView::CMyToolView()
: m_pMyToolSheet(NULL)
{

}

CMyToolView::~CMyToolView()
{
	if(m_pMyToolSheet != NULL)
		SAFE_DELETE(m_pMyToolSheet);
}

BEGIN_MESSAGE_MAP(CMyToolView, CView)
END_MESSAGE_MAP()


// CMyToolView 그리기입니다.

void CMyToolView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CMyToolView 진단입니다.

#ifdef _DEBUG
void CMyToolView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyToolView 메시지 처리기입니다.

void CMyToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pMyToolSheet = new CMyToolSheet;
	m_pMyToolSheet->Create(this, WS_CHILD | WS_VISIBLE);
	m_pMyToolSheet->MoveWindow(0, 0, 500, 600);
}
