/*!
 * \file MouseCollision.h
 * \date 2016/06/05 23:00
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
/*
	//! ���콺 ��ü�� ����

	���콺 ������ �����ϰ�.. �̰� UI�� �����Ѵ� ġ�µ�,

	���콺 ������ �޴� ģ������, �ƴϸ�,

	input manager�� ó���� �� �����ӿ����� ���콺 ��ġ�� set�س��� ���ϱ�,

	�� ��ġ�� ����ϴ°� input manager���� �ѱ��,

	mouse collision �޴� ��ü���� �� ������ ������, �ڽŰ� �浹�ϴ��� �ƴ��� ���θ� �˻�..

	�׷� �㿡, mouse�� ���� ����� ��ġ�� �ش��ϴ� ��ü�� ��ŷó���Ѵ�?
*/

//! ������Ʈ ��ŷ�Ϸ���, �ش� ������Ʈ�� OBBCollision ������Ʈ�� ���� �־�� �Ѵ�..
// �ٿ�� �ڽ��� �ű� �������..
// ���� �ش� ������Ʈ��, �浹 ��ó�� �ڵ�(Functor) �ȵ�������� �׳� �ٿ���ڽ� ������ �����ִ°� �Ǵϱ�,
#ifndef MouseCollision_h__
#define MouseCollision_h__

#include "Engine_Include.h"
#include "Collision.h"
#include "OBBCollision.h"
#include "CollisionFunctors.h"

BEGIN_NAMESPACE(ENGINE)
class CTerrainInfo;
class ENGINE_DLL_SPECIFIER CMouseCollision : public ENGINE::CCollision
{
	// member variable
private:
	D3DXVECTOR3 m_vPivot;
	D3DXVECTOR3 m_vPickingRay;

	const ENGINE::CTerrainInfo* m_pTerrainInfo;

	// member function
public:
	static CMouseCollision* Create(ENGINE::CGameObject* _pOwner);
	void PickTerrain(D3DXVECTOR3* _pOut);
	VERTEX_COLOR* PickTileIndex(void);//, int _iVertexLU, int _iVertexRU, int _iVertexLD, int _iVertexRD);
	void PickObject(const COBBCollision::OBB_INFO* _pOBBInfo, const D3DXMATRIX* _pWorld, CCollisionFunctor* _pFunctor);
private:
	void CalculatePickingRay(const D3DXMATRIX* _pWorld);
	void CalculatePickingRayInViewSpace(void);
	void CalculatePickingRayInLocalSpace(const D3DXMATRIX* _pWorld);
	void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CMouseCollision(ENGINE::CGameObject* _pOwner);
public:
	virtual ~CMouseCollision(void);
};
END_NAMESPACE

#endif // MouseCollision_h__