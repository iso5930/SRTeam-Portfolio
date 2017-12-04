/*!
 * \file MyToolView.h
 * \date 2016/06/01 20:32
 *
 * \author 서하늘
 * Contact: user@company.com
 *
 * \brief 시트를 보여주기 위한 뷰.
 *
 * TODO: long description
 *
 * \note
*/
#pragma once


// CMyToolView 뷰입니다.

class CMyToolSheet;
class CMyToolView : public CView
{
	DECLARE_DYNCREATE(CMyToolView)

public:
	CMyToolSheet*	m_pMyToolSheet;

protected:
	CMyToolView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyToolView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};


