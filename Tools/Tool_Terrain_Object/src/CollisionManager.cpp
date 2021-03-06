#include "StdAfx.h"
#include "CollisionManager.h"
#include "Collision.h"
#include "TerrainCollision.h"
#include "MouseCollision.h"

IMPLEMENT_SINGLETON(CCollisionManager)

CCollisionManager::CCollisionManager(void)
{
}

CCollisionManager::~CCollisionManager(void)
{
	Release();
}

HRESULT CCollisionManager::AddColObject(eCollisionType _eCollisionType, int _iVertexCountX, int _iVertexCountZ)
{
	COLLISION_MAP::iterator iter = m_CollisionMap.find(_eCollisionType);

	if(iter != m_CollisionMap.end())
	{
		UTIL::SHOW_ERROR(L"이미 존재하는 충돌", L"입니다.");
		return E_FAIL;
	}
	
	ENGINE::CCollision*	pCollision = NULL;
	switch(_eCollisionType)
	{
	case COLLISION_TYPE_TERRAIN:
		pCollision = NULL;
		break;

	case COLLISION_TYPE_MOUSE:
		pCollision = CMouseCollision::Create(NULL, _iVertexCountX, _iVertexCountZ);
		break;
	}

	if(pCollision == NULL)
		return E_FAIL;

	m_CollisionMap.insert(COLLISION_MAP::value_type(_eCollisionType, pCollision));

	return S_OK;
}

ENGINE::CCollision*	CCollisionManager::CloneColObject(eCollisionType _eCollisionType)
{
	COLLISION_MAP::iterator iter = m_CollisionMap.find(_eCollisionType);

	if(iter == m_CollisionMap.end())
		return NULL;

	//return iter->second->Clone();
	return NULL;
}

void CCollisionManager::Release(void)
{
	COLLISION_MAP::iterator iter = m_CollisionMap.begin();
	COLLISION_MAP::iterator iter_end = m_CollisionMap.end();
	for(; iter != iter_end; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	m_CollisionMap.clear();
}
