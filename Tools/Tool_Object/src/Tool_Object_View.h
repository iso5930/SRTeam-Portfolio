
// Tool_Object_View.h : CTool_Object_View 클래스의 인터페이스
//


#pragma once


class CTool_Object_Doc;
class CTool_Object_View : public CView
{
protected: // serialization에서만 만들어집니다.
	CTool_Object_View();
	DECLARE_DYNCREATE(CTool_Object_View)

// 특성입니다.
public:
	CTool_Object_Doc* GetDocument() const;

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
	virtual ~CTool_Object_View();
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
private:
	void SetWindowSize(void);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // Tool_Object_View.cpp의 디버그 버전
inline CTool_Object_Doc* CTool_Object_View::GetDocument() const
   { return reinterpret_cast<CTool_Object_Doc*>(m_pDocument); }
#endif

