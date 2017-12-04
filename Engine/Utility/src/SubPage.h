/*!
 * \file SubPage.h
 * \date 2016/06/04 23:42
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

#ifndef SubPage_h__
#define SubPage_h__

#include "Page.h"

BEGIN_NAMESPACE(ENGINE)

class CMainUIObserver;
class CGroupObserver;
class CButton;

class ENGINE_DLL_SPECIFIER CSubPage : public CPage
{
private:
	vector<eCharacterID>	m_vecCharID;
	int						m_iCharCur;
	eCharacterID			m_eCharCur;
	int						m_iMainUICur;
	CMainUIObserver*		m_pObserver;
	CGroupObserver*			m_pCharObserver;
	vector<CButton*>		m_vecButton;
	bool					m_bMessageBox;
	D3DXVECTOR3				m_vMessagePos;

	
public:
	static CSubPage* Create(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

private:
	HRESULT Init(void);
	void	Release(void);

private:
	void CharUpdate(void);
	void DiaryUpdate(void);
	void CharRender(void);
	void DiaryRender(void);

public:
	virtual int Update(void);
	virtual void Render(void);

private:
	explicit CSubPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite);

public:
	virtual ~CSubPage(void);
	
};

END_NAMESPACE
#endif // SubPage_h__