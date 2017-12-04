#include "Component.h"

ENGINE::CComponent::CComponent(ENGINE::CGameObject* _pOwner)
:m_pOwner(_pOwner)
{

}

ENGINE::CComponent::~CComponent(void)
{
	
}

int ENGINE::CComponent::Update(void)
{
	return 0;
}

const ENGINE::CGameObject* ENGINE::CComponent::GetOwner(void) const
{
	return m_pOwner;
}
