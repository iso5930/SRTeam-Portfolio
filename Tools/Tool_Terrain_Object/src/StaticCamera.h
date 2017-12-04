/*!
 * \file StaticCamera.h
 * \date 2016/06/07 20:20
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

#pragma once

#include "Camera.h"

namespace ENGINE
{
	class CTransform;
}

class CStaticCamera : public ENGINE::CCamera
{
public:
	const ENGINE::CTransform* m_pTargetInfo;
	float m_fTargetDistance;
	float m_fCameraSpeed;
	float m_fAngle;

public:
	static CStaticCamera*	Create(eObjectType _eObjectType);
	virtual int Update(void);

public:
	void SetTarget(const ENGINE::CTransform* _pTargetInfo);

private:
	virtual HRESULT Initialize(void);
	void KeyCheck(void);
	virtual void Release(void);

public:
	CStaticCamera(eObjectType _eObjectType);
	~CStaticCamera(void);
};
