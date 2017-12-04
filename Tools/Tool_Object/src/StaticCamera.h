/*!
 * \file StaticCamera.h
 * \date 2016/06/04 16:43
 *
 * \author ¹ÚÁ¤¹Î
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef StaticCamera_h__
#define StaticCamera_h__

#include "Tools_Include.h"
#include "Camera.h"

namespace ENGINE
{
	class CTransform;
}
class CStaticCamera : public ENGINE::CCamera
{
	// member variable
private:
	const ENGINE::CTransform* m_pTargetInfo;
	float m_fTargetDistance;
	float m_fAngle;

	// member function
public:
	static CStaticCamera* Create(eObjectType _eObjectType);
	virtual int Update(void);
private:
	virtual HRESULT Initialize(void);
	void KeyCheck(void);
	virtual void Release(void);

	// getter & setter
public:
	void SetTargetInfo(const ENGINE::CTransform* _pTargetInfo);

	// constructor & destructor
private:
	explicit CStaticCamera(eObjectType _eObjectType);
public:
	virtual ~CStaticCamera(void);
	MAKE_UNCOPYABLE(CStaticCamera)
};

#endif // StaticCamera_h__