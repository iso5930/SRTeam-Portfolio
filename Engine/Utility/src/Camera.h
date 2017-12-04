/*!
 * \file Camera.h
 * \date 2016/06/04 16:24
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

#ifndef Camera_h__
#define Camera_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CCamera : public CGameObject
{
	// member variable
protected:
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;

	// member function
public:
	void SetViewSpaceMatrix(const D3DXVECTOR3* _pEye,
							const D3DXVECTOR3* _pAt,
							const D3DXVECTOR3* _pUp);

	void SetProjectionMatrix(const float _fFovY,
							 const float _fAspect,
							 const float _fNear,
							 const float _fFar);

	// getter & setter
public:
	// -

	// constructor & destructor
protected:
	explicit CCamera(eObjectType _eObjectType);
public:
	virtual ~CCamera(void) PURE;
	MAKE_UNCOPYABLE(CCamera)
};
END_NAMESPACE

#endif // Camera_h__