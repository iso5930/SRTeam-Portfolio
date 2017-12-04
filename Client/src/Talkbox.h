/*!
 * \file Talkbox.h
 * \date 2016/06/22 16:07
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Talkbox_h__
#define Talkbox_h__

#include "Client_Include.h"
#include "GameObject.h"
#include "SmartText.h"

class CPlaneObject;
class CTalkbox : public ENGINE::CGameObject
{
	// member variable
private:
	CPlaneObject* m_pTalkbox;
	CPlaneObject* m_pTalkersFace;

	ENGINE::SMART_TEXT m_Text;

	bool m_bDraw;

	// member function
public:
	static CTalkbox* Create(eObjectType _eObjectType, ENGINE::SMART_TEXT& _pText, CPlaneObject* _pTalkbox, CPlaneObject* _pTalkersFace = NULL);
	virtual int Update(void);
	virtual void Render(void);
private:
	virtual HRESULT Initialize(void) { return S_OK; }
	HRESULT Initialize(ENGINE::SMART_TEXT& _pText, CPlaneObject* _pTalkbox, CPlaneObject* _pTalkersFace = NULL);
	HRESULT AddComponent(void);
	virtual void Release(void);

	// getter & setter
public:
	void SetDraw(bool _b)
	{
		m_bDraw = _b;
	}

	// constructor & destructor
private:
	explicit CTalkbox(eObjectType _eObjectType);
public:
	~CTalkbox(void);
	MAKE_UNCOPYABLE(CTalkbox)
};

#endif // Talkbox_h__