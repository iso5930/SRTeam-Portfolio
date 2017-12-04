/*!
 * \file CharacterItemPage.h
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

#ifndef CharacterItemPage_h__
#define CharacterItemPage_h__

#include "CharacterPage.h"

BEGIN_NAMESPACE(ENGINE)

class CGroupObserver;
class CItem;
class CInventory;

class ENGINE_DLL_SPECIFIER CCharacterItemPage : public CCharacterPage
{
	enum {ITEM_START, ITEM_TEST, ITEM_END};
	enum {SCROLL_START, SCROLL_PLUS, SCROLL_MINU, SCROLL_DRAG};

private:
	CGroupObserver* m_pGroupObserver;

public:
	static CCharacterItemPage* Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

private:
	HRESULT Init(void);
	void	Release(void);

public:
	virtual int Update(void);
	virtual void Render(void);

private:
	LPD3DXFONT m_pD3DXFont;
	TCHAR m_szText[FULL_STRING];

private:
	eCharacterID eCharID;

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

	float	m_fPlus;

	int		iX; // �κ��丮�� �ִ� ������ �������� ���ΰ� (��ũ�� ������)
	int		iY; // �κ��丮�� �ִ� ������ �������� ���ΰ� (��ũ�� ������)
	int		iYBackUp;

	bool	m_bMessage;
	float	fMouseX;
	float	fMouseY;

	bool	bButton;
	int		m_iSelectMouse;

private:
	CInventory*				m_pInven;

	vector<CItem*>*			vecInven;
	typedef vector<CItem*>*	VECINVEN;

private:
	explicit CCharacterItemPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CCharacterItemPage(void);

};

END_NAMESPACE


#endif // CharacterItemPage_h__