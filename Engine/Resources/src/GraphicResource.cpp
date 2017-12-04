#include "GraphicResource.h"

ENGINE::CGraphicResource::CGraphicResource(void)
:CComponent(NULL)
,m_pReferenceCount(new DWORD(0))
{

}

ENGINE::CGraphicResource::~CGraphicResource(void)
{
	
}

void ENGINE::CGraphicResource::Release(void)
{
	SAFE_DELETE(m_pReferenceCount);
}

void ENGINE::CGraphicResource::SetOwner(ENGINE::CGameObject* _pOwner)
{
	m_pOwner = _pOwner;
}
