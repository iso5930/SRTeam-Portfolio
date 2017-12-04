#include "stdafx.h"
#include "CubeObject.h"

#include "Stage.h"
#include "TerrainCollision.h"
#include "Transform.h"
#include "Texture.h"
#include "Export_Function.h"

CCubeObject::CCubeObject(eObjectType _eObjectType)
:CGameObject(_eObjectType)
,m_pInfo(NULL)
,m_pVIBuffer(NULL)
,m_pTexture(NULL)
,m_pTerrainCollision(NULL)
,m_pTerrainVertex(NULL)
{

}

CCubeObject::~CCubeObject(void)
{
	Release();
}

CCubeObject* CCubeObject::Create(eObjectType _eObjectType, const D3DXVECTOR3& _vPos)
{
	CCubeObject* pInstance = new CCubeObject(_eObjectType);
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	pInstance->SetPos(_vPos);

	return pInstance;
}

int CCubeObject::Update(void)
{
	SetDirection();

	ENGINE::CGameObject::Update();

	return 0;
}

void CCubeObject::Render(void)
{
	LPDIRECT3DDEVICE9 pDevice = ENGINE::GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	ENGINE::GetDevice()->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pTexture->Render(0);
	m_pVIBuffer->Render();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

HRESULT CCubeObject::Initialize(void)
{
	HRESULT hr = AddComponent();
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CCubeObject::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Cube_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_DYNAMIC, L"Texture_Cube");
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Texture", pComponent));

	m_pTerrainCollision = ENGINE::CTerrainCollision::Create(this, m_pInfo, new ENGINE::CColStop(m_pInfo, NULL)); //! nullÀÌ¸é.. À½..
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"TerrainCollision", m_pTerrainCollision));

	return S_OK;
}

void CCubeObject::SetDirection(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &D3DXVECTOR3(0.f, 0.f, 1.f), &m_pInfo->m_matWorld);
	D3DXVec3Normalize(&m_pInfo->m_vDir, &m_pInfo->m_vDir);
}

void CCubeObject::Release(void)
{
	
}

void CCubeObject::SetPos(const D3DXVECTOR3& _vPos)
{
	m_pInfo->m_vPos = _vPos;
}
