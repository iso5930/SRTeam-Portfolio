/*!
 * \file ObjectPage.h
 * \date 2016/06/01 20:34
 *
 * \author ���ϴ�
 * Contact: user@company.com
 *
 * \brief ������Ʈ ���� ���� ������.
 *
 * TODO: long description
 *
 * \note
*/

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
};
