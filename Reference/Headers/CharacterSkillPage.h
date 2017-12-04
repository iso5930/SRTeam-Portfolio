/*!
 * \file CharacterSkillPage.h
 * \date 2016/06/04 23:26
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

#ifndef CharacterSkillPage_h__
#define CharacterSkillPage_h__

#include "CharacterPage.h"

BEGIN_NAMESPACE(ENGINE)

class CGroupObserver;

class ENGINE_DLL_SPECIFIER CCharacterSkillPage : public CCharacterPage
{
private:
	CGroupObserver*	m_pGroupObserver;
	int				m_iScrollY;

public:
	static CCharacterSkillPage* Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

private:
	HRESULT Init(void);
	void	Release(void);

public:
	virtual int Update(void);
	virtual void Render(void);

private:
	explicit CCharacterSkillPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CCharacterSkillPage(void);
};

END_NAMESPACE

#endif // CharacterSkillPage_h__