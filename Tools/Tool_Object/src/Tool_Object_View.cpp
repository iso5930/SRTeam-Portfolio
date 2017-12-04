
// Tool_Object_View.cpp : CTool_Object_View 클래스의 구현
//

#include "stdafx.h"
#include "../home/Tool_Object.h"

#include "Tool_Object_Doc.h"
#include "Tool_Object_View.h"

#include "Export_Function.h"
#include "MainFrm.h"
#include "AnyObject.h"
#include "StaticCamera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
	//! 할 일들..

	1. 카메라 조작, 실제 게임의 시점을 그대로 받아올 것. (확대, 축소는?)

	2. 새 컴포넌트 삽입, 피킹으로 인한 이동, 회전, 확대, 축소

	3. 해당 버퍼에 텍스쳐 종류별로 입히게 수정

	3. 컴포넌트 덩어리를 저장 / 로드

	4. 충돌 박스 여기서 만들어줌?
*/

HWND g_hWnd = NULL;

// CTool_Object_View

IMPLEMENT_DYNCREATE(CTool_Object_View, CView)

BEGIN_MESSAGE_MAP(CTool_Object_View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTool_Object_View::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CTool_Object_View 생성/소멸


CTool_Object_View::CTool_Object_View()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTool_Object_View::~CTool_Object_View()
{
}

BOOL CTool_Object_View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTool_Object_View 그리기

void CTool_Object_View::OnDraw(CDC* /*pDC*/)
{
	CTool_Object_Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	ENGINE::GetDevice()->Clear(
		0,
		NULL,
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		1.f,
		0);

	ENGINE::GetDevice()->BeginScene();

	// draw
	if (g_pObject)
		g_pObject->Render();

	ENGINE::GetDevice()->EndScene();

	ENGINE::GetDevice()->Present(NULL, NULL, NULL, NULL);
}


// CTool_Object_View 인쇄


void CTool_Object_View::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CTool_Object_View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTool_Object_View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTool_Object_View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CTool_Object_View::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTool_Object_View::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CTool_Object_View 진단

#ifdef _DEBUG
void CTool_Object_View::AssertValid() const
{
	CView::AssertValid();
}

void CTool_Object_View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool_Object_Doc* CTool_Object_View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool_Object_Doc)));
	return (CTool_Object_Doc*)m_pDocument;
}
#endif //_DEBUG


void CTool_Object_View::SetWindowSize(void)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	RECT rcWindow;
	pMainFrame->GetWindowRect(&rcWindow);
	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);

	RECT rcMainView;
	GetClientRect(&rcMainView);

	int iRowFrm = rcWindow.right - rcMainView.right;
	int iColFrm = rcWindow.bottom - rcMainView.bottom;

	pMainFrame->SetWindowPos(NULL,
		0,
		0,
		WINCX + iRowFrm,
		WINCY + iColFrm,
		SWP_NOZORDER);
}

// CTool_Object_View 메시지 처리기

void CTool_Object_View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SetWindowSize();

	g_hWnd = m_hWnd;

	HRESULT hr = ENGINE::GetDeviceManager()->InitDevice(ENGINE::CGraphicDevice::WINDOWED_TRUE, g_hWnd, WINCX, WINCY);
	if FAILED(hr)
		return;

	ENGINE::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	ENGINE::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//! 굳이 여기에 둬야 하나..
	// MFC 오브젝트들 초기화 순서는 어찌 돼먹은 건지..
	ENGINE::GetResourceManager()->AddBuffer(RESOURCE_TYPE_STATIC,
		ENGINE::CVIBuffer::BUFFER_TYPE_RECTANGLE_TEXTURE,
		L"Buffer_Rectangle_Texture");

	ENGINE::GetResourceManager()->AddBuffer(RESOURCE_TYPE_STATIC,
		ENGINE::CVIBuffer::BUFFER_TYPE_CUBE_TEXTURE,
		L"Buffer_Cube_Texture");

	ENGINE::GetResourceManager()->AddTexture(RESOURCE_TYPE_DYNAMIC,
		TEXTURE_TYPE_NORMAL,
		L"Texture_Rectangle_Example",
		L"../../../Client/bin/Resources/Texture/Player0.png",
		1);

	ENGINE::GetResourceManager()->AddTexture(RESOURCE_TYPE_DYNAMIC,
		TEXTURE_TYPE_CUBE,
		L"Texture_Cube_Example",
		L"../../../Client/bin/Resources/Texture/Monster0.dds",
		1);

	//! 이걸로 타이머를..
	SetTimer(1, 30, NULL);
}

void CTool_Object_View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ENGINE::CGraphicDevice::DestroyInstance();
	ENGINE::CResourceManager::DestroyInstance();
	ENGINE::CInputManager::DestroyInstance();
	ENGINE::CTimeManager::DestroyInstance();
}

void CTool_Object_View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ENGINE::GetInputManager()->SetKeyState(g_hWnd, false);

	ENGINE::GetTimeManager()->SetTime();

	if (g_pObject)
		g_pObject->Update();

	if (g_pCamera)
		g_pCamera->Update();

	Invalidate(false);

	CView::OnTimer(nIDEvent);
}
