/*!
 * \file Navi.h
 * \date 2016/06/13 20:11
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

#ifndef Navi_h__
#define Navi_h__

#include "Client_Include.h"
#include "GameObject.h"

namespace ENGINE
{
	class CGroupObserver;
}

class CNavi : public ENGINE::CGameObject
{
	enum eGoal {GOAL_START, GOAL_1, GOAL_2, GOAL_3, GOAL_END};
private:
	float		m_fAngle;
	TEXINFO*	m_pNavi;
	TEXINFO*	m_pNaviDir;
	TEXINFO*	m_pMessage;

private:
	ENGINE::CGroupObserver* m_pGroupObserver;

private:
	bool			m_bHighAngle;
	bool			m_bArr;
	D3DXVECTOR3		m_vGoal1;
	D3DXVECTOR3		m_vGoal2;
	D3DXVECTOR3		m_vGoal3;
	D3DXVECTOR3		m_vTagPos;
	int				iGoalNow;
	bool			m_bKeyInput;

public:
	static CNavi* Create(eObjectType _eObjectType);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);

public:
	virtual int Update(void);
	virtual void Render(void);
	virtual	void KeyCheak(void);
	virtual float AngleCheak(void);
	virtual void TextOut(D3DXMATRIX matWorld);

private:
	explicit CNavi(eObjectType _eObjectType);

public:
	virtual ~CNavi(void);

	

};

#endif // Navi_h__