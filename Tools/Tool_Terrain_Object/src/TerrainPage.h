/*!
 * \file TerrainPage.h
 * \date 2016/06/01 20:34
 *
 * \author 서하늘
 * Contact: user@company.com
 *
 * \brief 터레인 툴을 위한 페이지.
 *
 * TODO: long description
 *
 * \note
*/

#pragma once

#include "GameObject.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "BackGround.h"
#include "afxwin.h"

// CTerrainPage 대화 상자입니다.

class CTerrainPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTerrainPage)

public:
	CMainFrame*		m_pMainFrame;
	CToolView*		m_pMainView;

public:
	CTerrainPage();
	virtual ~CTerrainPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TERRAINPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	//터레인 X, Z 카운트
	int m_iCountX;
	int m_iCountZ;
	int	m_iTileMax;

	ENGINE::CGameObject* m_pGameObject;
	
	//터레인 생성 버튼
	afx_msg void OnBnClickedCreateTerrainButton();
	CString m_strTerrainKey;
	afx_msg void OnBnClickedTerrainFixButton();
	afx_msg void OnBnClickedTextureFixButton();
	CListBox m_TextureListBox;
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeTextureListbox();
	afx_msg void OnBnClickedLeftUpButton();
	afx_msg void OnBnClickedRightUpButton();
	afx_msg void OnBnClickedLeftDownButton();
	afx_msg void OnBnClickedRightDownButton();
	afx_msg void OnBnClickedHeightApplyButton();
	float m_fHeight;
	afx_msg void OnBnClickedRotateCcwButton();
	afx_msg void OnBnClickedRotateCwButton();
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedLoadButton();
	afx_msg void OnBnClickedResetTerrainButton();
};
