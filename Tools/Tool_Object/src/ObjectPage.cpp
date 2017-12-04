// C:\Users\Administrator\Desktop\srproject1\trunk\SRTeam1\Tools\Tool_Object\src\ObjectPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "../home/Tool_Object.h"
#include "ObjectPage.h"

#include "AnyObject.h"
#include "Export_Function.h"
#include "VIBuffer.h"
#include "StaticCamera.h"
#include "Transform.h"


// CObjectPage 대화 상자입니다.
CAnyObject* g_pObject = NULL;
CStaticCamera* g_pCamera = NULL;

IMPLEMENT_DYNAMIC(CObjectPage, CPropertyPage)

CObjectPage::CObjectPage()
	: CPropertyPage(CObjectPage::IDD)
{

}

CObjectPage::~CObjectPage()
{
	SAFE_DELETE(g_pObject);

	SAFE_DELETE(g_pCamera);
}

void CObjectPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CObjectPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CREATE_NEW_OBJ, &CObjectPage::OnBnClickedCreateNewObj)
	ON_BN_CLICKED(IDC_DELETE_OBJ, &CObjectPage::OnBnClickedDeleteObj)
END_MESSAGE_MAP()


// CObjectPage 메시지 처리기입니다.

void CObjectPage::OnBnClickedCreateNewObj()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (g_pObject == NULL)
	{
		g_pObject = CAnyObject::Create(OBJECT_TYPE_DYNAMIC);

		g_pCamera = CStaticCamera::Create(OBJECT_TYPE_DYNAMIC);

		g_pObject->PrepareFind();
		ENGINE::CComponent* pTransform = g_pObject->GetComponent(L"Transform");

		g_pCamera->SetTargetInfo(static_cast<const ENGINE::CTransform*>(pTransform));
	}
}

void CObjectPage::OnBnClickedDeleteObj()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SAFE_DELETE(g_pObject);

	SAFE_DELETE(g_pCamera);
}
