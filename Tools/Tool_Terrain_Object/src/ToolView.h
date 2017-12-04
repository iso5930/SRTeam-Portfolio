/*!
 * \file ToolView.h
 * \date 2016/06/01 20:38
 *
 * \author ���ϴ�
 * Contact: user@company.com
 *
 * \brief ���� ���κ�.
 *
 * TODO: long description
 *
 * \note
*/


// ToolView.h : CToolView Ŭ������ �������̽�
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
protected: // serialization������ ��������ϴ�.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

public:
	CBackGround*	m_pBack;
	wstring			m_wstrTerrainKey;
	ENGINE::CGameObject*	m_pGameObject;
	CStaticCamera*			m_pStaticCamera;

// Ư���Դϴ�.
public:
	CToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // ToolView.cpp�� ����� ����
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

