/*!
 * \file Button.h
 * \date 2016/06/05 3:49
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

#ifndef Button_h__
#define Button_h__

#include "Engine_Include.h"
#include "Component.h"

BEGIN_NAMESPACE(ENGINE)

class CMainUIObserver;
class CSubPageObserver;

class ENGINE_DLL_SPECIFIER CButton : public CComponent
{
private:
	eButtonType			m_eButtonType;
	RECT				m_rcButton;
	POINT				m_ptMouse;
	float				m_fX;
	float				m_fY;
	CMainUIObserver*	m_pObserver;
	CSubPageObserver*	m_pSubObserver;

public:
	static CButton* Create(ENGINE::CGameObject* _pOwner, const D3DXVECTOR3& _vPos, const float& _fCX, const float& _fCY, eButtonType _eType = BUTTON_END);
	
public:
	void SetMousePos(POINT _ptMouse);

private:
	HRESULT Init(const D3DXVECTOR3& _vPos, const float& _fCX, const float& _fCY, eButtonType _eType = BUTTON_END);
	void Release(void);
	void DrawFont(char* _pName, float _fX, float _fY, float _fIntervalX, float _fIntervalY);

public:
	virtual int Update(void);
	virtual void Render(void);

public:
	RECT* GetButton(void);

private:
	explicit CButton(ENGINE::CGameObject* _pOwner);

public:
	virtual ~CButton(void);
};

END_NAMESPACE

#endif // Button_h__