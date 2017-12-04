/*!
 * \file SmartText.h
 * \date 2016/06/09 17:04
 *
 * \author 박정민
 * Contact: user@company.com
 *
 * \brief 스크린 좌표계 사용!
 *
 * TODO: long description
 *
 * \note
*/

#ifndef SmartText_h__
#define SmartText_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CSmartText
{
	// member variable
public:
	TCHAR m_szContent[FULL_STRING];
private:
	D3DXVECTOR2 m_vPos;
	RECT m_rcBox;

	// member function
public:
	void Draw(DWORD _dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void TalkboxDraw(DWORD _dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));

	// getter & setter
public:
	void SetPos(float _fX, float _fY);

	// constructor & destructor
public:
	explicit CSmartText(void);
	explicit CSmartText(TCHAR* _szText, float _fX = 0.f, float _fY = 0.f);
	~CSmartText(void);
	//MAKE_UNCOPYABLE(CSmartText)
};
typedef CSmartText SMART_TEXT;
END_NAMESPACE

#endif // SmartText_h__