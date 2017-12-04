#include "stdafx.h"
#include "SwitchObject.h"

#include "Export_Function.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "TerrainCollision.h"
#include "MouseCollision.h"
#include "OBBCollision.h"
#include "Col_Event_Functors.h"

CSwitchObject::CSwitchObject(eObjectType _eObjectType, ENGINE::CCollisionFunctor* _pFunctor)
:CGameObject(_eObjectType)
,m_pBuffer(NULL)
,m_pTexture(NULL)
,m_pInfo(NULL)
,m_pTerrainCollision(NULL)
,m_pMouseCollision(NULL)
,m_pOBBCollision(NULL)
,m_pFunctor(_pFunctor)
{

}

CSwitchObject::~CSwitchObject(void)
{
	Release();
}

CSwitchObject* CSwitchObject::Create(eObjectType _eObjectType, const wstring& _strTextureKey, ENGINE::CCollisionFunctor* _pFunctor)
{
	CSwitchObject* pInstance = new CSwitchObject(_eObjectType, _pFunctor);
	pInstance->SetTextureKey(_strTextureKey);
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CSwitchObject::Update(void)
{
	ENGINE::CGameObject::Update();

	return 0;
}

void CSwitchObject::Render(void)
{
	ENGINE::GetDevice()->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	LPDIRECT3DDEVICE9 pDevice = ENGINE::GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pTexture->Render(0);
	//m_pTexture->Render((int)m_pSpriteFrame->GetCurFrame());
	m_pBuffer->Render();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pOBBCollision->Render();
}

HRESULT CSwitchObject::Initialize(void)
{
	HRESULT hr = AddComponent();
	if FAILED(hr)
		return hr;

	SetD3DXVector3(&m_pInfo->m_vScale, 0.5f, 0.5f, 1.f);

	m_pInfo->m_pAngle[ANGLE_TYPE_X] = D3DXToRadian(90.f);

	m_pInfo->m_vPos.y += 0.2f;

	return S_OK;
}

HRESULT CSwitchObject::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Rectangle_Texture");
	m_pBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Buffer", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_DYNAMIC, m_strTextureKey);
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Texture", pComponent));

	m_pInfo = ENGINE::CTransform::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", m_pInfo));

	//m_pTerrainCollision = ENGINE::CTerrainCollision::Create(this, m_pInfo, new ENGINE::CColStop(m_pInfo, NULL));
	//m_ComponentMap.insert(COMPONENT_MAP::value_type(L"TerrainCollision", m_pTerrainCollision));

	m_pOBBCollision = ENGINE::COBBCollision::Create(this, m_pInfo, NULL, 0.5f, 0.5f, 0.5f, m_pFunctor);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollision));

	m_pMouseCollision = ENGINE::CMouseCollision::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"MouseCollision", m_pMouseCollision));


	return S_OK;
}

void CSwitchObject::Release(void)
{

}

void CSwitchObject::SetTextureKey(const wstring& _strTextureKey)
{
	m_strTextureKey = _strTextureKey;
}

void CSwitchObject::SetPos(float _fX, float _fZ)
{
	m_pInfo->m_vPos.x = _fX;
	m_pInfo->m_vPos.z = _fZ;
}
