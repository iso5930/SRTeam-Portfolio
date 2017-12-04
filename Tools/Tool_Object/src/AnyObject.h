/*!
 * \file AnyObject.h
 * \date 2016/06/14 5:46
 *
 * \author ¹ÚÁ¤¹Î
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef AnyObject_h__
#define AnyObject_h__

#include "Tools_Include.h"
#include "GameObject.h"

namespace ENGINE
{
	class CTransform;
	class CVIBuffer;
	class CTexture;
}
class CAnyObject : public ENGINE::CGameObject
{
	// member variable
private:
	ENGINE::CTransform* m_pInfo;
	ENGINE::CVIBuffer* m_pBuffer;
	ENGINE::CTexture* m_pTexture;

	// member function
public:
	static CAnyObject* Create(eObjectType _eObjectType);
	virtual int Update(void);
	virtual void Render(void);
private:
	virtual HRESULT Initialize(void);
	HRESULT AddComponent(void);
	virtual void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CAnyObject(eObjectType _eObjectType);
public:
	~CAnyObject(void);
	MAKE_UNCOPYABLE(CAnyObject)
};

#endif // AnyObject_h__