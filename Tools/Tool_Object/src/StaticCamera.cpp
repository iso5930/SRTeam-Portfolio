#include "stdafx.h"

#include "StaticCamera.h"
#include "Transform.h"

#include "Export_Function.h"

CStaticCamera::CStaticCamera(eObjectType _eObjectType)
:CCamera(_eObjectType)
,m_pTargetInfo(NULL)
,m_fTargetDistance(0.f)
,m_fAngle(0.f)
{

}

CStaticCamera::~CStaticCamera(void)
{
	Release();
}

CStaticCamera* CStaticCamera::Create(eObjectType _eObjectType)
{
	CStaticCamera* pInstance = new CStaticCamera(_eObjectType);
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CStaticCamera::Update(void)
{
	KeyCheck();

	//! 정리할 것..
	D3DXVECTOR3 vEye;
	D3DXVECTOR3 vAt;

	vEye = m_pTargetInfo->m_vDir * -1;
	D3DXVec3Normalize(&vEye, &vEye);
	vEye *= m_fTargetDistance;

	D3DXVECTOR3 vRight;
	memcpy(&vRight, m_pTargetInfo->m_matWorld.m[0], sizeof(float) * 3);

	D3DXMATRIX matRotAxis;
	D3DXMatrixRotationAxis(&matRotAxis, &vRight, m_fAngle);
	D3DXVec3TransformNormal(&vEye, &vEye, &matRotAxis);

	vEye += m_pTargetInfo->m_vPos;
	vAt	= m_pTargetInfo->m_vPos;
	
	CCamera::SetViewSpaceMatrix(&vEye, &vAt, &D3DXVECTOR3(0.f, 1.f, 0.f));
	CCamera::SetProjectionMatrix(D3DXToRadian(45.f), float(WINCX) / WINCY, 1.f, 1000.f);

	return 0;
}

HRESULT CStaticCamera::Initialize(void)
{
	m_fTargetDistance = 10.f;
	m_fAngle = D3DXToRadian(45.f);

	return S_OK;
}

void CStaticCamera::KeyCheck(void)
{
	float fTimeDelta = ENGINE::GetTimeDelta();

	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_Q))
		m_fAngle += D3DXToRadian(45.f) * fTimeDelta;
	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_E))
		m_fAngle -= D3DXToRadian(45.f) * fTimeDelta;

	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_Z))
	{
		if(m_fTargetDistance < 11.f)
			m_fTargetDistance += 20.f * fTimeDelta;
	}
	else if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_A))
	{
		if(m_fTargetDistance > 9.f)
			m_fTargetDistance -= 20.f * fTimeDelta;
	}
	else
	{
		if(m_fTargetDistance > 10.f)
			m_fTargetDistance -= 20.f * fTimeDelta;
		if(m_fTargetDistance < 10.f)
			m_fTargetDistance += 20.f * fTimeDelta;
		if(int(m_fTargetDistance) == 10)
			m_fTargetDistance = 10.f;
	}
}

void CStaticCamera::Release(void)
{

}

void CStaticCamera::SetTargetInfo(const ENGINE::CTransform* _pTargetInfo)
{
	m_pTargetInfo = _pTargetInfo;
}
