#include "stdafx.h"
#include "CameraObserver.h"
#include "InfoSubject.h"
#include "Export_Function.h"

CCameraObserver::CCameraObserver(const void* _pOwner)
:CObserver(_pOwner)
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}

CCameraObserver::~CCameraObserver(void)
{

}

CCameraObserver*	CCameraObserver::Create(const void* _pOwner)
{
	return new CCameraObserver(_pOwner);
}

void CCameraObserver::Update(int _iMessage)
{
	const ENGINE::CInfoSubject::DATA_LIST*	pDataList =
		ENGINE::GetInfoSubject()->GetDataList(_iMessage);
	if(pDataList == NULL)
		return;

	switch(_iMessage)
	{
	case MESSAGE_CAMERA_VIEW:
		m_matView = *static_cast<D3DXMATRIX*>(pDataList->front());
		break;
		
	case MESSAGE_CAMERA_PROJECTION:
		m_matProj = *static_cast<D3DXMATRIX*>(pDataList->front());
		break;
	}
}
const D3DXMATRIX* CCameraObserver::GetViewMatrix(void)
{
	return &m_matView;
}

const D3DXMATRIX* CCameraObserver::GetProjMatrix(void)
{
	return &m_matProj;
}