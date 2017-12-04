/*!
 * \file CharacterEquipPage.h
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
	TCHAR	szEquip[FULL_STRING];
	int		eNowCheakType;
	int		eEquipCheak;
	int		m_iCode;
	int		iContinue;

	int		iX; // 인벤토리에 있는 마지막 아이템의 가로값 (스크롤 미적용)
	int		iY; // 인벤토리에 있는 마지막 아이템의 세로값 (스크롤 미적용)

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