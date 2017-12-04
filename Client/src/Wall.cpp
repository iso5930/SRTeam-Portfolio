#include "stdafx.h"
#include "Wall.h"
#include "Transform.h"
#include "RectangleTexture.h"
#include "Export_Function.h"
#include "Texture.h"
#include "Sprite.h"
#include "TerrainInfo.h"
#include "RectangleWave.h"
#include "TerrainCollision.h"

#include "OBBCollision.h"


CWall::CWall(eObjectType _eObjectType)
:Cetc(_eObjectType)
, m_fSpeed(0.0001f)
, m_fAngle(0.f)
, m_iNum(0)
,m_pOBBCollision(NULL)
{
}

CWall::~CWall()
{
	Release();
}

void CWall::SetDirection(void)
{
}

CWall* CWall::Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos, int iNum, float fAngle)
{
	CWall*		pWall = new CWall(_eObjectType);

	pWall->Initialize(_vPos, iNum, fAngle);

	return pWall;
}

HRESULT CWall::Initialize(void)
{
	return S_OK;
}

HRESULT CWall::Initialize(D3DXVECTOR3 _vPos, int iNum, float fAngle)
{
	HRESULT hr = AddComponent();

	m_pInfo->m_vScale /= 2.f;
	m_pInfo->m_vPos = _vPos;
	m_pInfo->m_vPos.x -= 0.5f;
	m_pInfo->m_vPos.y += 0.5f;
	m_pInfo->m_vPos.z -= 0.5f;

	//m_pInfo->m_matWorld._42 += 0.5f;
	
	m_iNum = iNum;
	m_fAngle = fAngle;
	m_pInfo->m_pAngle[ANGLE_TYPE_Y] = D3DXToRadian(m_fAngle);

	return S_OK;
}

int CWall::Update(void)
{
	ENGINE::CGameObject::Update();

	return 0;
}	

void CWall::Render(void)
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

	m_pTexture->Render(m_iNum);
	m_pVIBuffer->Render();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pOBBCollision->Render();
}

void CWall::Release(void)
{
}

HRESULT CWall::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Cube_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_DYNAMIC, L"Wall_Nomal");
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Wall_Nomal", pComponent));

	m_pOBBCollision = ENGINE::COBBCollision::Create(this, m_pInfo, NULL, m_pInfo->m_vScale.x * 0.5f, m_pInfo->m_vScale.y * 0.5f, m_pInfo->m_vScale.z * 0.5f, new ENGINE::CColSliding, false, true);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollision));

	return S_OK;
}

void CWall::SetPos(const D3DXVECTOR3& vPos)
{
	m_pInfo->m_vPos = vPos;
}
