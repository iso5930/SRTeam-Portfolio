#include "StdAfx.h"
#include "Terrain.h"
#include "Transform.h"
#include "Pipeline.h"
#include "Texture.h"
#include "Export_Function.h"

CTerrain::CTerrain(void)
{
}

CTerrain::~CTerrain(void)
{
	Release();
}

CTerrain* CTerrain::Create(void)
{
	CTerrain* pInstance = new CTerrain;
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	//m_iCountX = _iCountX;
	//m_iCountZ = _iCountZ;

	//int m_iCountTotal = m_iCountX + m_iCountZ;
	//m_vecTile->reserve(m_iCountTotal);

	return pInstance;
}

int CTerrain::Update(void)
{
	
	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_LEFT))
		m_pInfo->m_pAngle[ANGLE_TYPE_Y] += 0.01f;
	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_RIGHT))
		m_pInfo->m_pAngle[ANGLE_TYPE_Y] -= 0.01f;

	ENGINE::CPipeline::MakeWorldMatrix(
		&m_pInfo->m_matWorld,
		&D3DXVECTOR3(1.f, 1.f, 1.f),
		m_pInfo->m_pAngle,
		&m_pInfo->m_vPos);
	
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &D3DXVECTOR3(0.f, 0.f, 1.f), &m_pInfo->m_matWorld);
	D3DXVec3Normalize(&m_pInfo->m_vDir, &m_pInfo->m_vDir);

	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_UP))
		m_pInfo->m_vPos += m_pInfo->m_vDir * 0.01f;
	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_DOWN))
		m_pInfo->m_vPos -= m_pInfo->m_vDir * 0.01f;

	return 0;
}

void CTerrain::Render(void)
{

}

HRESULT CTerrain::Initialize(void)
{

	return S_OK;
}

HRESULT CTerrain::AddComponent(void)
{

	return S_OK;
}

void CTerrain::Release(void)
{

}