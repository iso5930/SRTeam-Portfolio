/*!
 * \file CameraObserver.h
 * \date 2016/06/08 21:46
 *
 * \author ¼­ÇÏ´Ã
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef CameraObserver_h__
#define CameraObserver_h__

#include "Observer.h"

namespace ENGINE
{
	class CInfoSubject;
}

class CCameraObserver : public ENGINE::CObserver
{
private:
	// member variable
private:
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;

	// member function
public:
	static CCameraObserver* Create(const void* _pOwner);

	virtual void Update(int _iMessage);

	// getter & setter
public:
	const D3DXMATRIX* GetViewMatrix(void);
	const D3DXMATRIX* GetProjMatrix(void);

	// constructor & destructor
private:
	explicit CCameraObserver(const void* _pOwner);
public:
	~CCameraObserver(void);
	MAKE_UNCOPYABLE(CCameraObserver)

};

#endif // CameraObserver_h__