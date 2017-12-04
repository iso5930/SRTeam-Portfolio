/*!
 * \file AnyObject.h
 * \date 2016/06/09 2:45
 *
 * \author ������
 * Contact: user@company.com
 *
 * \brief � ������Ʈ��, ������Ʈ �����͸� �� ��ü�� ���� ���� �� �ִ�..
 �� ������Ʈ�� .dat�� ���� �ؼ�, Ŭ�󿡼� �о�� ���̴�..
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