// C:\Users\Administrator\Desktop\srproject1\trunk\SRTeam1\Tools\Tool_Object\src\LeftForm.cpp : ���� �����Դϴ�.
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


// CLeftForm �����Դϴ�.

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


// CLeftForm �޽��� ó�����Դϴ�.

void CLeftForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_LeftSheet = new CLeftSheet;
	m_LeftSheet->Create(this, WS_CHILD | WS_VISIBLE);
	m_LeftSheet->MoveWindow(0, 0, WINCX, WINCY);
	//! �ƴ� �״ϱ�, �䳪 ��Ʈ, ������ ���� �͵� ũ��� ��� �����ؾ� �ϴ� �ǰ�?
}
