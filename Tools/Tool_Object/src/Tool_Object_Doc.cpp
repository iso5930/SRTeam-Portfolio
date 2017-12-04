
// Tool_Object_Doc.cpp : CTool_Object_Doc 클래스의 구현
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


// CTool_Object_Doc 생성/소멸

CTool_Object_Doc::CTool_Object_Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CTool_Object_Doc::~CTool_Object_Doc()
{
}

BOOL CTool_Object_Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CTool_Object_Doc serialization

void CTool_Object_Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CTool_Object_Doc 진단

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


// CTool_Object_Doc 명령
