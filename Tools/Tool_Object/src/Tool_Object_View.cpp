
// Tool_Object_View.cpp : CTool_Object_View Ŭ������ ����
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
	//! �� �ϵ�..

	1. ī�޶� ����, ���� ������ ������ �״�� �޾ƿ� ��. (Ȯ��, ��Ҵ�?)

	2. �� ������Ʈ ����, ��ŷ���� ���� �̵�, ȸ��, Ȯ��, ���

	3. �ش� ���ۿ� �ؽ��� �������� ������ ����

	3. ������Ʈ ����� ���� / �ε�

	4. �浹 �ڽ� ���⼭ �������?
*/

HWND g_hWnd = NULL;

// CTool_Object_View

IMPLEMENT_DYNCREATE(CTool_Object_View, CView)

BEGIN_MESSAGE_MAP(CTool_Object_View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTool_Object_View::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CTool_Object_View ����/�Ҹ�


CTool_Object_View::CTool_Object_View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CTool_Object_View::~CTool_Object_View()
{
}

BOOL CTool_Object_View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTool_Object_View �׸���

void CTool_Object_View::OnDraw(CDC* /*pDC*/)
{
	CTool_Object_Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
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


// CTool_Object_View �μ�


void CTool_Object_View::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CTool_Object_View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTool_Object_View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTool_Object_View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CTool_Object_View ����

#ifdef _DEBUG
void CTool_Object_View::AssertValid() const
{
	CView::AssertValid();
}

void CTool_Object_View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool_Object_Doc* CTool_Object_View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
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

// CTool_Object_View �޽��� ó����

void CTool_Object_View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	SetWindowSize();

	g_hWnd = m_hWnd;

	HRESULT hr = ENGINE::GetDeviceManager()->InitDevice(ENGINE::CGraphicDevice::WINDOWED_TRUE, g_hWnd, WINCX, WINCY);
	if FAILED(hr)
		return;

	ENGINE::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	ENGINE::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//! ���� ���⿡ �־� �ϳ�..
	// MFC ������Ʈ�� �ʱ�ȭ ������ ���� �Ÿ��� ����..
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

	//! �̰ɷ� Ÿ�̸Ӹ�..
	SetTimer(1, 30, NULL);
}

void CTool_Object_View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	ENGINE::CGraphicDevice::DestroyInstance();
	ENGINE::CResourceManager::DestroyInstance();
	ENGINE::CInputManager::DestroyInstance();
	ENGINE::CTimeManager::DestroyInstance();
}

void CTool_Object_View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	ENGINE::GetInputManager()->SetKeyState(g_hWnd, false);

	ENGINE::GetTimeManager()->SetTime();

	if (g_pObject)
		g_pObject->Update();

	if (g_pCamera)
		g_pCamera->Update();

	Invalidate(false);

	CView::OnTimer(nIDEvent);
}
