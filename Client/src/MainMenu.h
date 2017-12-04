/*!
 * \file MainMenu.h
 * \date 2016/06/05 4:01
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

#ifndef MainMenu_h__
#define MainMenu_h__

#include "Client_Include.h"
#include "GameObject.h"

namespace ENGINE
{
	class CPage;
	class CButton;
	class CCharacterGroup; // Test
	class CSubPageObserver;
}

class CMainMenu : public ENGINE::CGameObject
{
private:
	LPD3DXSPRITE				m_pSprite;
	bool						m_bUISwitch;
	ENGINE::CSubPageObserver*	m_pSubObserver;
	
private:
	//test
	ENGINE::CCharacterGroup* m_pGroup;
	
private:
	vector<ENGINE::CPage*>	m_vecPage[MENU_END];
	ENGINE::CPage*			m_pSubPage;
	int						m_iTopMenuIndex;
	int						m_iLeftMenuIndex;

private:
	vector<ENGINE::CButton*>	m_vecLeftButton;
	vector<ENGINE::CButton*>	m_vecTopButton;
	
public:
	static CMainMenu* Create(eObjectType _eObjectType);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);

public:
	virtual int	 Update(void);
	virtual void Render(void);

public:
	bool	GetUISwitch(void);

private:
	explicit CMainMenu(eObjectType _eObjectType);

public:
	virtual ~CMainMenu(void);
};

#endif // MainMenu_h__