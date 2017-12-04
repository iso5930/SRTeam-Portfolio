/*!
 * \file TerrainCollision.h
 * \date 2016/06/05 17:27
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

#ifndef TerrainCollision_h__
#define TerrainCollision_h__

#include "Engine_Include.h"
#include "Collision.h"
#include "CollisionFunctors.h"

BEGIN_NAMESPACE(ENGINE)
class CTransform;
class CTerrainInfo;
class ENGINE_DLL_SPECIFIER CTerrainCollision : public ENGINE::CCollision
{
	//! 이건 뭐.. 거의 고정인듯.
	enum
	{
		VTXITV = 1
	};
	const float COS_CANNOT_CLIMB;

	// member variable
private:
	ENGINE::CTransform* m_pOwnersInfo;
	const ENGINE::CTerrainInfo* m_pTerrainInfo;

	CCollisionFunctor* m_pColFunctor;

	// member function
public:
	static CTerrainCollision* Create(ENGINE::CGameObject* _pOwner, ENGINE::CTransform* _pOwnersInfo, CCollisionFunctor* _ColFunctor);
	virtual int Update(void);
private:
	HRESULT Initialize(ENGINE::CTransform* _pOwnersInfo, CCollisionFunctor* _ColFunctor);
	void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CTerrainCollision(ENGINE::CGameObject* _pOwner);
public:
	virtual ~CTerrainCollision(void);
	MAKE_UNCOPYABLE(CTerrainCollision)
};
END_NAMESPACE

#endif // TerrainCollision_h__