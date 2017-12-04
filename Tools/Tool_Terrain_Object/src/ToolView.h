/*!
 * \file ToolView.h
 * \date 2016/06/01 20:38
 *
 * \author 서하늘
 * Contact: user@company.com
 *
 * \brief 툴의 메인뷰.
 *
 * TODO: long description
 *
 * \note
*/


// ToolView.h : CToolView 클래스의 인터페이스
//


#pragma once

#include "Device.h"
#include "StaticCamera.h"

class CToolDoc;
class CBackGround;

namespace ENGINE
{
	class	CGraphicDevice;
	class	CGameObject;
}

class CToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

public:
	CBackGround*	m_pBack;
	wstring			m_wstrTerrainKey;
	ENGINE::CGameObject*	m_pGameObject;
	CStaticCamera*			m_pStaticCamera;

// 특성입니다.
public:
	CToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // ToolView.cpp의 디버그 버전
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

