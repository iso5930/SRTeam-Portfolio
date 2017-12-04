// TerrainPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "../home/Tool.h"
#include "TerrainPage.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TileTerrain.h"
#include "Export_Function.h"
#include "MouseCollision.h"


// CTerrainPage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTerrainPage, CPropertyPage)

CTerrainPage::CTerrainPage()
	: CPropertyPage(CTerrainPage::IDD)
	, m_iCountX(0)
	, m_iCountZ(0)
	, m_strTerrainKey(_T(""))
	, m_iTileMax(109)
	, m_fHeight(0)
{
	m_pMainFrame = ((CMainFrame*)AfxGetMainWnd());
	m_pMainView	=	m_pMainFrame->m_pMainView;
}

CTerrainPage::~CTerrainPage()
{

}

void CTerrainPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TERRAIN_SIZE_X_EDIT, m_iCountX);
	DDX_Text(pDX, IDC_TERRAIN_SIZE_Z_EDIT, m_iCountZ);
	DDX_Text(pDX, IDC_TERRAIN_KEY_EDIT, m_strTerrainKey);
	DDX_Control(pDX, IDC_TEXTURE_LISTBOX, m_TextureListBox);
	DDX_Text(pDX, IDC_TERRAIN_HEIGHT_EDIT, m_fHeight);
}


BEGIN_MESSAGE_MAP(CTerrainPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CREATE_TERRAIN_BUTTON, &CTerrainPage::OnBnClickedCreateTerrainButton)
	ON_BN_CLICKED(IDC_TERRAIN_FIX_BUTTON, &CTerrainPage::OnBnClickedTerrainFixButton)
	ON_BN_CLICKED(IDC_TEXTURE_FIX_BUTTON, &CTerrainPage::OnBnClickedTextureFixButton)
	ON_LBN_SELCHANGE(IDC_TEXTURE_LISTBOX, &CTerrainPage::OnLbnSelchangeTextureListbox)
	ON_BN_CLICKED(IDC_LEFT_UP_BUTTON, &CTerrainPage::OnBnClickedLeftUpButton)
	ON_BN_CLICKED(IDC_RIGHT_UP_BUTTON, &CTerrainPage::OnBnClickedRightUpButton)
	ON_BN_CLICKED(IDC_LEFT_DOWN_BUTTON, &CTerrainPage::OnBnClickedLeftDownButton)
	ON_BN_CLICKED(IDC_RIGHT_DOWN_BUTTON, &CTerrainPage::OnBnClickedRightDownButton)
	ON_BN_CLICKED(IDC_HEIGHT_APPLY_BUTTON, &CTerrainPage::OnBnClickedHeightApplyButton)
	ON_BN_CLICKED(IDC_ROTATE_CCW_BUTTON, &CTerrainPage::OnBnClickedRotateCcwButton)
	ON_BN_CLICKED(IDC_ROTATE_CW_BUTTON, &CTerrainPage::OnBnClickedRotateCwButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CTerrainPage::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_LOAD_BUTTON, &CTerrainPage::OnBnClickedLoadButton)
	ON_BN_CLICKED(IDC_RESET_TERRAIN_BUTTON, &CTerrainPage::OnBnClickedResetTerrainButton)
END_MESSAGE_MAP()


// CTerrainPage 메시지 처리기입니다.

void CTerrainPage::OnBnClickedCreateTerrainButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);		

	m_pGameObject = NULL;

	if(m_iCountX == 0 || m_iCountZ == 0 || m_strTerrainKey == L"")
		return;

	wstring wstrTemp;
	wstrTemp = m_strTerrainKey;

	m_pMainView->m_wstrTerrainKey = wstrTemp;

	//렉트 터레인
	ENGINE::GetResourceManager()->AddBuffer(
		RESOURCE_TYPE_DYNAMIC,
		ENGINE::CVIBuffer::BUFFER_TYPE_RECTANGLE_TERRAIN,
		wstrTemp,
		m_iCountX, m_iCountZ, 1);

	m_pMainView->m_pBack->SetReadVertexColor(m_iCountX, m_iCountZ, wstrTemp);

	//타일 터레인
	m_pGameObject = CTileTerrain::Create(OBJECT_TYPE_DYNAMIC, m_iCountX, m_iCountZ, 1, wstrTemp);

	m_pMainView->m_pBack->SetCollsionMouse(m_iCountX, m_iCountZ);

	m_pMainView->m_pBack->m_bCreateTerrain = true;
	
	m_pMainView->Invalidate(TRUE);
	
	UpdateData(FALSE);

}

void CTerrainPage::OnBnClickedTerrainFixButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_pMainView->m_pBack->m_bTerrainFix = true;
	m_pMainView->m_pBack->m_bTextureFix = false;

	m_pMainView->Invalidate(TRUE);

	UpdateData(FALSE);
}

void CTerrainPage::OnBnClickedTextureFixButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CMainFrame*		pMainFrame	=	((CMainFrame*)AfxGetMainWnd());
	CToolView*		pMainView	=	pMainFrame->m_pMainView;

	m_pMainView->m_pBack->m_bTerrainFix = false;
	m_pMainView->m_pBack->m_bTextureFix = true;

	m_pMainView->Invalidate(TRUE);

	UpdateData(FALSE);
}

BOOL CTerrainPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	for(int i = 0; i < m_iTileMax; ++i)
	{
		//리스트 박스 문자열 출력
		wstring wstrTemp = L"Tile";
		TCHAR szTemp2[10] = L"";
		_itow_s(i, szTemp2, 10);
		wstrTemp += szTemp2;
		m_TextureListBox.AddString(wstrTemp.c_str());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CTerrainPage::OnLbnSelchangeTextureListbox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iIndex = 0;

	m_pMainView->m_pBack->m_iTextureIndex = m_TextureListBox.GetCurSel();
	iIndex = m_TextureListBox.GetCurSel();

	wstring wstrTemp = L"../../../Client/bin/Resources/Texture/Tile/";//%d.bmp"
	TCHAR	szTemp[10] = L"";
	_itow_s(iIndex, szTemp, 10);
	wstrTemp += szTemp;
	wstrTemp += L".bmp";

	CWnd*	pWnd = (CWnd*)GetDlgItem(IDC_TEXTURE_PREVIEW);
	CDC*	pDc = pWnd->GetDC();
	CStatic* pStaticSize = (CStatic*)GetDlgItem(IDC_TEXTURE_PREVIEW);
	CRect	rect;

	pStaticSize->GetClientRect(rect);

	CImage	Image;
	Image.Load(wstrTemp.c_str());
	Image.Draw(pDc->m_hDC, 0, 0, 90, 90);

	
}

void CTerrainPage::OnBnClickedLeftUpButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_pMainView->m_pBack->m_eVertexDirect = VERTEX_DIRECT_LEFT_UP;

	UpdateData(FALSE);
}

void CTerrainPage::OnBnClickedRightUpButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_pMainView->m_pBack->m_eVertexDirect = VERTEX_DIRECT_RIGHT_UP;

	UpdateData(FALSE);
}

void CTerrainPage::OnBnClickedLeftDownButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_pMainView->m_pBack->m_eVertexDirect = VERTEX_DIRECT_LEFT_DOWN;

	UpdateData(FALSE);
}

void CTerrainPage::OnBnClickedRightDownButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_pMainView->m_pBack->m_eVertexDirect = VERTEX_DIRECT_RIGHT_DOWN;

	UpdateData(FALSE);
}

void CTerrainPage::OnBnClickedHeightApplyButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_fHeight;
	m_pMainView->m_pBack->m_fHeightValue = m_fHeight;
	UpdateData(FALSE);
}

void CTerrainPage::OnBnClickedRotateCcwButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	switch(m_pMainView->m_pBack->m_eTextureRotation)
	{
	case TEXTURE_ROTATION_UP :
		m_pMainView->m_pBack->m_eTextureRotation = TEXTURE_ROTATION_LEFT;
		break;

	case TEXTURE_ROTATION_LEFT :
		m_pMainView->m_pBack->m_eTextureRotation = TEXTURE_ROTATION_DOWN;
		break;

	case TEXTURE_ROTATION_DOWN :
		m_pMainView->m_pBack->m_eTextureRotation = TEXTURE_ROTATION_RIGHT;
		break;

	case TEXTURE_ROTATION_RIGHT :
		m_pMainView->m_pBack->m_eTextureRotation = TEXTURE_ROTATION_UP;
	}

	UpdateData(FALSE);
}

void CTerrainPage::OnBnClickedRotateCwButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	switch(m_pMainView->m_pBack->m_eTextureRotation)
	{
	case TEXTURE_ROTATION_UP :
		m_pMainView->m_pBack->m_eTextureRotation = TEXTURE_ROTATION_RIGHT;
		break;

	case TEXTURE_ROTATION_LEFT :
		m_pMainView->m_pBack->m_eTextureRotation = TEXTURE_ROTATION_UP;
		break;

	case TEXTURE_ROTATION_DOWN :
		m_pMainView->m_pBack->m_eTextureRotation = TEXTURE_ROTATION_LEFT;
		break;

	case TEXTURE_ROTATION_RIGHT :
		m_pMainView->m_pBack->m_eTextureRotation = TEXTURE_ROTATION_DOWN;
	}

	UpdateData(FALSE);
}

void CTerrainPage::OnBnClickedResetTerrainButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_strTerrainKey = L"";
	m_pMainView->m_wstrTerrainKey = m_strTerrainKey;
	ENGINE::GetResourceManager()->ReleaseDynamic();

	UpdateData(FALSE);
}


void CTerrainPage::OnBnClickedSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CFileDialog		FileDialog(FALSE, L"dat", NULL, OFN_EXPLORER, NULL, NULL);

	CString		strPathName;
	TCHAR		szCurDir[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH - 1, szCurDir);

	FileDialog.m_ofn.lpstrInitialDir = szCurDir;

	int iResult = FileDialog.DoModal();

	if(iResult == IDOK)
	{
		strPathName = FileDialog.GetPathName();
	}

	if(iResult == IDCANCEL)
		return;

	int					iCountX = dynamic_cast<CTileTerrain*>(m_pGameObject)->m_iCountX;
	int					iCountZ = dynamic_cast<CTileTerrain*>(m_pGameObject)->m_iCountZ;

	VERTEX_COLOR*		pVertexColor = m_pMainView->m_pBack->m_pVertexColor;
	vector<CTile*>*		pVecTile = &dynamic_cast<CTileTerrain*>(m_pGameObject)->m_vecTile;
	
	DWORD		dwByte = 0;

	HANDLE		hFile = CreateFile(strPathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(hFile, &iCountX, sizeof(int), &dwByte, NULL);
	WriteFile(hFile, &iCountZ, sizeof(int), &dwByte, NULL);
	
	for(int i = 0; i < iCountX * iCountZ; ++i)
	{
		WriteFile(hFile, &(pVertexColor[i]), sizeof(VERTEX_COLOR), &dwByte, NULL);
	}

	for(size_t i = 0; i < pVecTile->size(); ++i)
	{
		//WriteFile(hFile, (*pVecTile)[i], sizeof(CTile), &dwByte, NULL);
		WriteFile(hFile, (*pVecTile)[i]->m_pVertex, sizeof(VERTEX_TEXTURE) * 4, &dwByte, NULL);
		WriteFile(hFile, &(*pVecTile)[i]->m_iTextureIndex, sizeof(int), &dwByte, NULL);
		//WriteFile(hFile, &(*pVecTile)[i]->m_eTextureRotation, sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);

	AfxMessageBox(L"Save Complete");

	UpdateData(FALSE);
}

void CTerrainPage::OnBnClickedLoadButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CFileDialog	FileDialog(TRUE, L"*.*", NULL, OFN_EXPLORER, NULL, NULL);

	TCHAR	szCurDir[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH - 1, szCurDir);
	szCurDir[MAX_PATH - 1] = 0;

	FileDialog.m_ofn.lpstrInitialDir = szCurDir;

	CString strPathName;
	CString	strFileName;

	if(FileDialog.DoModal() == IDOK)
	{
		strPathName = FileDialog.GetPathName();
		strFileName = FileDialog.GetFileName();
	}

	if(FileDialog.DoModal() == IDCANCEL)
	{
		AfxMessageBox(L"Load Failed");
		return;
	}

	int iCountX, iCountZ;
	VERTEX_COLOR*		pVertexColor = m_pMainView->m_pBack->m_pVertexColor;//dynamic_cast<CTileTerrain*>(m_pGameObject)->m_pVertexColor;
	vector<CTile*>*		pVecTile = &dynamic_cast<CTileTerrain*>(m_pGameObject)->m_vecTile;

	DWORD	dwByte = 0;
	
	HANDLE	hFile = CreateFile(strPathName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == NULL)
		AfxMessageBox(L"로드 실패");

	for(size_t i = 0; i < pVecTile->size(); ++i)
	{
		delete	(*pVecTile)[i];
	}
	pVecTile->clear();

	ReadFile(hFile, &iCountX, sizeof(int), &dwByte, NULL);
	ReadFile(hFile, &iCountZ, sizeof(int), &dwByte, NULL);


	m_pMainView->m_pBack->m_pMouseCollision = CMouseCollision::Create(NULL, iCountX, iCountZ);

	pVertexColor = new VERTEX_COLOR[iCountX * iCountZ];

	for(int i = 0; i < iCountX * iCountZ; ++i)
	{
		ReadFile(hFile, &(pVertexColor[i]), sizeof(VERTEX_COLOR), &dwByte, NULL);
	}

	while(true)
	{
		CTile*	pTile = new CTile(OBJECT_TYPE_DYNAMIC);

		VERTEX_TEXTURE*	pVertexTexture = new VERTEX_TEXTURE[4];

		int iTextureIndex = 0;
		//eTextureRotation eRotateType = TEXTURE_ROTATION_UP;

		ReadFile(hFile, pVertexTexture, sizeof(VERTEX_TEXTURE) * 4, &dwByte, NULL);
		ReadFile(hFile, &iTextureIndex, sizeof(int), &dwByte, NULL);
		//ReadFile(hFile, &eRotateType, sizeof(int), &dwByte, NULL);

		pTile->LoadTile(pVertexTexture, iTextureIndex);

		if(dwByte == 0)
		{
			delete pTile;
			break;
		}

		pVecTile->push_back(pTile);
	}

	CloseHandle(hFile);

	wstring wstrTemp = strFileName;

	m_pMainView->m_wstrTerrainKey = wstrTemp;

	ENGINE::GetResourceManager()->AddBuffer(RESOURCE_TYPE_DYNAMIC, ENGINE::CVIBuffer::BUFFER_TYPE_RECTANGLE_TERRAIN, wstrTemp, iCountX, iCountZ, 1);

	ENGINE::GetResourceManager()->WriteVerticies(RESOURCE_TYPE_DYNAMIC, wstrTemp, pVertexColor);
	
	m_pMainView->m_pBack->SetReadVertexColor(iCountX, iCountZ, wstrTemp);

	//m_pGameObject = CTileTerrain::Create(iCountX, iCountZ, 1, wstrTemp);

	//int i = pVecTile->size();

	//for(size_t i = 0; i < pVecTile->size(); ++i)
	//{
	//	//dynamic_cast<CTileTerrain*>(m_pGameObject)->SetTileTexture(i, (*pVecTile)[i]->m_iTextureIndex, (*pVecTile)[i]->m_eTextureRotation);
	//}

	m_pMainView->m_pBack->SetTextureHeight(iCountX, iCountZ);

	m_pMainView->m_pBack->SetCollsionMouse(iCountX, iCountZ);

	AfxMessageBox(L"로드 성공...");

	m_strTerrainKey = strFileName;

	m_pMainView->Invalidate(TRUE);

	UpdateData(FALSE);
}
