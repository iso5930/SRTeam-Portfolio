/*!
 * \file ObjectPage.h
 * \date 2016/06/01 20:34
 *
 * \author 서하늘
 * Contact: user@company.com
 *
 * \brief 오브젝트 툴을 위한 페이지.
 *
 * TODO: long description
 *
 * \note
*/

#pragma once

// CObjectPage 대화 상자입니다.

class CObjectPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CObjectPage)


public:
	CObjectPage();
	virtual ~CObjectPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OBJECTPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
};
