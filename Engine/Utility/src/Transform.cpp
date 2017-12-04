#include "Transform.h"

#include "Pipeline.h"

ENGINE::CTransform::CTransform(ENGINE::CGameObject* _pOwner)
:CComponent(_pOwner)
,m_vPos(0.f, 0.f, 0.f)
,m_vDir(0.f, 0.f, 1.f)
,m_vScale(1.f, 1.f, 1.f)
{
	ZeroMemory(m_pAngle, sizeof(m_pAngle));
	D3DXMatrixIdentity(&m_matWorld);
}

ENGINE::CTransform::~CTransform(void)
{
	
}

ENGINE::CTransform* ENGINE::CTransform::Create(ENGINE::CGameObject* _pOwner)
{
	return new CTransform(_pOwner);
}

int ENGINE::CTransform::Update(void)
{
	ENGINE::CPipeline::MakeWorldMatrix(
		&m_matWorld,
		&m_vScale,
		m_pAngle,
		&m_vPos);

	return 0;
}
