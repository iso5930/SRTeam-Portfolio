
// ToolView.cpp : CToolView 클래스의 구현
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CToolView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_pBack = NULL;
	m_pGameObject = NULL;
	m_pStaticCamera = NULL;

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

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


// CToolView 인쇄


void CToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기

void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//툴 창의 크기를 맞춰준다.
	CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWindow;
	pFrame->GetWindowRect(&rcWindow);

	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);

	RECT	rcMainView;
	GetClientRect(&rcMainView);

	float fRowFrm = float(rcWindow.right - rcMainView.right);
	float fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	pFrame->SetWindowPos(NULL, 0, 0, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);

	//핸들을 얻어온다.
	g_hWnd = m_hWnd;

	//백그라운드 초기화
	m_pBack = new CBackGround;
	m_pBack->Initialize();
	m_pBack->SetMainView(this);

	//디바이스 이니셜라이즈
	ENGINE::GetDeviceManager()->InitDevice(ENGINE::CGraphicDevice::WINDOWED_TRUE,
		g_hWnd,
		WINCX,
		WINCY);

	ENGINE::GetTimeManager()->InitTime();

	//텍스쳐 생성
	ENGINE::GetResourceManager()->AddTexture(RESOURCE_TYPE_STATIC, TEXTURE_TYPE_NORMAL, L"Tile",
		L"../../../Client/bin/Resources/Texture/Tile/%d.bmp", 109);

	SetTimer(1, 100, NULL);
	m_pStaticCamera = CStaticCamera::Create(OBJECT_TYPE_STATIC);
	m_pStaticCamera->SetTarget(m_pBack->m_pInfo);

}

void CToolView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnTimer(nIDEvent);

	ENGINE::GetInputManager()->SetKeyState(g_hWnd, false);

	ENGINE::GetTimeManager()->SetTime();

	m_pBack->Update();

	m_pStaticCamera->Update();
}
