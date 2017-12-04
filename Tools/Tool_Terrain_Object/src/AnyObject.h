/*!
 * \file AnyObject.h
 * \date 2016/06/09 2:45
 *
 * \author 박정민
 * Contact: user@company.com
 *
 * \brief 어떤 오브젝트든, 컴포넌트 데이터를 이 객체를 통해 만들 수 있다..
 이 오브젝트를 .dat로 빼든 해서, 클라에서 읽어올 것이다..
 *
 * TODO: long description
 *
 * \note
*/

#ifndef AnyObject_h__
#define AnyObject_h__

#include "Tools_Include.h"
#include "GameObject.h"

class CAnyObject : public ENGINE::CGameObject
{
	// member variable
private:
	wstring m_strObjectKey;

	// member function
public:
	static CAnyObject* Create(eObjectType _eObjectType);
	virtual int Update(void);
	virtual void Render(void);
	//HRESULT AddComponent(ENGINE::CVIBuffer::eBufferType _eBufferType);
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
};

#endif // AnyObject_h__