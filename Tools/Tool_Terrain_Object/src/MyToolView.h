/*!
 * \file MyToolView.h
 * \date 2016/06/01 20:32
 *
 * \author ���ϴ�
 * Contact: user@company.com
 *
 * \brief ��Ʈ�� �����ֱ� ���� ��.
 *
 * TODO: long description
 *
 * \note
*/
#pragma once


// CMyToolView ���Դϴ�.

class CMyToolSheet;
class CMyToolView : public CView
{
	DECLARE_DYNCREATE(CMyToolView)

public:
	CMyToolSheet*	m_pMyToolSheet;

protected:
	CMyToolView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyToolView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
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


