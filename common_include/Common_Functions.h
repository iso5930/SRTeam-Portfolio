/*!
 * \file Common_Functions.h
 * \date 2016/05/24 19:37
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 ������ ��������, �ϴ� inline���� ���� �͵��� ��������,
 �ƴ� �͵��� utility Ŭ������ static ����� �α��..
 inline ���� �͵��� h�� ���� �����ϸ� ��ũ�� ������ �������⼭ �ջ��ϱ� ����.

 //! ���̹� ������ �߿��� �� ������..
 ����ν� CCommonUtility Ŭ������ �̸��� typedef�� �ִ��� �ٿ����� �͹ۿ� ������ �ȳ�..
*/

#ifndef Common_Functions_h__
#define Common_Functions_h__

// ���� ��ü ���� ����
template <typename T>
inline void SAFE_DELETE(T& _pObject)
{
	delete _pObject;
	_pObject = NULL;
}

// ��ü �迭 ���� ����
template <typename T>
inline void SAFE_DELETE_ARRAY(T& _pObject)
{
	delete[] _pObject;
	_pObject = NULL;
}

// ���� ����Ʈ ��ü ���� ����
template <typename T>
inline void SAFE_RELEASE(T& _pObject)
{
	if (_pObject)
	{
		_pObject->Release();
		_pObject = NULL;
	}
}

// �޼��� �ڽ� ǥ��
inline void MSGBOX(TCHAR* _szMessage)
{
	MessageBox(NULL, _szMessage, L"System Message", MB_OK);
}

// ���� �޸� �޼��� �ڽ� ǥ��
inline void MSGBOX_CAPTIONED(TCHAR* _szMessage, TCHAR* _szCaption)
{
	MessageBox(NULL, _szMessage, _szCaption, MB_OK);
}

// ���� ä��� �ζ��� �Լ�
inline void SetD3DXVector3(D3DXVECTOR3* _pVec, float _fX, float _fY, float _fZ)
{
	_pVec->x = _fX;
	_pVec->y = _fY;
	_pVec->z = _fZ;
}

inline void SetD3DXVector2(D3DXVECTOR2* _pVec, float _fX, float _fY)
{
	_pVec->x = _fX;
	_pVec->y = _fY;
}


class CCommonUtility
{
	// member variable
private:
	// -

	// member function
public:
	// �̳༮�� �ƹ����� ���⺸�ٴ�,
	// API �Լ� �Ʒ����̳�, �׿� ���� ������ �߻��� '���� ����� ��ġ'�� �Ŵ� �� ������ ����..
	// __asm���� break point ������ ���ܰ� �� ��ġ�� �ٷ� �ߴ����� �߶�� �ǹ̵� �ְ�,
	// �Լ� Ÿ�� �ö󰡸� �Ź� �ߴ��� �ɷ�����
	// ���� ���� �߻� ��ġ �ƴϸ� �ǹ� ���� �ʳ�? �;.. ������ ȣ�� �������� �̹� �� ���ٵ�.
	//! release ����� ���� �� �༮ ������ ������ ������ ������?
	static void SHOW_ERROR(HRESULT _hr, TCHAR* _szMessage)
	{
		static TCHAR szBuffer[2][FULL_STRING] = {0};

		lstrcpy(szBuffer[0], _szMessage);
		wsprintf(szBuffer[1], L"\n\nError Caution : %d", _hr);
		lstrcat(szBuffer[0], szBuffer[1]);
		MessageBox(NULL, szBuffer[0], NULL, MB_OK);

		// make breakpoint
		__asm
		{
			int 3
		};
	}

	static void SHOW_ERROR(const TCHAR* _szCaution, TCHAR* _szMessage)
	{
		static TCHAR szBuffer[FULL_STRING] = {0};

		lstrcpy(szBuffer, _szMessage);
		lstrcat(szBuffer, L"\n\nError Caution : ");
		lstrcat(szBuffer, _szCaution);
		MessageBox(NULL, szBuffer, NULL, MB_OK);

		// make breakpoint
		__asm
		{
			int 3
		};
	}

	// constructor & destructor
private:
	explicit CCommonUtility(void);
	~CCommonUtility(void);
	CCommonUtility(CCommonUtility& _Other);
	CCommonUtility& operator =(CCommonUtility& _Other);
};
typedef CCommonUtility UTIL;

#endif // Common_Functions_h__