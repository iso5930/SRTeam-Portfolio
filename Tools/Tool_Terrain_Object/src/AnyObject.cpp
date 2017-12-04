#include "stdafx.h"
#include "AnyObject.h"

CAnyObject::CAnyObject(eObjectType _eObjectType)
:CGameObject(_eObjectType)
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
	return 0;
}

void CAnyObject::Render(void)
{

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
	return S_OK;
}

void CAnyObject::Release(void)
{

}
