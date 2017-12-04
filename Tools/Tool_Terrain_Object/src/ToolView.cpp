
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
#include "../home/Tool.h"

#include "ToolDoc.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "../Engine/System/src/GraphicDevice.h"
#include "ResourceManager.h"
#include "BackGround.h"
#include "MyToolView.h"
#include "MyToolSheet.h"
#include "TerrainPage.h"
#include "TimeManager.h"
#include "Export_Function.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CView)

BEGIN_MESSAGE_MAP(CToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CToolView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_pBack = NULL;
	m_pGameObject = NULL;
	m_pStaticCamera = NULL;

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	//ENGINE::GetDeviceManager()->Render_Begin();

	//ENGINE::GetDeviceManager()->Render_End();

	//Render_Begin

	ENGINE::GetDevice()->Clear(
		0,
		NULL,
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		1.f,
		0);
	ENGINE::GetDevice()->BeginScene();

	//m_wstrTerrainKey = ((CMainFrame*)AfxGetMainWnd())->m_pMyToolView->m_pMyToolSheet->m_TerrainPage.m_strTerrainKey;
	m_pGameObject = ((CMainFrame*)AfxGetMainWnd())->m_pMyToolView->m_pMyToolSheet->m_TerrainPage.m_pGameObject;

	m_pBack->Render();


	//Render_End
	ENGINE::GetDevice()->EndScene();
	ENGINE::GetDevice()->Present(NULL, NULL, NULL, NULL);
}


// CToolView �μ�


void CToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CToolView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CToolView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����

void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	//�� â�� ũ�⸦ �����ش�.
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWindow;
	pFrame->GetWindowRect(&rcWindow);

	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);

	RECT	rcMainView;
	GetClientRect(&rcMainView);

	float fRowFrm = float(rcWindow.right - rcMainView.right);
	float fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	pFrame->SetWindowPos(NULL, 0, 0, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);

	//�ڵ��� ���´�.
	g_hWnd = m_hWnd;

	//��׶��� �ʱ�ȭ
	m_pBack = new CBackGround;
	m_pBack->Initialize();
	m_pBack->SetMainView(this);

	//����̽� �̴ϼȶ�����
	ENGINE::GetDeviceManager()->InitDevice(ENGINE::CGraphicDevice::WINDOWED_TRUE,
		g_hWnd,
		WINCX,
		WINCY);

	ENGINE::GetTimeManager()->InitTime();

	//�ؽ��� ����
	ENGINE::GetResourceManager()->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tile",
		L"../../../Client/bin/Resources/Texture/Tile/%d.bmp", 109);

	SetTimer(1, 100, NULL);
	m_pStaticCamera = CStaticCamera::Create(OBJECT_TYPE_STATIC);
	m_pStaticCamera->SetTarget(m_pBack->m_pInfo);

}

void CToolView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	ENGINE::GetDeviceManager()->DestroyInstance();
	ENGINE::CTimeManager::DestroyInstance();
	ENGINE::GetInputManager()->DestroyInstance();
	ENGINE::GetResourceManager()->DestroyInstance();
	ENGINE::GetInfoSubject()->DestroyInstance();
	if(m_pStaticCamera != NULL)
		SAFE_DELETE(m_pStaticCamera);

	if(m_pGameObject !=NULL)
		SAFE_DELETE(m_pGameObject);

	if(m_pBack != NULL)
		SAFE_DELETE(m_pBack);
}

void CToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnTimer(nIDEvent);

	ENGINE::GetInputManager()->SetKeyState(g_hWnd, false);

	ENGINE::GetTimeManager()->SetTime();

	m_pBack->Update();

	m_pStaticCamera->Update();
}
