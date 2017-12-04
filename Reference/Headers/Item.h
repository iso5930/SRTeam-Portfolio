/*!
 * \file Item.h
 * \date 2016/06/06 14:42
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
	int				m_iNum;					// 몇개를 가지고 있는가?
	bool			m_bFree;				// 착용 가능한가?
	eCharacterID	m_eID;					// 누군가 착용중이라면 누가 갖고있는가?
	int				m_iType;				// 장비의 타입은 어떤 것인가?
	TCHAR			m_szName[FULL_STRING];	// 아이템 이름
	int				m_iImgCode;				// 출력할 이미지를 정하는 변수
	int				m_iItemCode;
	bool			m_bSelect;				// 좌클릭으로 현제 선택중인지 체크하는 변수
	bool			m_bCursorOn;			// 커서가 위에 있는지 확인하는 변수

	int				m_iBP;					// 해당 장비가 가지고 있는 효과
	int				m_iAtk;					// 해당 장비가 가지고 있는 효과
	int				m_iDef;					// 해당 장비가 가지고 있는 효과
	int				m_iSpd;					// 해당 장비가 가지고 있는 효과
	int				m_iMag;					// 해당 장비가 가지고 있는 효과
	int				m_iCri;					// 해당 장비가 가지고 있는 효과

public: // protected -> public.. 죄송합니다 답이 안보였어요
	explicit CItem(eObjectType _eObjectType);

public:
	virtual ~CItem(void);
};

END_NAMESPACE

#endif // Item_h__