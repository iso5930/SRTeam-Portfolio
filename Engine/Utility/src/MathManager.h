/*!
 * \file MathManager.h
 * \date 2016/06/03 2:33
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

#ifndef MathManager_h__
#define MathManager_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CMathManager
{
	// member variable
private:
	// -

	// member function
public:
	static void MyRotationX(D3DXVECTOR3* _pOut, const D3DXVECTOR3* _pIn, const float _fAngle);
	static void MyRotationY(D3DXVECTOR3* _pOut, const D3DXVECTOR3* _pIn, const float _fAngle);
	static void MyRotationZ(D3DXVECTOR3* _pOut, const D3DXVECTOR3* _pIn, const float _fAngle);

public:
	static D3DXVECTOR3 Bezier(D3DXVECTOR3* _pPoint, int _in, float _fmu);
	static D3DXVECTOR3 Bezier3(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, double _dmu);
	static D3DXVECTOR3 Bezier4(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, D3DXVECTOR3 _v4, float _dmu);
	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CMathManager(void);
	~CMathManager(void);
	MAKE_UNCOPYABLE(CMathManager)
};
END_NAMESPACE

#endif // MathManager_h__