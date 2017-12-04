#include "StdAfx.h"
#include "StaticCamera.h"
#include "TimeManager.h"
#include "Transform.h"
#include "GraphicDevice.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "Export_Function.h"
#include "InfoSubject.h"

CStaticCamera::CStaticCamera(eObjectType _eObjectType)
: CCamera(_eObjectType)
, m_pTargetInfo(NULL)
, m_fTargetDistance(0.f)
, m_fCameraSpeed(0.f)
, m_fAngle(0.f)
{
}

CStaticCamera::~CStaticCamera(void)
{
	Release();
}

CStaticCamera*	CStaticCamera::Create(eObjectType _eObjectType)
{
	CStaticCamera*	pInstance = new CStaticCamera(_eObjectType);
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CStaticCamera::Update(void)
{
	KeyCheck();

	// target renewal
	D3DXVECTOR3 vEye;//(0.f, 60.f, -80.f);
	D3DXVECTOR3 vAt;

	vEye = m_pTargetInfo->m_vDir * (-1);
	D3DXVec3Normalize(&vEye, &vEye);

	vEye *= m_fTargetDistance;

	D3DXVECTOR3		vRight;
	memcpy(&vRight, &m_pTargetInfo->m_matWorld.m[0][0], sizeof(float) * 3);

	D3DXMATRIX	matRotAxis;
	D3DXMatrixRotationAxis(&matRotAxis, &vRight, m_fAngle);
	D3DXVec3TransformNormal(&vEye, &vEye, &matRotAxis);


	vEye += m_pTargetInfo->m_vPos;
	vAt	= m_pTargetInfo->m_vPos;
	
	CCamera::SetViewSpaceMatrix(&vEye, &vAt, &D3DXVECTOR3(0.f, 1.f, 0.f));
	CCamera::SetProjectionMatrix(D3DXToRadian(45.f), float(WINCX) / float(WINCY), 1.f, 1000.f);

	ENGINE::GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);
	ENGINE::GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matProj);

	ENGINE::GetInfoSubject()->Notify(MESSAGE_CAMERA_VIEW);
	ENGINE::GetInfoSubject()->Notify(MESSAGE_CAMERA_PROJECTION);

	return 0;
}

HRESULT CStaticCamera::Initialize(void)
{
	m_fCameraSpeed = 10.f;
	m_fTargetDistance = 10.f;
	m_fAngle = D3DXToRadian(45.f);

	ENGINE::GetInfoSubject()->AddData(MESSAGE_CAMERA_VIEW, &m_matView);
	ENGINE::GetInfoSubject()->AddData(MESSAGE_CAMERA_PROJECTION, &m_matProj);

	return S_OK;
}

void CStaticCamera::KeyCheck(void)
{
	float fElapsedTime = ENGINE::GetTimeDelta();

	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_Q))
		m_fAngle += D3DXToRadian(45.f) * fElapsedTime;
	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_E))
		m_fAngle -= D3DXToRadian(45.f) * fElapsedTime;

	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_O))
		m_fTargetDistance += 20.f * fElapsedTime;//0.02;
	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_P))
		m_fTargetDistance -= 20.f * fElapsedTime;//0.02;

	CMainFrame*		pMainFrame	=	((CMainFrame*)AfxGetMainWnd());
	pMainFrame->m_pMainView->OnDraw(NULL);//Invalidate(TRUE);

}

void CStaticCamera::Release(void)
{

}

void CStaticCamera::SetTarget(const ENGINE::CTransform* _pTargetInfo)
{
	m_pTargetInfo = _pTargetInfo;
}
