#include "AbilityGroup.h"

#include "Ability.h"

ENGINE::CAbilityGroup::CAbilityGroup(eObjectType _eObjectType)
:CGameObject(_eObjectType)
{

}

ENGINE::CAbilityGroup::~CAbilityGroup(void)
{
	Release();
}	

ENGINE::CAbilityGroup* ENGINE::CAbilityGroup::Create(eObjectType _eObjectType, eCharacterID _CharID)
{
	CAbilityGroup* pAbilityGroup = new CAbilityGroup(_eObjectType);

	if(pAbilityGroup->Initialize(_CharID))
	{
		SAFE_DELETE(pAbilityGroup);
	}

	return pAbilityGroup;
}

HRESULT ENGINE::CAbilityGroup::Initialize(void)
{
	return S_OK;
}

HRESULT ENGINE::CAbilityGroup::Initialize(eCharacterID _CharID)
{
	m_eCharID = _CharID;

	return S_OK;
}

int ENGINE::CAbilityGroup::Update(void)
{
	return 0;
}

void ENGINE::CAbilityGroup::Render(void)
{
	
}

eCharacterID ENGINE::CAbilityGroup::GetCharacterID(void)
{
	return m_eCharID;
}

vector<ENGINE::CAbility*>* ENGINE::CAbilityGroup::GetAbility(void)
{
	return &m_vecAbility;
}

void ENGINE::CAbilityGroup::AddAbility(CAbility* _pAbility)
{
	m_vecAbility.push_back(_pAbility);
}

void ENGINE::CAbilityGroup::Release(void)
{
	for(size_t i = 0; i < m_vecAbility.size(); ++i)
	{
		SAFE_DELETE(m_vecAbility[i]);
	}
	m_vecAbility.clear();
}
