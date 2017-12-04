#include "Inventory.h"

#include "Item.h"

ENGINE::CInventory::CInventory(eObjectType _eObjectType)
:CGameObject(_eObjectType)
{

}

ENGINE::CInventory::~CInventory(void)
{
	Release();
}

ENGINE::CInventory* ENGINE::CInventory::Create(eObjectType _eObjectType)
{
	CInventory* pInventory = new CInventory(_eObjectType);

	if(FAILED(pInventory->Initialize(0)))
	{
		SAFE_DELETE(pInventory);
	}

	return pInventory;
}

HRESULT ENGINE::CInventory::Initialize(void)
{
	return S_OK;
}

HRESULT ENGINE::CInventory::Initialize(int iNum)
{
	return S_OK;
}

int ENGINE::CInventory::Update(void)
{
	int a = 10;

	return 0;
}	

void ENGINE::CInventory::Render(void)
{

}

vector<ENGINE::CItem*>* ENGINE::CInventory::GetvecInven(void)
{
	return &m_vecInven;
}

void ENGINE::CInventory::Release(void)
{
	for(size_t i = 0; i < m_vecInven.size(); ++i)
	{
		SAFE_DELETE(m_vecInven[i]);
	}
	m_vecInven.clear();
}
