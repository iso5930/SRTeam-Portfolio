/*!
 * \file PlaneObject.h
 * \date 2016/06/17 0:27
 *
 * \author 박정민
 * Contact: user@company.com
 *
 * \brief 스프라이트 쓴다
 *
 * TODO: long description
 *
 * \note
*/

#ifndef PlaneObject_h__
#define PlaneObject_h__

#include "Client_Include.h"
#include "GameObject.h"

class CPlaneObject : public ENGINE::CGameObject
{
	// member variable
private:
	wstring m_strTextureKey;
	float m_fX;
	float m_fY;
	DWORD m_Color;
	bool m_bDraw;

	// member function
public:
	static CPlaneObject* Create(eObjectType _eObjectType, const wstring& _strTextureKey, bool _bDraw);
	virtual int Update(void);
	virtual void Render(void);
private:
	virtual HRESULT Initialize(void);
	HRESULT AddComponent(void);
	virtual void Release(void);

	// getter & setter
public:
	void SetTextureKey(const wstring& _strTextureKey);
	void SetPos(float _fX, float _fY)
	{
		m_fX = _fX;
		m_fY = _fY;
	}
	void SetColor(DWORD _Color)
	{
		m_Color = _Color;
	}
	void SetDraw(bool _b)
	{
		m_bDraw = _b;
	}

	// constructor & destructor
private:
	explicit CPlaneObject(eObjectType _eObjectType, bool _bDraw);
public:
	~CPlaneObject(void);
	MAKE_UNCOPYABLE(CPlaneObject)
};

#endif // PlaneObject_h__