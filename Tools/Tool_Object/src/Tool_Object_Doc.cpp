
// Tool_Object_Doc.cpp : CTool_Object_Doc Ŭ������ ����
//

#include "stdafx.h"
#include "../home/Tool_Object.h"

#include "Tool_Object_Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTool_Object_Doc

IMPLEMENT_DYNCREATE(CTool_Object_Doc, CDocument)

BEGIN_MESSAGE_MAP(CTool_Object_Doc, CDocument)
END_MESSAGE_MAP()


// CTool_Object_Doc ����/�Ҹ�

CTool_Object_Doc::CTool_Object_Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CTool_Object_Doc::~CTool_Object_Doc()
{
}

BOOL CTool_Object_Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CTool_Object_Doc serialization

void CTool_Object_Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CTool_Object_Doc ����

#ifdef _DEBUG
void CTool_Object_Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTool_Object_Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTool_Object_Doc ���
