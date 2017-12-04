/*!
 * \file Common_Functions.h
 * \date 2016/05/24 19:37
 *
 * \author 박정민
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 복잡해 보이지만, 일단 inline으로 만들 것들은 전역으로,
 아닌 것들은 utility 클래스의 static 멤버로 두기로..
 inline 안할 것들을 h에 몸통 정의하면 링크때 에러가 여기저기서 뿜뿜하기 때문.

 //! 네이밍 관리가 중요할 것 같은데..
 현재로썬 CCommonUtility 클래스의 이름을 typedef로 최대한 줄여보는 것밖에 생각이 안남..
*/

#ifndef Common_Functions_h__
#define Common_Functions_h__

// 단일 객체 안전 해제
template <typename T>
inline void SAFE_DELETE(T& _pObject)
{
	delete _pObject;
	_pObject = NULL;
}

// 객체 배열 안전 해제
template <typename T>
inline void SAFE_DELETE_ARRAY(T& _pObject)
{
	delete[] _pObject;
	_pObject = NULL;
}

// 단일 스마트 객체 안전 해제
template <typename T>
inline void SAFE_RELEASE(T& _pObject)
{
	if (_pObject)
	{
		_pObject->Release();
		_pObject = NULL;
	}
}

// 메세지 박스 표시
inline void MSGBOX(TCHAR* _szMessage)
{
	MessageBox(NULL, _szMessage, L"System Message", MB_OK);
}

// 제목 달린 메세지 박스 표시
inline void MSGBOX_CAPTIONED(TCHAR* _szMessage, TCHAR* _szCaption)
{
	MessageBox(NULL, _szMessage, _szCaption, MB_OK);
}

// 벡터 채우는 인라인 함수
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
	// 이녀석은 아무때나 쓰기보다는,
	// API 함수 아래쪽이나, 그와 같이 에러가 발생한 '가장 깊숙한 위치'에 거는 게 좋을것 같다..
	// __asm으로 break point 걸은게 예외가 난 위치에 바로 중단점이 뜨라는 의미도 있고,
	// 함수 타고 올라가며 매번 중단점 걸려봐야
	// 실제 예외 발생 위치 아니면 의미 없지 않나? 싶어서.. 어차피 호출 스택으로 이미 다 볼텐데.
	//! release 모드일 때는 이 녀석 때문에 문제가 생기지 않을까?
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