/*!
 * \file CharacterEquipPage.h
 * \date 2016/06/04 23:21
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
#ifndef CharacterEquipPage_h__
#define CharacterEquipPage_h__

#include "CharacterPage.h"

BEGIN_NAMESPACE(ENGINE)

class CGroupObserver;
class CItem;
class CEquip;

class ENGINE_DLL_SPECIFIER CCharacterEquipPage : public CCharacterPage
{
	enum {SCROLL_START, SCROLL_PLUS, SCROLL_MINU, SCROLL_DRAG};
private:
	CGroupObserver* m_pGroupObserver;

public:
	static CCharacterEquipPage* Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

private:
	HRESULT Init(void);
	void	Release(void);

private:
	eCharacterID			eCharID;
	CHARACTER_STATE			m_tTempState;

	int		m_iItem; // ������ �ִ� �������� ������ ����
	float	m_fScroll; // ��ũ�Ѱ�
	float	m_fScrollOut;
	bool	m_bScrollOut;
	float	m_fScrollClo; // ��ũ���� ��ġ�� �˾Ƴ��� ���� ����

	bool	m_bUpScrollNow;
	bool	m_bDownScrollNow;
	bool	m_bMoveScrollNow; // �Է¿� ���� ��ũ�� �ؽ��� ��ȯ

	bool	m_bKeyInput;
	int		m_iKeyInput;
	TCHAR	szEquip[FULL_STRING];
	int		eNowCheakType;
	int		eEquipCheak;
	int		m_iCode;
	int		iContinue;

	int		iX; // �κ��丮�� �ִ� ������ �������� ���ΰ� (��ũ�� ������)
	int		iY; // �κ��丮�� �ִ� ������ �������� ���ΰ� (��ũ�� ������)

	CEquip*	m_pEquip;

private:
	vector<CItem*>*			vecEquip;
	typedef vector<CItem*>*	VECEQUIP;

public:
	virtual int Update(void);
	virtual void Render(void);

public:
	bool	EquipCheak(int eEquip, int iImgCode, int iItemCode, eCharacterID eCharID);
	int		ImgCheak(int eEquip, eCharacterID eCharID);

private:
	explicit CCharacterEquipPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CCharacterEquipPage(void);

};

END_NAMESPACE

#endif // CharacterEquipPage_h__