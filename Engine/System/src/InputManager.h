/*!
 * \file InputManager.h
 * \date 2016/06/09 20:44
 *
 * \author 박정민
 * Contact: user@company.com
 *
 * \brief
 *
 * TODO: long description
 *
 * \note
 //! 마우스 휠 이벤트 처리 없고, 아직 없는 키할당..
*/

#ifndef InputManager_h__
#define InputManager_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class CCollisionFunctor;
class ENGINE_DLL_SPECIFIER CInputManager
{
	DECLARE_SINGLETON(CInputManager)

	// member variable
private:
	KEY_STATE m_tOldKey;
	KEY_STATE m_tCurrentKey;

	POINT m_ptMouse;

	bool m_bOnEvent;

	bool m_bDrawBoundingBox;

	// member function
public:
	void SetKeyState(HWND _hWnd, bool _bKeyDisable);

	bool IsKeyDown(const KEY_STATE& _tKeyState);
	bool IsKeyUpNow(const KEY_STATE& _tKeyState);
	bool IsKeyDownNow(const KEY_STATE& _tKeyState);

	bool IsEventProgressKeyDownNow(void);

	// getter & setter
public:
	void GetMousePos(POINT* _ptOut);
	void GetMousePos(D3DXVECTOR3* _vOut);

	void SetOnEvent(bool _b)
	{
		m_bOnEvent = _b;
	}
	bool GetOnEvent(void)
	{
		return m_bOnEvent;
	}
	bool IsDrawBoundingBox(void)
	{
		return m_bDrawBoundingBox;
	}
	void SetDrawBoundingBox(void)
	{
		m_bDrawBoundingBox = !m_bDrawBoundingBox;
	}

	// constructor & destructor
private:
	explicit CInputManager(void);
	~CInputManager(void);
};
END_NAMESPACE

#endif // InputManager_h__