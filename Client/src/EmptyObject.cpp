#include "stdafx.h"
#include "EmptyObject.h"

#include "Export_Function.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "TerrainCollision.h"
#include "MouseCollision.h"
#include "OBBCollision.h"
#include "Col_Event_Functors.h"

CEmptyObject::CEmptyObject(eObjectType _eObjectType, float _fX, float _fY, float _fZ)
:CGameObject(_eObjectType)
,m_pInfo(NULL)
,m_pTerrainCollision(NULL)
,m_pMouseCollision(NULL)
,m_pOBBCollision(NULL)
,m_fX(_fX)
,m_fY(_fY)
,m_fZ(_fZ)
{

}

CEmptyObject::~CEmptyObject(void)
{
	Release();
}

CEmptyObject* CEmptyObject::Create(eObjectType _eObjectType, ENGINE::CCollisionFunctor* _pFunctor, float _fX, float _fY, float _fZ)
{
	CEmptyObject* pInstance = new CEmptyObject(_eObjectType, _fX, _fY, _fZ);
	pInstance->SetColFunctor(_pFunctor);
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CEmptyObject::Update(void)
{
	ENGINE::CGameObject::Update();

	return 0;
}

void CEmptyObject::Render(void)
{
	ENGINE::GetDevice()->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pOBBCollision->Render();
}

HRESULT CEmptyObject::Initialize(void)
{
	HRESULT hr = AddComponent();
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CEmptyObject::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	m_pInfo = ENGINE::CTransform::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", m_pInfo));

	m_pTerrainCollision = ENGINE::CTerrainCollision::Create(this, m_pInfo, new ENGINE::CColStop(m_pInfo, NULL));
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"TerrainCollision", m_pTerrainCollision));

	m_pOBBCollision = ENGINE::COBBCollision::Create(this, m_pInfo, NULL, m_fX, m_fY, m_fZ, m_pFunctor);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollision));

	m_pMouseCollision = ENGINE::CMouseCollision::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"MouseCollision", m_pMouseCollision));


	return S_OK;
}

void CEmptyObject::Release(void)
{

}

void CEmptyObject::SetPos(float _fX, float _fZ)
{
	m_pInfo->m_vPos.x = _fX;
	m_pInfo->m_vPos.z = _fZ;
}

void CEmptyObject::SetPos(D3DXVECTOR3& _vPos)
{
	m_pInfo->m_vPos = _vPos;
}
