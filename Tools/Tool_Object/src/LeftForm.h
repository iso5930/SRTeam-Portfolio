#pragma once



// CLeftForm �� ���Դϴ�.

class CLeftSheet;
class CLeftForm : public CFormView
{
	DECLARE_DYNCREATE(CLeftForm)

protected:
	CLeftForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CLeftForm();

public:
	enum { IDD = IDD_LEFTFORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	CLeftSheet* m_LeftSheet;
public:
	virtual void OnInitialUpdate();
};


