/*!
 * \file MouseCollision.h
 * \date 2016/06/05 23:00
 *
 * \author 박정민
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
/*
	//! 마우스 객체의 존재

	마우스 포인터 렌더하고.. 이건 UI에 렌더한다 치는데,

	마우스 렌더를 받는 친구들은, 아니면,

	input manager가 처음에 이 프레임에서의 마우스 위치를 set해놓고 가니까,

	이 위치를 계산하는건 input manager에게 넘기고,

	mouse collision 받는 객체들은 이 광선을 가지고, 자신과 충돌하는지 아닌지 여부를 검사..

	그런 담에, mouse와 가장 가까운 위치에 해당하는 객체를 피킹처리한다?
*/

//! 오브젝트 피킹하려면, 해당 오브젝트가 OBBCollision 컴포넌트를 갖고 있어야 한다..
// 바운딩 박스가 거기 들어있음..
// 물론 해당 오브젝트가, 충돌 후처리 코드(Functor) 안들고있으면 그냥 바운딩박스 정보만 갖고있는게 되니깐,
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