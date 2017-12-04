#include "Equip.h"

#include "Item.h"

ENGINE::CEquip::CEquip(eObjectType _eObjectType)
:CGameObject(_eObjectType)
{

}

ENGINE::CEquip::~CEquip(void)
{
	Release();
}

ENGINE::CEquip* ENGINE::CEquip::Create(eObjectType _eObjectType, eCharacterID _CharID)
{
	CEquip* pEquip = new CEquip(_eObjectType);

	if(FAILED(pEquip->Initialize(_CharID)))
	{
		SAFE_DELETE(pEquip);
	}

	return pEquip;
}

HRESULT ENGINE::CEquip::Initialize(void)
{
	return S_OK;
}

void ENGINE::CEquip::InitEquip(int iNum)
{
	//m_iNum = iNum;
}

HRESULT ENGINE::CEquip::Initialize(eCharacterID _CharID)
{
	m_eCharID = _CharID;

	/*
	������ �߰���� :

	pItem->m_iNum		= ���� �������� �󸶳� ������ �ִ°�?
	pItem->m_bFree		= ������ �ش� �������� �����ϰ� �ִ°�?
	pItem->m_eID		= �����ϰ� �ִ°� ������? (�������� �ƴ϶�� CHARACTER_END���� ��)
	pItem->m_iType		= ����� Ÿ���� ���?
	pItem->m_iImgCode	= �κ��丮���� ����ؾ� �ϴ� �̹����� ���° �̹����ΰ�?
	pItem->m_szName		= ����� �̸��� �����ΰ�?
	pItem->m_iItemCode	= ����� ������ ��ȣ�� �����ΰ�? (�κ��丮���� ��� ��ü � ����, �׳� ��� �ٸ� ��ȣ�� OK)
	pItem->m_bCursorOn	= Ŀ���� ����� ���� �ִ°�?
	pItem->m_bSelect	= �ش� ��� �����ߴ°�?

	
	������ �̷�������...
	if((*vecEquip)[i]->m_iType == TYPE_CAP && (*vecEquip)[i]->m_eID == eCharID)
	{
		CPage::DrawText((*vecEquip)[i]->m_szName, D3DCOLOR_ARGB(255, 0, 0, 0), 240.f, 375.f);
		DrawSprite(RESOURCE_TYPE_STATIC, L"Item", 442.f, 375.f, (*vecEquip)[i]->m_iImgCode, NULL); //����
	}
	*/

	for(int i = 0; i < 14; ++i)
	{
		if(i == 0 || i == 6)
		{
			CItem*	pItem = new CItem(OBJECT_TYPE_STATIC);

			pItem->m_iNum = 1;
			pItem->m_bFree = false;
			pItem->m_eID = CHARACTER_END;
			pItem->m_iType = TYPE_CAP;
			pItem->m_iImgCode = i + 2;
			if(i == 0)
				wsprintf(pItem->m_szName, L"���и���");
			if(i == 6)
				wsprintf(pItem->m_szName, L"���̻��︧");
			pItem->m_iItemCode = i;
			pItem->m_bCursorOn = false;
			pItem->m_bSelect = false;

			pItem->m_iBP = 5;
			pItem->m_iAtk = 0;
			pItem->m_iDef = 2;
			pItem->m_iSpd = 1;
			pItem->m_iMag = 1;
			pItem->m_iCri = 1;

			m_vecEquip.push_back(pItem);
		}
		else if(i == 1 || i == 7)
		{
			CItem*	pItem = new CItem(OBJECT_TYPE_STATIC);

			pItem->m_iNum = 1;
			pItem->m_bFree = false;
			pItem->m_eID = CHARACTER_END;
			pItem->m_iType = TYPE_WEAPON;
			pItem->m_iImgCode = i + 2;
			if(i == 1)
				wsprintf(pItem->m_szName, L"���̺�ΰ�");
			if(i == 7)
				wsprintf(pItem->m_szName, L"��ε�ҵ�");
			pItem->m_iItemCode = i;
			pItem->m_bCursorOn = false;
			pItem->m_bSelect = false;

			pItem->m_iBP = 2;
			pItem->m_iAtk = 6;
			pItem->m_iDef = 3;
			pItem->m_iSpd = 1;
			pItem->m_iMag = 8;
			pItem->m_iCri = 10;

			m_vecEquip.push_back(pItem);
		}
		else if(i == 2 || i == 8)
		{
			CItem*	pItem = new CItem(OBJECT_TYPE_STATIC);

			pItem->m_iNum = 1;
			pItem->m_bFree = false;
			pItem->m_eID = CHARACTER_END;
			pItem->m_iType = TYPE_ARMOUR;
			pItem->m_iImgCode = i + 2;
			if(i == 2)
				wsprintf(pItem->m_szName, L"������");
			if(i == 8)
				wsprintf(pItem->m_szName, L"��ũ��Ʈ");
			pItem->m_iItemCode = i;
			pItem->m_bCursorOn = false;
			pItem->m_bSelect = false;
			
			pItem->m_iBP = 9;
			pItem->m_iAtk = 0;
			pItem->m_iDef = 0;
			pItem->m_iSpd = 0;
			pItem->m_iMag = 1;
			pItem->m_iCri = 3;

			m_vecEquip.push_back(pItem);
		}
		else if(i == 3 || i == 9)
		{
			CItem*	pItem = new CItem(OBJECT_TYPE_STATIC);

			pItem->m_iNum = 1;
			pItem->m_bFree = false;
			pItem->m_eID = CHARACTER_END;
			pItem->m_iType = TYPE_SHOES;
			pItem->m_iImgCode = i + 2;
			if(i == 3)
				wsprintf(pItem->m_szName, L"����");
			if(i == 9)
				wsprintf(pItem->m_szName, L"��������ȭ");
			pItem->m_iItemCode = i;
			pItem->m_bCursorOn = false;
			pItem->m_bSelect = false;
			
			pItem->m_iBP = 3;
			pItem->m_iAtk = 1;
			pItem->m_iDef = 3;
			pItem->m_iSpd = 4;
			pItem->m_iMag = 2;
			pItem->m_iCri = 5;

			m_vecEquip.push_back(pItem);
		}
		else if(i == 4 || i == 10)
		{
			CItem*	pItem = new CItem(OBJECT_TYPE_STATIC);

			pItem->m_iNum = 1;
			pItem->m_bFree = false;
			pItem->m_eID = CHARACTER_END;
			pItem->m_iType = TYPE_WEAR;
			pItem->m_iImgCode = i + 2;
			if(i == 4)
				wsprintf(pItem->m_szName, L"����Ʈ��");
			if(i == 10)
				wsprintf(pItem->m_szName, L"��ư���÷�");
			pItem->m_iItemCode = i;
			pItem->m_bCursorOn = false;
			pItem->m_bSelect = false;
			
			pItem->m_iBP = 3;
			pItem->m_iAtk = 1;
			pItem->m_iDef = 3;
			pItem->m_iSpd = 1;
			pItem->m_iMag = 2;
			pItem->m_iCri = 2;

			m_vecEquip.push_back(pItem);
		}
		else if(i == 5 || i == 11)
		{
			CItem*	pItem = new CItem(OBJECT_TYPE_STATIC);

			pItem->m_iNum = 1;
			pItem->m_bFree = false;
			pItem->m_eID = CHARACTER_END;
			pItem->m_iType = TYPE_SHIELD;
			pItem->m_iImgCode = i + 2;
			if(i == 5)
				wsprintf(pItem->m_szName, L"��Ŭ��");
			if(i == 11)
				wsprintf(pItem->m_szName, L"ī�����ǵ�");
			pItem->m_iItemCode = i;
			pItem->m_bCursorOn = false;
			pItem->m_bSelect = false;
			
			pItem->m_iBP = 10;
			pItem->m_iAtk = 3;
			pItem->m_iDef = 0;
			pItem->m_iSpd = 0;
			pItem->m_iMag = 0;
			pItem->m_iCri = 0;

			m_vecEquip.push_back(pItem);
		}
	}

	CItem*	pItem = new CItem(OBJECT_TYPE_STATIC);

	pItem->m_iNum = 1;
	pItem->m_bFree = false;
	pItem->m_eID = CHARACTER_END;
	pItem->m_iType = TYPE_ACCESSORY1;
	pItem->m_iImgCode = 14;
	wsprintf(pItem->m_szName, L"�����ǹ���");
	pItem->m_iItemCode = 14;
	pItem->m_bCursorOn = false;
	pItem->m_bSelect = false;
	
	pItem->m_iBP = 5;
	pItem->m_iAtk = 5;
	pItem->m_iDef = 5;
	pItem->m_iSpd = 5;
	pItem->m_iMag = 5;
	pItem->m_iCri = 5;

	m_vecEquip.push_back(pItem);

	pItem = new CItem(OBJECT_TYPE_STATIC);

	pItem->m_iNum = 1;
	pItem->m_bFree = false;
	pItem->m_eID = CHARACTER_END;
	pItem->m_iType = TYPE_ACCESSORY1;
	pItem->m_iImgCode = 15;
	wsprintf(pItem->m_szName, L"��Ż��");
	pItem->m_iItemCode = 15;
	pItem->m_bCursorOn = false;
	pItem->m_bSelect = false;
	
	pItem->m_iBP = 5;
	pItem->m_iAtk = 5;
	pItem->m_iDef = 5;
	pItem->m_iSpd = 5;
	pItem->m_iMag = 5;
	pItem->m_iCri = 5;

	m_vecEquip.push_back(pItem);

	pItem = new CItem(OBJECT_TYPE_STATIC);

	pItem->m_iNum = 1;
	pItem->m_bFree = false;
	pItem->m_eID = CHARACTER_END;
	pItem->m_iType = TYPE_ACCESSORY1;
	pItem->m_iImgCode = 16;
	wsprintf(pItem->m_szName, L"���극�̽���");
	pItem->m_iItemCode = 16;
	pItem->m_bCursorOn = false;
	pItem->m_bSelect = false;
	
	pItem->m_iBP = 5;
	pItem->m_iAtk = 5;
	pItem->m_iDef = 5;
	pItem->m_iSpd = 5;
	pItem->m_iMag = 5;
	pItem->m_iCri = 5;

	m_vecEquip.push_back(pItem);
	
	pItem = new CItem(OBJECT_TYPE_STATIC);

	pItem->m_iNum = 1;
	pItem->m_bFree = false;
	pItem->m_eID = CHARACTER_END;
	pItem->m_iType = TYPE_ACCESSORY1;
	pItem->m_iImgCode = 17;
	wsprintf(pItem->m_szName, L"�����Ÿ��");
	pItem->m_iItemCode = 17;
	pItem->m_bCursorOn = false;
	pItem->m_bSelect = false;
	
	pItem->m_iBP = 5;
	pItem->m_iAtk = 5;
	pItem->m_iDef = 5;
	pItem->m_iSpd = 5;
	pItem->m_iMag = 5;
	pItem->m_iCri = 5;

	m_vecEquip.push_back(pItem);
	
	pItem = new CItem(OBJECT_TYPE_STATIC);

	pItem->m_iNum = 1;
	pItem->m_bFree = false;
	pItem->m_eID = CHARACTER_END;
	pItem->m_iType = TYPE_ACCESSORY1;
	pItem->m_iImgCode = 18;
	wsprintf(pItem->m_szName, L"�����ǵ�");
	pItem->m_iItemCode = 18;
	pItem->m_bCursorOn = false;
	pItem->m_bSelect = false;
	
	pItem->m_iBP = 5;
	pItem->m_iAtk = 5;
	pItem->m_iDef = 5;
	pItem->m_iSpd = 5;
	pItem->m_iMag = 5;
	pItem->m_iCri = 5;

	m_vecEquip.push_back(pItem);

	pItem = new CItem(OBJECT_TYPE_STATIC);

	pItem->m_iNum = 1;
	pItem->m_bFree = false;
	pItem->m_eID = CHARACTER_END;
	pItem->m_iType = TYPE_ACCESSORY1;
	pItem->m_iImgCode = 19;
	wsprintf(pItem->m_szName, L"����̾");
	pItem->m_iItemCode = 19;
	pItem->m_bCursorOn = false;
	pItem->m_bSelect = false;
	
	pItem->m_iBP = 5;
	pItem->m_iAtk = 5;
	pItem->m_iDef = 5;
	pItem->m_iSpd = 5;
	pItem->m_iMag = 5;
	pItem->m_iCri = 5;

	m_vecEquip.push_back(pItem);

	pItem = new CItem(OBJECT_TYPE_STATIC);

	pItem->m_iNum = 1;
	pItem->m_bFree = false;
	pItem->m_eID = CHARACTER_END;
	pItem->m_iType = TYPE_WEAPON;
	pItem->m_iImgCode = 20;
	wsprintf(pItem->m_szName, L"���");
	pItem->m_iItemCode = 20;
	pItem->m_bCursorOn = false;
	pItem->m_bSelect = false;
	
	pItem->m_iBP = 5;
	pItem->m_iAtk = 10;
	pItem->m_iDef = 3;
	pItem->m_iSpd = 3;
	pItem->m_iMag = 3;
	pItem->m_iCri = 1;

	m_vecEquip.push_back(pItem);

	pItem = new CItem(OBJECT_TYPE_STATIC);

	pItem->m_iNum = 1;
	pItem->m_bFree = false;
	pItem->m_eID = CHARACTER_END;
	pItem->m_iType = TYPE_WEAPON;
	pItem->m_iImgCode = 21;
	wsprintf(pItem->m_szName, L"��������");
	pItem->m_iItemCode = 21;
	pItem->m_bCursorOn = false;
	pItem->m_bSelect = false;
	
	pItem->m_iBP = 5;
	pItem->m_iAtk = 10;
	pItem->m_iDef = 3;
	pItem->m_iSpd = 3;
	pItem->m_iMag = 3;
	pItem->m_iCri = 1;

	m_vecEquip.push_back(pItem);

	pItem = new CItem(OBJECT_TYPE_STATIC);

	pItem->m_iNum = 1;
	pItem->m_bFree = false;
	pItem->m_eID = CHARACTER_END;
	pItem->m_iType = TYPE_WEAPON;
	pItem->m_iImgCode = 24;
	wsprintf(pItem->m_szName, L"�׷���Ʈ�ҵ�");
	pItem->m_iItemCode = 24;
	pItem->m_bCursorOn = false;
	pItem->m_bSelect = false;
	
	pItem->m_iBP = 5;
	pItem->m_iAtk = 10;
	pItem->m_iDef = 3;
	pItem->m_iSpd = 3;
	pItem->m_iMag = 3;
	pItem->m_iCri = 1;

	m_vecEquip.push_back(pItem);

	pItem = new CItem(OBJECT_TYPE_STATIC);

	pItem->m_iNum = 1;
	pItem->m_bFree = false;
	pItem->m_eID = CHARACTER_END;
	pItem->m_iType = TYPE_WEAPON;
	pItem->m_iImgCode = 25;
	wsprintf(pItem->m_szName, L"����");
	pItem->m_iItemCode = 25;
	pItem->m_bCursorOn = false;
	pItem->m_bSelect = false;
	
	pItem->m_iBP = 5;
	pItem->m_iAtk = 10;
	pItem->m_iDef = 3;
	pItem->m_iSpd = 3;
	pItem->m_iMag = 3;
	pItem->m_iCri = 1;

	m_vecEquip.push_back(pItem);

	return S_OK;
}

int ENGINE::CEquip::Update(void)
{
	return 0;
}

void ENGINE::CEquip::Render(void)
{

}

eCharacterID ENGINE::CEquip::GetCharacterID(void)
{
	return m_eCharID;
}

vector<ENGINE::CItem*>* ENGINE::CEquip::GetvecEquip(void)
{
	return &m_vecEquip;
}

void ENGINE::CEquip::Release(void)
{
	for(size_t i = 0; i < m_vecEquip.size(); ++i)
	{
		SAFE_DELETE(m_vecEquip[i]);
	}
	m_vecEquip.clear();
}
