#include "stdafx.h"
#include "Water.h"
#include "Transform.h"
#include "RectangleTexture.h"
#include "Export_Function.h"
#include "Texture.h"
#include "Sprite.h"
#include "TerrainInfo.h"
#include "RectangleWave.h"


CWater::CWater(eObjectType _eObjectType)
:Cetc(_eObjectType)
, m_fHight(1.f)
, m_bControl(false)
, m_fSpeed(0.0001f)
{
}

CWater::~CWater()
{
	Release();
}

void CWater::SetDirection(void)
{
}

CWater* CWater::Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos, float fStart)
{
	CWater*		pWater = new CWater(_eObjectType);

	pWater->Initialize(_vPos, fStart);

	return pWater;
}

HRESULT CWater::Initialize(void)
{
	return S_OK;
}

HRESULT CWater::Initialize(D3DXVECTOR3 _vPos, float fStart)
{
	HRESULT hr = AddComponent();

	m_pInfo->m_vPos = _vPos;
	m_pInfo->m_vScale /= 25.f;

	m_pInfo->m_vScale.y = fStart;

	//m_pInfo->m_pAngle[ANGLE_TYPE_X] = 1.57075f; 

	m_fSpeed = 0.0005f;

	return S_OK;
}

int CWater::Update(void)
{
	ENGINE::CGameObject::Update();

	if(m_pInfo->m_vScale.y >= 0.03f)
		m_bControl = false;
	if(m_pInfo->m_vScale.y <= -0.03f)
		m_bControl = true;

	if(m_pInfo->m_vScale.y < 0.03f && m_bControl == true)
		m_pInfo->m_vScale.y += m_fSpeed;
	else if(m_pInfo->m_vScale.y > -0.03f && m_bControl == false)
		m_pInfo->m_vScale.y -= m_fSpeed;

	return 0;
}	

void CWater::Render(void)
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

	m_pTexture->Render(int(m_pSprite->GetCurFrame()));
	m_pVIBuffer->Render();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CWater::Release(void)
{
}

HRESULT CWater::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Wave_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));

	/*pComponent = ENGINE::CRectangleWave::Create(129, 129, 1);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Wave_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);À¸¿¢
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));*/

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Water_Nomal");
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Water_Nomal", pComponent));
	
	pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 31.f, 21.f));
	m_pSprite = static_cast<ENGINE::CSprite*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Water_Frame", pComponent));


	return S_OK;
}

void CWater::SetPos(const D3DXVECTOR3& vPos)
{
	m_pInfo->m_vPos = vPos;
}
