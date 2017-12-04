#include "stdafx.h"
#include "AnyObject.h"

#include "Transform.h"
#include "Export_Function.h"
#include "Texture.h"

CAnyObject::CAnyObject(eObjectType _eObjectType)
:CGameObject(_eObjectType)
,m_pInfo(NULL)
,m_pBuffer(NULL)
,m_pTexture(NULL)
{

}

CAnyObject::~CAnyObject(void)
{
	Release();
}

CAnyObject* CAnyObject::Create(eObjectType _eObjectType)
{
	CAnyObject* pInstance = new CAnyObject(_eObjectType);
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CAnyObject::Update(void)
{
	ENGINE::CGameObject::Update();

	return 0;
}

void CAnyObject::Render(void)
{
	ENGINE::GetDevice()->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pTexture->Render(0);
	m_pBuffer->Render(0);
}

HRESULT CAnyObject::Initialize(void)
{
	HRESULT hr = AddComponent();
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CAnyObject::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	m_pInfo = ENGINE::CTransform::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", m_pInfo));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this,
		RESOURCE_TYPE_STATIC,
		L"Buffer_Cube_Texture");
	m_pBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Buffer", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this,
		RESOURCE_TYPE_DYNAMIC,
		L"Texture_Cube_Example");
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Texture", pComponent));

	return S_OK;
}

void CAnyObject::Release(void)
{

}
