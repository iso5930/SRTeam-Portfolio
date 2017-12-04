/*!
 * \file MyToolSheet.h
 * \date 2016/06/01 20:32
 *
 * \author ���ϴ�
 * Contact: user@company.com
 *
 * \brief �ͷ��� �������� ������Ʈ �������� �θ� ��Ʈ.
 *
 * TODO: long description
 *
 * \note
*/

#pragma once
#include "TerrainPage.h"
#include "ObjectPage.h"



// CMyToolSheet

class CMyToolSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyToolSheet)

public:
	CTerrainPage	m_TerrainPage;
	CObjectPage		m_ObjectPage;


public:
	CMyToolSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMyToolSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMyToolSheet(void);
	virtual ~CMyToolSheet();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};


