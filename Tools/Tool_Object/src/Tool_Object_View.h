
// Tool_Object_View.h : CTool_Object_View Ŭ������ �������̽�
//


#pragma once


class CTool_Object_Doc;
class CTool_Object_View : public CView
{
protected: // serialization������ ��������ϴ�.
	CTool_Object_View();
	DECLARE_DYNCREATE(CTool_Object_View)

// Ư���Դϴ�.
public:
	CTool_Object_Doc* GetDocument() const;

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
	virtual ~CTool_Object_View();
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
private:
	void SetWindowSize(void);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // Tool_Object_View.cpp�� ����� ����
inline CTool_Object_Doc* CTool_Object_View::GetDocument() const
   { return reinterpret_cast<CTool_Object_Doc*>(m_pDocument); }
#endif

