/*!
 * \file CharacterMagicPage.h
 * \date 2016/06/04 23:27
 *
 * \author ÀÌÁøÇü
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef CharacterMagicPage_h__
#define CharacterMagicPage_h__

#include "CharacterPage.h"

BEGIN_NAMESPACE(ENGINE)

class CGroupObserver;

class ENGINE_DLL_SPECIFIER CCharacterMagicPage : public CCharacterPage
{
private:
	CGroupObserver* m_pGroupObserver;
	int				m_iScrollY;

public:
	static CCharacterMagicPage* Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

private:
	HRESULT Init(void);
	void	Release(void);

public:
	virtual int Update(void);
	virtual void Render(void);

private:
	explicit CCharacterMagicPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CCharacterMagicPage(void);
};

END_NAMESPACE

#endif // CharacterMagicPage_h__