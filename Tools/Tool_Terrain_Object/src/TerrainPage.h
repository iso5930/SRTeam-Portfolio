/*!
 * \file TerrainPage.h
 * \date 2016/06/01 20:34
 *
 * \author ���ϴ�
 * Contact: user@company.com
 *
 * \brief �ͷ��� ���� ���� ������.
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

// CTerrainPage ��ȭ �����Դϴ�.

class CTerrainPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTerrainPage)

public:
	CMainFrame*		m_pMainFrame;
	CToolView*		m_pMainView;

public:
	CTerrainPage();
	virtual ~CTerrainPage();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TERRAINPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	//�ͷ��� X, Z ī��Ʈ
	int m_iCountX;
	int m_iCountZ;
	int	m_iTileMax;

	ENGINE::CGameObject* m_pGameObject;
	
	//�ͷ��� ���� ��ư
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
