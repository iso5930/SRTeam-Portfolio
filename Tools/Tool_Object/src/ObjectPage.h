#pragma once


// CObjectPage ��ȭ �����Դϴ�.
class CObjectPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CObjectPage)

public:
	CObjectPage();
	virtual ~CObjectPage();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_OBJECTPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCreateNewObj();
	afx_msg void OnBnClickedDeleteObj();
};
