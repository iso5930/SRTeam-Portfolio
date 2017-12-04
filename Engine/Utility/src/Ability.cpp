#include "Ability.h"

ENGINE::CAbility::CAbility(eObjectType _eObjectType)
:CGameObject(_eObjectType)
,m_tAbiliIconFrame(0, 3, 10), m_dwTime(0), m_bField(false), m_iDamage(0)
{

}

ENGINE::CAbility::~CAbility(void)
{

}

int ENGINE::CAbility::Update(void)
{
	return 0;
}

void ENGINE::CAbility::Render(void)
{
	
}

void ENGINE::CAbility::DrawAbility(float _fY)
{	
	m_fY = _fY;

	this->Render();
}

void ENGINE::CAbility::SetField(bool _bField)
{
	m_bField = _bField;
}

const wstring ENGINE::CAbility::GetAbilityName(void)
{	
	return m_wstrAbilityName;
}

void ENGINE::CAbility::SetDamage(int _iDamage)
{
	m_iDamage = _iDamage;
}
