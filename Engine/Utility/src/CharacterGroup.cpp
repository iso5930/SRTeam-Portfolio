#include "CharacterGroup.h"
#include "Export_Function.h"
#include "Character.h"
#include "Transform.h"
#include "MainUIObserver.h"

ENGINE::CCharacterGroup::CCharacterGroup(eObjectType _eObjectType)
:CGameObject(_eObjectType)
{

}

ENGINE::CCharacterGroup::~CCharacterGroup(void)
{
	Release();
}

ENGINE::CCharacterGroup* ENGINE::CCharacterGroup::Create(eObjectType _eObjectType)
{
	CCharacterGroup* pCharacterGroup = new CCharacterGroup(_eObjectType);

	if(FAILED(pCharacterGroup->Initialize()))
	{
		SAFE_DELETE(pCharacterGroup);
	}

	return pCharacterGroup;
}

HRESULT ENGINE::CCharacterGroup::Initialize(void)
{
	ENGINE::GetInfoSubject()->AddData(MESSAGE_CHARACTER_GROUP, this);
	ENGINE::GetInfoSubject()->Notify(MESSAGE_CHARACTER_GROUP);

	m_pMainUIObserver = ENGINE::CMainUIObserver::Create(this);
	ENGINE::GetInfoSubject()->Subscribe(m_pMainUIObserver);

	return S_OK;
}

void ENGINE::CCharacterGroup::Release(void)
{
	for(size_t i = 0; i < m_vecCharacter.size(); ++i)
	{
		SAFE_DELETE(m_vecCharacter[i]);
	}

	m_vecCharacter.clear();
}

int ENGINE::CCharacterGroup::Update(void)
{
	if(ENGINE::GetManagement()->GetGameObject(L"ResultBoard") != NULL)
	{
		return 0;
	}

	if(ENGINE::GetBattleManeger()->GetBattleStart())
	{
		ENGINE::GetBattleManeger()->Update();

		return 0;
	}

	bool bMainUI = m_pMainUIObserver->GetSwitch();

	if(bMainUI == false)
	{
		return 0;
	}

	m_vecCharacter[0]->Update();

	if (ENGINE::GetInputManager()->GetOnEvent())
	{
		for(size_t i = 1; i < m_vecCharacter.size(); ++i)
		{
			m_vecCharacter[i]->Update();
		}
	}
	else
	{
		for(size_t i = 1; i < m_vecCharacter.size(); ++i)
		{
			m_vecCharacter[i]->SubCharacterUpdate(m_vecCharacter[i - 1]->GetMemento());
		}
	}
	

	ENGINE::GetInfoSubject()->Notify(MESSAGE_CHARACTER_GROUP);

	return 0;
}

void ENGINE::CCharacterGroup::Render(void)
{
	if(ENGINE::GetBattleManeger()->GetBattleStart())
	{
		ENGINE::GetBattleManeger()->Render();
	}

	for(size_t i = 0; i < m_vecCharacter.size(); ++i)
	{
		if(m_vecCharacter[i]->GetCharacterState()->iHitPoint == 0)
		{
			continue;
		}
		m_vecCharacter[i]->Render();
	}
	ENGINE::GetInfoSubject()->Notify(MESSAGE_CHARACTER_GROUP);
}

vector<ENGINE::CCharacter*>* ENGINE::CCharacterGroup::GetCharacterGroup(void)
{
	return &m_vecCharacter;
}

HRESULT ENGINE::CCharacterGroup::GroupSort(vector<eCharacterID>* _pvecCharID)
{
	vector<ENGINE::CCharacter*> vecTemp;

	for(size_t i = 0; i < _pvecCharID->size(); ++i)
	{
		for(size_t j = 0; j < m_vecCharacter.size(); ++j)
		{
			if((*_pvecCharID)[i] == m_vecCharacter[j]->GetCharacterID())
			{
				vecTemp.push_back(m_vecCharacter[j]);
				break;
			}
		}
	}

	m_vecCharacter.clear();

	for(size_t i = 0; i < vecTemp.size(); ++i)
	{
		m_vecCharacter.push_back(vecTemp[i]);
	}

	////위치 정렬을 하자!!.

	D3DXVECTOR3 vPos = m_vecCharacter[0]->GetInfo()->m_vPos;

	for(size_t i = 0; i < m_vecCharacter.size(); ++i)
	{
		m_vecCharacter[i]->GetInfo()->m_vPos = vPos + D3DXVECTOR3(0.f, 0.f, i * 0.8f);
	}
	for(size_t i = 0; i < m_vecCharacter.size(); ++i)
	{
		m_vecCharacter[i]->GetMemento()->clear();
		m_vecCharacter[i]->SetDestPos(&(m_vecCharacter[i]->GetInfo()->m_vPos));
		m_vecCharacter[i]->ResetCharacter();
	}

	return S_OK;
}

HRESULT ENGINE::CCharacterGroup::GroupSort(void)
{
	D3DXVECTOR3 vPos = m_vecCharacter[0]->GetInfo()->m_vPos;

	m_vecCharacter[0]->SetCharacterState(Character_Stand);

	for(size_t i = 0; i < m_vecCharacter.size(); ++i)
	{
		m_vecCharacter[i]->GetInfo()->m_vPos = vPos + D3DXVECTOR3(0.f, 0.f, i * 0.8f);
	}
	for(size_t i = 0; i < m_vecCharacter.size(); ++i)
	{
		m_vecCharacter[i]->GetMemento()->clear();
		m_vecCharacter[i]->SetDestPos(&(m_vecCharacter[i]->GetInfo()->m_vPos));
		m_vecCharacter[i]->ResetCharacter();
		m_vecCharacter[i]->SetState();
		m_vecCharacter[i]->Render();
	}
	return S_OK;
}

void ENGINE::CCharacterGroup::AddCharacter(eCharacterID _eCharID, CCharacter* _pCharacter)
{
	for(size_t i = 0; i < m_vecCharacter.size(); ++i)
	{
		if(m_vecCharacter[i]->GetCharacterID() == _eCharID)
		{
			return;
		}
	}

	m_vecCharacter.push_back(_pCharacter);
}

ENGINE::CCharacter* ENGINE::CCharacterGroup::GetCharacter(eCharacterID _eCharID)
{
	for(size_t i = 0; i < m_vecCharacter.size(); ++i)
	{
		if(m_vecCharacter[i]->GetCharacterID() == _eCharID)
		{
			return m_vecCharacter[i];
		}
	}

	return NULL;
}

ENGINE::CCharacter* ENGINE::CCharacterGroup::GetLeaderCharacter(void)
{
	return m_vecCharacter[0];
}

void ENGINE::CCharacterGroup::PrepareFind(void)
{
	m_finder = m_vecCharacter.begin();
	m_finder_end = m_vecCharacter.end();

	if (m_finder != m_finder_end)
		(*m_finder)->PrepareFind();
}

ENGINE::CComponent* ENGINE::CCharacterGroup::GetComponent(const wstring& _strComponentKey)
{
	for (; m_finder != m_finder_end;)
	{
		ENGINE::CComponent* pComponent = (*m_finder)->GetComponent(_strComponentKey);
		if (pComponent != NULL)
			return pComponent;

		++m_finder;
		if (m_finder != m_finder_end)
			(*m_finder)->PrepareFind();
	}

	return NULL;
}

int ENGINE::CCharacterGroup::BattleUpdate(void)
{
	if(ENGINE::GetBattleManeger()->GetTurn())
	{
		for(size_t i = 0; i < m_vecCharacter.size(); ++i)
		{
			if(m_vecCharacter[i]->GetCharacterState()->iHitPoint == 0)
			{
				continue;
			}

			m_vecCharacter[i]->SetBillBoard();
		}	
	}
	else
	{
		for(size_t i = 0; i < m_vecCharacter.size(); ++i)
		{
			if(m_vecCharacter[i]->GetCharacterState()->iHitPoint == 0)
			{
				continue;
			}

			m_vecCharacter[i]->BattleUpdate();
		}	
	}
	return 0;
}	