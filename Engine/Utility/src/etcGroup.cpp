#include "etcGroup.h"
#include "etc.h"
#include "Export_System.h"

ENGINE::CetcGroup::CetcGroup(eObjectType _eObjectType)
:CGameObject(_eObjectType)
{

}

ENGINE::CetcGroup::~CetcGroup(void)
{
	Release();
}

ENGINE::CetcGroup* ENGINE::CetcGroup::Create(eObjectType _eObjectType)
{
	CetcGroup* petcGroup = new CetcGroup(_eObjectType);

	if(FAILED(petcGroup->Initialize()))
	{
		SAFE_DELETE(petcGroup);
	}

	return petcGroup;
}

HRESULT ENGINE::CetcGroup::Initialize(void)
{
	return S_OK;
}

int ENGINE::CetcGroup::Update(void)
{	
	if(ENGINE::GetBattleManeger()->GetBattleStart())
	{
		return 0;
	}
	else
		m_vecetc[0]->Update();

	return 0;
}		

void ENGINE::CetcGroup::Render(void)
{
	if(ENGINE::GetBattleManeger()->GetBattleStart())
	{
		for(size_t i = 0; i < m_vecetc.size(); ++i)
		{
			m_vecetc[i]->Render();
		}
	}
	else
		m_vecetc[0]->Render();
}

void ENGINE::CetcGroup::Release(void)
{
	for(size_t i = 0; i < m_vecetc.size(); ++i)
	{
		SAFE_DELETE(m_vecetc[i]);
	}
	m_vecetc.clear();
}

void ENGINE::CetcGroup::Addetc(Cetc* _petc)
{
	m_vecetc.push_back(_petc);
}

vector<ENGINE::Cetc*>* ENGINE::CetcGroup::GetetcGroup(void)
{
	return &m_vecetc;
}


void ENGINE::CetcGroup::PrepareFind(void)
{
	m_finder = m_vecetc.begin();
	m_finder_end = m_vecetc.end();

	if (m_finder != m_finder_end)
		(*m_finder)->PrepareFind();
}

ENGINE::CComponent* ENGINE::CetcGroup::GetComponent(const wstring& _strComponentKey)
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
