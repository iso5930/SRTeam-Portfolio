#include "MathManager.h"

ENGINE::CMathManager::CMathManager(void)
{

}

ENGINE::CMathManager::~CMathManager(void)
{

}

void ENGINE::CMathManager::MyRotationX(D3DXVECTOR3* _pOut, const D3DXVECTOR3* _pIn, const float _fAngle)
{
	const D3DXVECTOR3 vTemp = *_pIn;

	_pOut->x = vTemp.x;
	_pOut->y = vTemp.y * cosf(_fAngle) - vTemp.z * sinf(_fAngle);
	_pOut->z = vTemp.y * sinf(_fAngle) + vTemp.z * cosf(_fAngle);
}

void ENGINE::CMathManager::MyRotationY(D3DXVECTOR3* _pOut, const D3DXVECTOR3* _pIn, const float _fAngle)
{
	const D3DXVECTOR3 vTemp = *_pIn;

	_pOut->x = vTemp.x * cosf(_fAngle) + vTemp.z * sinf(_fAngle);
	_pOut->y = vTemp.y;
	_pOut->z = vTemp.x * -sinf(_fAngle) + vTemp.z * cosf(_fAngle);
}

void ENGINE::CMathManager::MyRotationZ(D3DXVECTOR3* _pOut, const D3DXVECTOR3* _pIn, const float _fAngle)
{
	const D3DXVECTOR3 vTemp = *_pIn;

	_pOut->x = vTemp.x * cosf(_fAngle) - vTemp.y * sinf(_fAngle);
	_pOut->y = vTemp.x * sinf(_fAngle) + vTemp.y * cosf(_fAngle);
	_pOut->z = vTemp.z;
}

D3DXVECTOR3 ENGINE::CMathManager::Bezier3(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, double _dmu)
{
	/*double d1, d2, d3;

	D3DXVECTOR3 vPoint;

	d3 = _dmu * _dmu;

	d1 = 1 - _dmu;

	d2 = d1 * d1;

	vPoint.x = float(_v1.x * d2 + 2 * _v2.x * d1 * _dmu + _v3.x * d3);
	vPoint.y = float(_v1.y * d2 + 2 * _v2.y * d1 * _dmu + _v3.y * d3);
	vPoint.z = float(_v1.z * d2 + 2 * _v2.z * d1 * _dmu + _v3.z * d3);*/

	double d1, d2, d3;

	D3DXVECTOR3 vPoint;

	d1 = _dmu * _dmu;
	d2 = 2 * _dmu * (1 - _dmu);
	d3 = (1 - _dmu) * (1 - _dmu);

	vPoint.x = float(_v3.x * d1 + _v2.x * d2 + _v1.x * d3);
	vPoint.y = float(_v3.y * d1 + _v2.y * d2 + _v1.y * d3);
	vPoint.z = float(_v3.z * d1 + _v2.z * d2 + _v1.z * d3);
	
	return vPoint;
}

D3DXVECTOR3 ENGINE::CMathManager::Bezier4(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, D3DXVECTOR3 _v4, float _dmu)
{
	float d1, d2, d3;

	D3DXVECTOR3 vPoint;

	d1 = 1 - _dmu;

	d2 = d1 * d1 * d1;

	d3 = _dmu * _dmu * _dmu;

	vPoint.x = d2 * _v1.x + 3 * _dmu * d1 * d1 * _v2.x + 3 * _dmu * _dmu * d1 * _v3.x + d3 * _v4.x;
	vPoint.y = d2 * _v1.y + 3 * _dmu * d1 * d1 * _v2.y + 3 * _dmu * _dmu * d1 * _v3.y + d3 * _v4.y;
	vPoint.z = d2 * _v1.y + 3 * _dmu * d1 * d1 * _v2.z + 3 * _dmu * _dmu * d1 * _v3.z + d3 * _v4.z;

	return vPoint;
}

D3DXVECTOR3 ENGINE::CMathManager::Bezier(D3DXVECTOR3* _pPoint, int _in, float _fmu)
{
	int k,kn,nn,nkn;

	double blend, muk, munk;

	D3DXVECTOR3 vPoint(0.f, 0.f, 0.f);

	muk = 1.0;

	munk = pow(1 - (double)_fmu, (double)_in);

	for(k = 0; k <= _in; k++)
	{
		nn = _in;
		kn = k;

		nkn = _in - k;

		blend = muk * munk;

		muk *= _fmu;

		munk /= (1 - _fmu);

		while(nn >= 1)
		{
			blend *= nn;

			nn --;

			if(kn > 1)
			{
				blend /= (double)kn;
				kn --;
			}
			if(nkn > 1)
			{
				blend /= (double)nkn;
				nkn--;
			}
		}
		vPoint.x += float(_pPoint[k].x * blend);
		vPoint.y += float(_pPoint[k].y * blend);
		vPoint.z += float(_pPoint[k].z * blend);
	}

	return vPoint;
}