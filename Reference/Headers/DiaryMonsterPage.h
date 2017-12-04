/*!
 * \file DiaryMonsterPage.h
 * \date 2016/06/04 23:35
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

#ifndef DiaryMonsterPage_h__
#define DiaryMonsterPage_h__

#include "DiaryPage.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CDiaryMonsterPage : public CDiaryPage
{
public:
	static CDiaryMonsterPage* Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

private:
	HRESULT Init(void);
	void	Release(void);

public:
	virtual int Update(void);
	virtual void Render(void);

private:
	explicit CDiaryMonsterPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CDiaryMonsterPage(void);
};

END_NAMESPACE

#endif // DiaryMonsterPage_h__