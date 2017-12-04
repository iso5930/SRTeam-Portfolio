/*!
 * \file DiaryScrapPage.h
 * \date 2016/06/04 23:37
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
#ifndef DiaryScrapPage_h__
#define DiaryScrapPage_h__

#include "DiaryPage.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CDiaryScrapPage : public CDiaryPage
{
public:
	static CDiaryScrapPage* Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

private:
	HRESULT Init(void);
	void	Release(void);

public:
	virtual int Update(void);
	virtual void Render(void);

private:
	explicit CDiaryScrapPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CDiaryScrapPage(void);
};

END_NAMESPACE

#endif // DiaryScrapPage_h__