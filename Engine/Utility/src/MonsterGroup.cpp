#include "MonsterGroup.h"
#include "Monster.h"
#include "Export_System.h"
#include "Transform.h"
#include "Export_Function.h"
#include "MainUIObserver.h"

ENGINE::CMonsterGroup::CMonsterGroup(eObjectType _eObjectType)
:CGameObject(_eObjectType), m_bMonsterDeath(false), m_pMainUIObserver(NULL)
{

}

ENGINE::CMonsterGroup::~CMonsterGroup(void)
{
	Release();
}

ENGINE::CMonsterGroup* ENGINE::CMonsterGroup::Create(eObjectType _eObjectType)
{
	CMonsterGroup* pMonsterGroup = new CMonsterGroup(_eObjectType);

	if(FAILED(pMonsterGroup->Initialize()))
	{
		SAFE_DELETE(pMonsterGroup);
	}

	return pMonsterGroup;
}

HRESULT ENGINE::CMonsterGroup::Initialize(void)
{
	m_pMainUIObserver = ENGINE::CMainUIObserver::Create(this);
	ENGINE::GetInfoSubject()->Subscribe(m_pMainUIObserver);

	return S_OK;
}

int ENGINE::CMonsterGroup::Update(void)
{	
	if(m_pMainUIObserver->GetSwitch() == false)
	{
		return 0;
	}

	if(ENGINE::GetManagement()->GetGameObject(L"ResultBoard") != NULL)
	{
		return 0;
	}

	if(m_bMonsterDeath)
	{
		return 1;
	}

	if(ENGINE::GetBattleManeger()->GetBattleStart())
	{
		if(ENGINE::GetBattleManeger()->GetTurn())
		{
			for(size_t i = 0; i < m_vecMonster.size(); ++i)
			{
				m_vecMonster[i]->SetBillBoard();
			}
		}
		else
		{
			for(size_t i = 0; i < m_vecMonster.size(); ++i)
			{
				m_vecMonster[i]->BattleUpdate();
			}
		}
		return 0;
	}
	else
		m_vecMonster[0]->Update();

	return 0;
}		

void ENGINE::CMonsterGroup::Render(void)
{
	if(m_bMonsterDeath)
	{
		return;
	}

	if(ENGINE::GetBattleManeger()->GetBattleStart())
	{
		for(size_t i = 0; i < m_vecMonster.size(); ++i)
		{
			m_vecMonster[i]->Render();
		}
	}
	else
		m_vecMonster[0]->Render();
}

void ENGINE::CMonsterGroup::Release(void)
{
	for(size_t i = 0; i < m_vecMonster.size(); ++i)
	{
		SAFE_DELETE(m_vecMonster[i]);
	}
	m_vecMonster.clear();
}

void ENGINE::CMonsterGroup::AddMonster(CMonster* _pMonster)
{
	m_vecMonster.push_back(_pMonster);

	for(size_t i = 0; i < m_vecMonster.size(); ++i)
	{
		TCHAR szFullName[50] = L"";
		TCHAR szName[50] = L"Enemy%d";

		wsprintf(szFullName, szName, i);

		m_vecMonster[i]->SetSubName(szFullName);
	}
}

vector<ENGINE::CMonster*>* ENGINE::CMonsterGroup::GetMonsterGroup(void)
{
	return &m_vecMonster;
}

void ENGINE::CMonsterGroup::PrepareFind(void)
{
	m_finder = m_vecMonster.begin();
	m_finder_end = m_vecMonster.end();

	if (m_finder != m_finder_end)
		(*m_finder)->PrepareFind();
}

ENGINE::CComponent* ENGINE::CMonsterGroup::GetComponent(const wstring& _strComponentKey)
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

void ENGINE::CMonsterGroup::SetMonsterDeath(void)
{
	m_bMonsterDeath = true;
}

void ENGINE::CMonsterGroup::DeleteMonster(int _iCur)
{
	if(size_t(_iCur) > m_vecMonster.size())
	{
		return;
	}

	vector<ENGINE::CMonster*>::iterator iter = m_vecMonster.begin();

	for(int i = 0; i < _iCur; ++i)
	{
		++iter;
	}

	iter = m_vecMonster.erase(iter);
}

void ENGINE::CMonsterGroup::BattleInit(void)
{
	D3DXVECTOR3 vPos = m_vecMonster[0]->GetInfo()->m_vPos;

	for(size_t i = 0; i < m_vecMonster.size(); ++i)
	{
		m_vecMonster[i]->SetState(MONSTER_STAND);

		m_vecMonster[i]->SetPos(vPos);
	}
}

ENGINE::CMonster* ENGINE::CMonsterGroup::GetLeaderMonster(void)
{
	return m_vecMonster[0];
}