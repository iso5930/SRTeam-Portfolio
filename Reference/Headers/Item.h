/*!
 * \file Item.h
 * \date 2016/06/06 14:42
 *
 * \author ������
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Item_h__
#define Item_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CItem : public CGameObject
{
	enum eEquipType {TYPE_STRAT, TYPE_CAP, TYPE_WEAPON, TYPE_ARMOUR, TYPE_SHOES, TYPE_WEAR, TYPE_SHIELD, TYPE_ACCESSORY1, TYPE_ACCESSORY2};
public:
	virtual int Update(void);
	virtual void Render(void);
	virtual HRESULT Initialize(void);
	virtual HRESULT Initialize(eObjectType _eObjectType);
	static CItem* Create(eObjectType _eObjectType);

public:
	int				m_iNum;					// ��� ������ �ִ°�?
	bool			m_bFree;				// ���� �����Ѱ�?
	eCharacterID	m_eID;					// ������ �������̶�� ���� �����ִ°�?
	int				m_iType;				// ����� Ÿ���� � ���ΰ�?
	TCHAR			m_szName[FULL_STRING];	// ������ �̸�
	int				m_iImgCode;				// ����� �̹����� ���ϴ� ����
	int				m_iItemCode;
	bool			m_bSelect;				// ��Ŭ������ ���� ���������� üũ�ϴ� ����
	bool			m_bCursorOn;			// Ŀ���� ���� �ִ��� Ȯ���ϴ� ����

	int				m_iBP;					// �ش� ��� ������ �ִ� ȿ��
	int				m_iAtk;					// �ش� ��� ������ �ִ� ȿ��
	int				m_iDef;					// �ش� ��� ������ �ִ� ȿ��
	int				m_iSpd;					// �ش� ��� ������ �ִ� ȿ��
	int				m_iMag;					// �ش� ��� ������ �ִ� ȿ��
	int				m_iCri;					// �ش� ��� ������ �ִ� ȿ��

public: // protected -> public.. �˼��մϴ� ���� �Ⱥ������
	explicit CItem(eObjectType _eObjectType);

public:
	virtual ~CItem(void);
};

END_NAMESPACE

#endif // Item_h__