#pragma once
#include "objectpage.h"



// CLeftSheet

class CLeftSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CLeftSheet)

public:
	CLeftSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CLeftSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CLeftSheet(void);
	virtual ~CLeftSheet();

protected:
	DECLARE_MESSAGE_MAP()
private:
	CObjectPage m_ObjectPage;
public:
	virtual BOOL OnInitDialog();
};


