// C:\Users\Administrator\Desktop\srproject1\trunk\SRTeam1\Tools\Tool_Object\src\ObjectPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "../home/Tool_Object.h"
#include "ObjectPage.h"

#include "AnyObject.h"
#include "Export_Function.h"
#include "VIBuffer.h"
#include "StaticCamera.h"
#include "Transform.h"


// CObjectPage ��ȭ �����Դϴ�.
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


// CObjectPage �޽��� ó�����Դϴ�.

void CObjectPage::OnBnClickedCreateNewObj()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SAFE_DELETE(g_pObject);

	SAFE_DELETE(g_pCamera);
}
