/*!
 * \file CharacterPage.h
 * \date 2016/06/04 23:11
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

#ifndef CharacterPage_h__
#define CharacterPage_h__

#include "Page.h"

BEGIN_NAMESPACE(ENGINE)

class CSubPageObserver;
class ENGINE_DLL_SPECIFIER CCharacterPage : public CPage
{
protected:
	CSubPageObserver*	m_pSubObserver;

public:
	virtual int		Update(void);
	virtual void	Render(void);

private:
	void Release(void);

protected:
	explicit CCharacterPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CCharacterPage(void);
};

END_NAMESPACE

#endif // CharacterPage_h__