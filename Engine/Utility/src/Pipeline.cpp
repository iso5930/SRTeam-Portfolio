#include "Pipeline.h"

#include "MathManager.h"

ENGINE::CPipeline::CPipeline(void)
{

}

ENGINE::CPipeline::~CPipeline(void)
{

}

void ENGINE::CPipeline::MakeWorldMatrix(D3DXMATRIX* _pOut,
										const D3DXVECTOR3* _pScale,
										const float _pAngle[],
										const D3DXVECTOR3* _pPos)
{
	D3DXMatrixIdentity(_pOut);

	D3DXVECTOR3 vRight(1.f, 0.f, 0.f);
	D3DXVECTOR3 vUp(0.f, 1.f, 0.f);
	D3DXVECTOR3 vLook(0.f, 0.f, 1.f);
	D3DXVECTOR3 vPos(0.f, 0.f, 0.f);

	vRight *= _pScale->x;
	vUp *= _pScale->y;
	vLook *= _pScale->z;

	CMathManager::MyRotationX(&vRight, &vRight, _pAngle[ANGLE_TYPE_X]);
	CMathManager::MyRotationX(&vUp, &vUp, _pAngle[ANGLE_TYPE_X]);
	CMathManager::MyRotationX(&vLook, &vLook, _pAngle[ANGLE_TYPE_X]);

	CMathManager::MyRotationY(&vRight, &vRight, _pAngle[ANGLE_TYPE_Y]);
	CMathManager::MyRotationY(&vUp, &vUp, _pAngle[ANGLE_TYPE_Y]);
	CMathManager::MyRotationY(&vLook, &vLook, _pAngle[ANGLE_TYPE_Y]);

	CMathManager::MyRotationZ(&vRight, &vRight, _pAngle[ANGLE_TYPE_Z]);
	CMathManager::MyRotationZ(&vUp, &vUp, _pAngle[ANGLE_TYPE_Z]);
	CMathManager::MyRotationZ(&vLook, &vLook, _pAngle[ANGLE_TYPE_Z]);

	vPos = *_pPos;

	MakeTransformMatrix(_pOut, &vRight, &vUp, &vLook, &vPos);
}

void ENGINE::CPipeline::MakeViewMatrix(D3DXMATRIX* _pOut,
									   const D3DXVECTOR3* _pEye,
									   const D3DXVECTOR3* _pAt,
									   const D3DXVECTOR3* _pUp)
{
	D3DXMatrixIdentity(_pOut);

	D3DXVECTOR3 vRight(1.f, 0.f, 0.f);
	D3DXVECTOR3 vUp(0.f, 1.f, 0.f);
	D3DXVECTOR3 vLook(0.f, 0.f, 1.f);
	D3DXVECTOR3 vPos(0.f, 0.f, 0.f);

	vLook = *_pAt - *_pEye;
	D3DXVec3Normalize(&vLook, &vLook);

	D3DXVec3Cross(&vRight, _pUp, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	D3DXVec3Cross(&vUp, &vLook, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);

	vPos = *_pEye;

	MakeTransformMatrix(_pOut, &vRight, &vUp, &vLook, &vPos);
	D3DXMatrixInverse(_pOut, 0, _pOut);
}

void ENGINE::CPipeline::MakeProjMatrix(D3DXMATRIX* _pOut,
									   float _fFovY,
									   float _fAspect,
									   float _fNear,
									   float _fFar)
{
	D3DXMatrixIdentity(_pOut);

	_pOut->_22 = 1.f / tan(_fFovY / 2.f);
	_pOut->_11 = (_pOut->_22) / _fAspect;

	_pOut->_33 = _fFar / (_fFar - _fNear);
	_pOut->_43 = _pOut->_33 * -_fNear;

	_pOut->_34 = 1.f;
	_pOut->_44 = 0.f;
}

void ENGINE::CPipeline::MyTransformCoord(D3DXVECTOR3* _pOut, const D3DXVECTOR3* _pVec, const D3DXMATRIX* _pMat)
{
	D3DXVECTOR4 vVec4(_pVec->x, _pVec->y, _pVec->z, 1.f);

	_pOut->x = vVec4.x * _pMat->_11 +
		vVec4.y * _pMat->_21 +
		vVec4.z * _pMat->_31 +
		vVec4.w * _pMat->_41;

	_pOut->y = vVec4.x * _pMat->_12 +
		vVec4.y * _pMat->_22 +
		vVec4.z * _pMat->_32 +
		vVec4.w * _pMat->_42;

	_pOut->z = vVec4.x * _pMat->_13 +
		vVec4.y * _pMat->_23 +
		vVec4.z * _pMat->_33 +
		vVec4.w * _pMat->_43;

	float fZ = vVec4.x * _pMat->_14 +
		vVec4.y * _pMat->_24 +
		vVec4.z * _pMat->_34 +
		vVec4.w * _pMat->_44;

	_pOut->x /= fZ;
	_pOut->y /= fZ;
	_pOut->z /= fZ;
}

void ENGINE::CPipeline::MyTransformNormal(D3DXVECTOR3* _pOut, const D3DXVECTOR3* _pVec, const D3DXMATRIX* _pMat)
{
	D3DXVECTOR4 vVec4(_pVec->x, _pVec->y, _pVec->z, 0.f);

	_pOut->x = vVec4.x * _pMat->_11 +
		vVec4.y * _pMat->_21 +
		vVec4.z * _pMat->_31 +
		vVec4.w * _pMat->_41;

	_pOut->y = vVec4.x * _pMat->_12 +
		vVec4.y * _pMat->_22 +
		vVec4.z * _pMat->_32 +
		vVec4.w * _pMat->_42;

	_pOut->z = vVec4.x * _pMat->_13 +
		vVec4.y * _pMat->_23 +
		vVec4.z * _pMat->_33 +
		vVec4.w * _pMat->_43;

	float fZ = vVec4.x * _pMat->_14 +
		vVec4.y * _pMat->_24 +
		vVec4.z * _pMat->_34 +
		vVec4.w * _pMat->_44;

	if (fZ != 0.f)
	{
		_pOut->x /= fZ;
		_pOut->y /= fZ;
		_pOut->z /= fZ;
	}
}

void ENGINE::CPipeline::MakeTransformMatrix(D3DXMATRIX* _pOut,
											const D3DXVECTOR3* _pRight,
											const D3DXVECTOR3* _pUp,
											const D3DXVECTOR3* _pLook,
											const D3DXVECTOR3* _pPos)
{
	memcpy(_pOut->m[0], _pRight, sizeof(float) * 3);
	memcpy(_pOut->m[1], _pUp, sizeof(float) * 3);
	memcpy(_pOut->m[2], _pLook, sizeof(float) * 3);
	memcpy(_pOut->m[3], _pPos, sizeof(float) * 3);
}
