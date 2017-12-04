/*!
 * \file Pipeline.h
 * \date 2016/06/03 2:04
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 //! �̰Ŷ�, �Ž� �Ŵ�����, ���̻� Ʃ���� �ʿ�� ����?
 ���̷�Ʈ �Լ� �� ������ �ǳ�?
 �̸��� �����ϰ�..
*/

#ifndef Pipeline_h__
#define Pipeline_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CPipeline
{
	// member variable
private:
	// -

	// member function
public:
	static void MakeWorldMatrix(D3DXMATRIX* _pOut,
								const D3DXVECTOR3* _pScale,
								const float _pAngle[],
								const D3DXVECTOR3* _pPos);

	static void MakeViewMatrix(D3DXMATRIX* _pOut,
							   const D3DXVECTOR3* _pEye,
							   const D3DXVECTOR3* _pAt,
							   const D3DXVECTOR3* _pUp);

	static void MakeProjMatrix(D3DXMATRIX* _pOut,
							   float _fFovY,
							   float _fAspect,
							   float _fNear,
							   float _fFar);

	static void MyTransformCoord(D3DXVECTOR3* _pOut,
								 const D3DXVECTOR3* _pVec,
								 const D3DXMATRIX* _pMat);

	static void MyTransformNormal(D3DXVECTOR3* _pOut,
			 					  const D3DXVECTOR3* _pVec,
								  const D3DXMATRIX* _pMat);
private:
	static void MakeTransformMatrix(D3DXMATRIX* _pOut,
									const D3DXVECTOR3* _pRight,
									const D3DXVECTOR3* _pUp,
									const D3DXVECTOR3* _pLook,
									const D3DXVECTOR3* _pPos);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CPipeline(void);
	~CPipeline(void);
MAKE_UNCOPYABLE(CPipeline)
};
END_NAMESPACE

#endif // Pipeline_h__