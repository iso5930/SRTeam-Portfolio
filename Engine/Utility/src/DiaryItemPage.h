/*!
 * \file DiaryItemPage.h
 * \date 2016/06/04 23:33
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

#ifndef DiaryItemPage_h__
#define DiaryItemPage_h__

#include "DiaryPage.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CDiaryItemPage : public CDiaryPage
{
public:
	static CDiaryItemPage* Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

private:
	HRESULT Init(void);
	void	Release(void);

public:
	virtual int Update(void);
	virtual void Render(void);

private:
	explicit CDiaryItemPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CDiaryItemPage(void);
};

END_NAMESPACE

#endif // DiaryItemPage_h__