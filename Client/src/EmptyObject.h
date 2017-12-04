/*!
 * \file EmptyObject.h
 * \date 2016/06/17 0:27
 *
 * \author 박정민
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef EmptyObject_h__
#define EmptyObject_h__

#include "Client_Include.h"
#include "GameObject.h"

namespace ENGINE
{
	class CTransform;

	class CTerrainCollision;
	class CMouseCollision;
	class COBBCollision;

	class CCollisionFunctor;
}
class CEmptyObject : public ENGINE::CGameObject
{
	// member variable
private:
	ENGINE::CTransform* m_pInfo;

	ENGINE::CTerrainCollision* m_pTerrainCollision;
	ENGINE::CMouseCollision* m_pMouseCollision;
	ENGINE::COBBCollision* m_pOBBCollision;

	ENGINE::CCollisionFunctor* m_pFunctor;
	float m_fX, m_fY, m_fZ;

	// member function
public:
	static CEmptyObject* Create(eObjectType _eObjectType, ENGINE::CCollisionFunctor* _pFunctor, float _fX, float _fY, float _fZ);
	virtual int Update(void);
	virtual void Render(void);
private:
	virtual HRESULT Initialize(void);
	HRESULT AddComponent(void);
	virtual void Release(void);

	// getter & setter
public:
	void SetPos(float _fX, float _fZ); //! 임시로..
	void SetColFunctor(ENGINE::CCollisionFunctor* _pFunctor)
	{
		m_pFunctor = _pFunctor;
	}
	void SetPos(D3DXVECTOR3& _vPos);


	// constructor & destructor
private:
	explicit CEmptyObject(eObjectType _eObjectType, float _fX, float _fY, float _fZ);
public:
	~CEmptyObject(void);
	MAKE_UNCOPYABLE(CEmptyObject)
};

#endif // EmptyObject_h__