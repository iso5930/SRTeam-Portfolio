#include "Camera.h"

#include "Pipeline.h"
#include "Export_Function.h"

ENGINE::CCamera::CCamera(eObjectType _eObjectType)
:CGameObject(_eObjectType)
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}

ENGINE::CCamera::~CCamera(void)
{

}

void ENGINE::CCamera::SetViewSpaceMatrix(const D3DXVECTOR3* _pEye, const D3DXVECTOR3* _pAt, const D3DXVECTOR3* _pUp)
{
	CPipeline::MakeViewMatrix(&m_matView, _pEye, _pAt, _pUp);
	ENGINE::GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);
}

void ENGINE::CCamera::SetProjectionMatrix(const float _fFovY, const float _fAspect, const float _fNear, const float _fFar)
{
	CPipeline::MakeProjMatrix(&m_matProj, _fFovY, _fAspect, _fNear, _fFar);
	ENGINE::GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matProj);
}
