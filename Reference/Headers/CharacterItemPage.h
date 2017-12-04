/*!
 * \file CharacterItemPage.h
 * \date 2016/06/04 23:21
 *
 * \author 이진형
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

	int		m_iItem; // 가지고 있는 아이템의 종류별 갯수
	float	m_fScroll; // 스크롤값
	float	m_fScrollOut;
	bool	m_bScrollOut;
	float	m_fScrollClo; // 스크롤의 위치를 알아내기 위한 값들

	bool	m_bUpScrollNow;
	bool	m_bDownScrollNow;
	bool	m_bMoveScrollNow; // 입력에 따라 스크롤 텍스쳐 변환

	bool	m_bKeyInput;
	int		m_iKeyInput;

	float	m_fPlus;

	int		iX; // 인벤토리에 있는 마지막 아이템의 가로값 (스크롤 미적용)
	int		iY; // 인벤토리에 있는 마지막 아이템의 세로값 (스크롤 미적용)
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