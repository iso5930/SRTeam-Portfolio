/*!
 * \file CollisionManager.h
 * \date 2016/06/07 18:27
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

namespace ENGINE
{
	class CCollision;
}

class CCollisionManager
{
	DECLARE_SINGLETON(CCollisionManager)

public:
	enum eCollisionType
	{
		COLLISION_TYPE_TERRAIN,
		COLLISION_TYPE_MOUSE
	};

private:
	typedef map<eCollisionType, ENGINE::CCollision*> COLLISION_MAP;

private:
	COLLISION_MAP	m_CollisionMap;

public:
	HRESULT AddColObject(eCollisionType _eCollisionType, int _iVertexCountX = 0, int _iVertexCountZ = 0);
	ENGINE::CCollision*	CloneColObject(eCollisionType _eCollisionType);

private:
	void Release(void);

public:
	CCollisionManager(void);
	~CCollisionManager(void);
};
