// MyToolView.cpp : ���� �����Դϴ�.
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


// CMyToolView �׸����Դϴ�.

void CMyToolView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CMyToolView �����Դϴ�.

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


// CMyToolView �޽��� ó�����Դϴ�.

void CMyToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pMyToolSheet = new CMyToolSheet;
	m_pMyToolSheet->Create(this, WS_CHILD | WS_VISIBLE);
	m_pMyToolSheet->MoveWindow(0, 0, 500, 600);
}
