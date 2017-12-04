/*!
 * \file TacticsPage.h
 * \date 2016/06/04 23:39
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

#ifndef TacticsPage_h__
#define TacticsPage_h__

#include "Page.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CTacticsPage : public CPage
{
public:
	static CTacticsPage* Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

private:
	HRESULT Init(void);
	void	Release(void);

public:
	virtual int		Update(void);
	virtual void	Render(void);

protected:
	explicit CTacticsPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CTacticsPage(void);
};

END_NAMESPACE


#endif // TacticsPage_h__