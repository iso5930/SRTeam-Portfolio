/*!
 * \file DiaryPage.h
 * \date 2016/06/04 23:30
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

#ifndef DiaryPage_h__
#define DiaryPage_h__

#include "Page.h"

BEGIN_NAMESPACE(ENGINE)
	
class ENGINE_DLL_SPECIFIER CDiaryPage : public CPage
{
public:
	virtual int		Update(void);
	virtual void	Render(void);

protected:
	explicit CDiaryPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CDiaryPage(void);
};

END_NAMESPACE

#endif // DiaryPage_h__