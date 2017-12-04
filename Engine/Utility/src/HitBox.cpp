#include "HitBox.h"
#include "Monster.h"
#include "Character.h"
#include "Movement.h"
#include "OBBCollision.h"

ENGINE::CHitBox::CHitBox(eObjectType _eObjectType)
:CGameObject(_eObjectType), m_bCreate(false), m_pCheck(NULL)
{

}

ENGINE::CHitBox::~CHitBox(void)
{
	
}

ENGINE::CHitBox* ENGINE::CHitBox::Create(eObjectType _eObjectType, ENGINE::CGameObject* _pOwner, CGameObject* _pTarget, float _fCX, float _fCY, float _fCZ, int _iAtk, bool _bPush, bool _bPlayer /*= false*/)
{
	CHitBox* pHitBox = new CHitBox(_eObjectType);

	pHitBox->SetOwner(_pOwner, _bPlayer);

	pHitBox->SetTarget(_pTarget);

	if(FAILED(pHitBox->Initialize()))
	{
		SAFE_DELETE(pHitBox);
	}

	if(FAILED(pHitBox->AddOBBCollision(_fCX, _fCY, _fCZ, _iAtk, _bPush)))
	{
		SAFE_DELETE(pHitBox);
	}

	return pHitBox;
}

HRESULT ENGINE::CHitBox::Initialize(void)
{
	m_pCheck = new bool;

	(*m_pCheck) = false;

	return S_OK;
}

HRESULT ENGINE::CHitBox::AddOBBCollision(float _fCX, float _fCY, float _fCZ, int _iAtk, bool _bPush)
{
	ENGINE::CMonster* pMonster = NULL;
	ENGINE::CCharacter* pCharacter = NULL;
	ENGINE::CMovement* pMovement = NULL;

	if(m_bPlayer)
	{
		pCharacter = static_cast<ENGINE::CCharacter*>(m_pOwner);
		pMovement = static_cast<ENGINE::CMovement*>(pCharacter->GetComponent(L"Movement"));
		m_pOBBCollision = ENGINE::COBBCollision::Create(pCharacter, pCharacter->GetInfo(), pMovement, _fCX, _fCY, _fCZ, new CColMonsterHit(_iAtk, m_pCheck, m_pTarget, _bPush), m_bPlayer);
	}
	else
	{
		pMonster = static_cast<ENGINE::CMonster*>(m_pOwner);
		m_pOBBCollision = ENGINE::COBBCollision::Create(pMonster, pMonster->GetInfo(), pMonster->GetMovement(), _fCX, _fCY, _fCZ, new CColCharacterHit(_iAtk, m_pCheck, m_pTarget), m_bPlayer);
	}

	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollision));

	return S_OK;
}

void ENGINE::CHitBox::SetOwner(ENGINE::CGameObject* _pOwner, bool _bPlayer /*= false*/)
{
	m_pOwner = _pOwner;
	m_bPlayer = _bPlayer;
}

int ENGINE::CHitBox::Update(void)
{
	CGameObject::Update();
	
	if(m_bCreate)
	{
		return 1;
	}
	else if((*m_pCheck))
	{
		return 1;
	}

	m_bCreate = true;

	return 0;
}

ENGINE::CGameObject* ENGINE::CHitBox::GetOwner(void)
{
	return m_pOwner;
}

void ENGINE::CHitBox::Render(void)
{
	m_pOBBCollision->Render();
}

void ENGINE::CHitBox::SetTarget(CGameObject* _pTarget)
{
	m_pTarget = _pTarget;
}