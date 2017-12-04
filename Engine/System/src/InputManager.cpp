#include "InputManager.h"

IMPLEMENT_SINGLETON(ENGINE::CInputManager)

ENGINE::CInputManager::CInputManager(void)
:m_bOnEvent(false)
,m_bDrawBoundingBox(false)
{
	memset(&m_ptMouse, 0, sizeof(POINT));
}

ENGINE::CInputManager::~CInputManager(void)
{

}

void ENGINE::CInputManager::SetKeyState(HWND _hWnd, bool _bKeyDisable)
{
	if (_bKeyDisable)
		return;

	// mouse pos
	GetCursorPos(&m_ptMouse);
	ScreenToClient(_hWnd, &m_ptMouse);

	// keyboard
	memcpy(&m_tOldKey, &m_tCurrentKey, sizeof(KEY_STATE));
	memset(&m_tCurrentKey, 0, sizeof(KEY_STATE));

	if (GetAsyncKeyState(VK_UP))
		m_tCurrentKey |= KEY_STATE_UP;

	if (!m_bOnEvent)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
			m_tCurrentKey |= KEY_STATE_LBUTTON;
		if (GetAsyncKeyState(VK_RETURN))
			m_tCurrentKey |= KEY_STATE_RETURN;
		if (GetAsyncKeyState(VK_ESCAPE))
			m_tCurrentKey |= KEY_STATE_ESCAPE;

		if (GetAsyncKeyState(VK_RBUTTON))
			m_tCurrentKey |= KEY_STATE_RBUTTON;

		
		if (GetAsyncKeyState(VK_DOWN))
			m_tCurrentKey |= KEY_STATE_DOWN;
		if (GetAsyncKeyState(VK_LEFT))
			m_tCurrentKey |= KEY_STATE_LEFT;
		if (GetAsyncKeyState(VK_RIGHT))
			m_tCurrentKey |= KEY_STATE_RIGHT;

		if (GetAsyncKeyState(VK_F1))
			m_tCurrentKey |= KEY_STATE_F1;
		if (GetAsyncKeyState(VK_F2))
			m_tCurrentKey |= KEY_STATE_F2;
		if (GetAsyncKeyState(VK_F3))
			m_tCurrentKey |= KEY_STATE_F3;
		if (GetAsyncKeyState(VK_F4))
			m_tCurrentKey |= KEY_STATE_F4;
		if (GetAsyncKeyState(VK_F5))
			m_tCurrentKey |= KEY_STATE_F5;
		if (GetAsyncKeyState(VK_F6))
			m_tCurrentKey |= KEY_STATE_F6;
		if (GetAsyncKeyState(VK_F7))
			m_tCurrentKey |= KEY_STATE_F7;
		if (GetAsyncKeyState(VK_F8))
			m_tCurrentKey |= KEY_STATE_F8;
		if (GetAsyncKeyState(VK_F9))
			m_tCurrentKey |= KEY_STATE_F9;
		if (GetAsyncKeyState(VK_F10))
			m_tCurrentKey |= KEY_STATE_F10;
		if (GetAsyncKeyState(VK_F11))
			m_tCurrentKey |= KEY_STATE_F11;
		if (GetAsyncKeyState(VK_F12))
			m_tCurrentKey |= KEY_STATE_F12;

		if (GetAsyncKeyState('1'))
			m_tCurrentKey |= KEY_STATE_1;
		if (GetAsyncKeyState('2'))
			m_tCurrentKey |= KEY_STATE_2;
		if (GetAsyncKeyState('3'))
			m_tCurrentKey |= KEY_STATE_3;
		if (GetAsyncKeyState('4'))
			m_tCurrentKey |= KEY_STATE_4;
		if (GetAsyncKeyState('5'))
			m_tCurrentKey |= KEY_STATE_5;
		if (GetAsyncKeyState('6'))
			m_tCurrentKey |= KEY_STATE_6;
		if (GetAsyncKeyState('7'))
			m_tCurrentKey |= KEY_STATE_7;
		if (GetAsyncKeyState('8'))
			m_tCurrentKey |= KEY_STATE_8;
		if (GetAsyncKeyState('9'))
			m_tCurrentKey |= KEY_STATE_9;
		if (GetAsyncKeyState('0'))
			m_tCurrentKey |= KEY_STATE_0;

		if (GetAsyncKeyState('Q'))
			m_tCurrentKey |= KEY_STATE_Q;
		if (GetAsyncKeyState('W'))
			m_tCurrentKey |= KEY_STATE_W;
		if (GetAsyncKeyState('E'))
			m_tCurrentKey |= KEY_STATE_E;
		if (GetAsyncKeyState('R'))
			m_tCurrentKey |= KEY_STATE_R;
		if (GetAsyncKeyState('T'))
			m_tCurrentKey |= KEY_STATE_T;
		if (GetAsyncKeyState('Y'))
			m_tCurrentKey |= KEY_STATE_Y;
		if (GetAsyncKeyState('U'))
			m_tCurrentKey |= KEY_STATE_U;
		if (GetAsyncKeyState('I'))
			m_tCurrentKey |= KEY_STATE_I;
		if (GetAsyncKeyState('O'))
			m_tCurrentKey |= KEY_STATE_O;
		if (GetAsyncKeyState('P'))
			m_tCurrentKey |= KEY_STATE_P;
		if (GetAsyncKeyState('A'))
			m_tCurrentKey |= KEY_STATE_A;
		if (GetAsyncKeyState('S'))
			m_tCurrentKey |= KEY_STATE_S;
		if (GetAsyncKeyState('D'))
			m_tCurrentKey |= KEY_STATE_D;
		if (GetAsyncKeyState('F'))
			m_tCurrentKey |= KEY_STATE_F;
		if (GetAsyncKeyState('G'))
			m_tCurrentKey |= KEY_STATE_G;
		if (GetAsyncKeyState('H'))
			m_tCurrentKey |= KEY_STATE_H;
		if (GetAsyncKeyState('J'))
			m_tCurrentKey |= KEY_STATE_J;
		if (GetAsyncKeyState('K'))
			m_tCurrentKey |= KEY_STATE_K;
		if (GetAsyncKeyState('L'))
			m_tCurrentKey |= KEY_STATE_L;
		if (GetAsyncKeyState('Z'))
			m_tCurrentKey |= KEY_STATE_Z;
		if (GetAsyncKeyState('X'))
			m_tCurrentKey |= KEY_STATE_X;
		if (GetAsyncKeyState('C'))
			m_tCurrentKey |= KEY_STATE_C;
		if (GetAsyncKeyState('V'))
			m_tCurrentKey |= KEY_STATE_V;
		if (GetAsyncKeyState('B'))
			m_tCurrentKey |= KEY_STATE_B;
		if (GetAsyncKeyState('N'))
			m_tCurrentKey |= KEY_STATE_N;
		if (GetAsyncKeyState('M'))
			m_tCurrentKey |= KEY_STATE_M;

		if (GetAsyncKeyState(VK_SPACE))
			m_tCurrentKey |= KEY_STATE_SPACE;
		if (GetAsyncKeyState(VK_MENU))
			m_tCurrentKey |= KEY_STATE_LALT;
		if (GetAsyncKeyState(VK_CONTROL))
			m_tCurrentKey |= KEY_STATE_LCTRL;
		if (GetAsyncKeyState(VK_LSHIFT))
			m_tCurrentKey |= KEY_STATE_LSHIFT;
	}
}

// 키가 눌려있는지만 체크..
bool ENGINE::CInputManager::IsKeyDown(const KEY_STATE& _tKeyState)
{
	if ((m_tCurrentKey & _tKeyState) == KEY_STATE_NO)
		return false;
	else
		return true;
}

// 키를 막 뗐는지 체크
bool ENGINE::CInputManager::IsKeyUpNow(const KEY_STATE& _tKeyState)
{
	if (((m_tOldKey & _tKeyState) != KEY_STATE_NO) && ((m_tCurrentKey & _tKeyState) == KEY_STATE_NO))
		return true;

	return false;
}

// 키를 막 눌렀는지 체크
bool ENGINE::CInputManager::IsKeyDownNow(const KEY_STATE& _tKeyState)
{
	if (((m_tOldKey & _tKeyState) == KEY_STATE_NO) && ((m_tCurrentKey & _tKeyState) != KEY_STATE_NO))
		return true;

	return false;
}

void ENGINE::CInputManager::GetMousePos(POINT* _ptOut)
{
	memcpy(_ptOut, &m_ptMouse, sizeof(POINT));
}

void ENGINE::CInputManager::GetMousePos(D3DXVECTOR3* _vOut)
{
	SetD3DXVector3(_vOut, (float)m_ptMouse.x, (float)m_ptMouse.y, 0.f);
}

bool ENGINE::CInputManager::IsEventProgressKeyDownNow(void)
{
	KEY_STATE _tKeyState = KEY_STATE_UP;
	if (((m_tOldKey & _tKeyState) == KEY_STATE_NO) && ((m_tCurrentKey & _tKeyState) != KEY_STATE_NO))
		return true;

	return false;
}
