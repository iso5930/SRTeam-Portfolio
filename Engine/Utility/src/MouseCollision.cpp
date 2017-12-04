#include "MouseCollision.h"

#include "Export_Function.h"
#include "TerrainInfo.h"
#include "OBBCollision.h"
#include "MouseCursor.h"

ENGINE::CMouseCollision::CMouseCollision(ENGINE::CGameObject* _pOwner)
:CCollision(_pOwner)
,m_vPivot(0.f, 0.f, 0.f)
,m_vPickingRay(0.f, 0.f, 0.f)
,m_pTerrainInfo(NULL)
{

}

ENGINE::CMouseCollision::~CMouseCollision(void)
{
	Release();
}

ENGINE::CMouseCollision* ENGINE::CMouseCollision::Create(ENGINE::CGameObject* _pOwner)
{
	return new CMouseCollision(_pOwner);
}

// PickObject를 받고..
// 없으면? PickTerrain..
// 이게 순서겠지..

// object를 찍었을 때, 이후의 처리?

void ENGINE::CMouseCollision::PickTerrain(D3DXVECTOR3* _pOut)
{
	//if (m_pTerrainInfo == NULL)
	//{
		ENGINE::GetManagement()->PrepareFind();
		CComponent* pComponent = ENGINE::GetManagement()->GetComponent(L"Terrain_Info");
		if (pComponent == NULL)
			return;
		m_pTerrainInfo = static_cast<const ENGINE::CTerrainInfo*>(pComponent);
	//}

	////132 173
	//
	//D3DXVECTOR3 vPos;

	//ENGINE::GetInputManager()->GetMousePos(&vPos);

	//if(vPos.x <= 132 && vPos.y <= 173)
	//{
	//	return;
	//}

	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	CalculatePickingRay(&matIdentity);

	const VERTEX_COLOR* pVertex = m_pTerrainInfo->m_pVertexColor;
	DWORD dwVertexCountX = m_pTerrainInfo->m_dwVertexCountX;
	DWORD dwVertexCountZ = m_pTerrainInfo->m_dwVertexCountZ;

	float fU = 0.f;
	float fV = 0.f;
	float fDist = 0.f;
	for(DWORD z = 0; z < dwVertexCountZ - 1; ++z)
	{
		for(DWORD x= 0; x < dwVertexCountX - 1; ++x)
		{
			DWORD dwIndex = z * dwVertexCountX + x;

			// 오른쪽 위 폴리곤
			if(D3DXIntersectTri(&pVertex[dwIndex + dwVertexCountX + 1].vPos,
				&pVertex[dwIndex + dwVertexCountX].vPos,
				&pVertex[dwIndex + 1].vPos,
				&m_vPivot,
				&m_vPickingRay,
				&fU, &fV, &fDist))
			{
				*_pOut = pVertex[dwIndex + dwVertexCountX + 1].vPos +
					(pVertex[dwIndex + dwVertexCountX].vPos - pVertex[dwIndex + dwVertexCountX + 1].vPos) * fU +
					(pVertex[dwIndex + 1].vPos - pVertex[dwIndex + dwVertexCountX + 1].vPos) * fV;

				return;
			}

			// 왼쪽 아래 폴리곤
			if(D3DXIntersectTri(&pVertex[dwIndex].vPos, 
				&pVertex[dwIndex + 1].vPos,
				&pVertex[dwIndex + dwVertexCountX].vPos,
				&m_vPivot,
				&m_vPickingRay,
				&fU, &fV, &fDist))
			{
				*_pOut = pVertex[dwIndex].vPos +
					(pVertex[dwIndex + 1].vPos - pVertex[dwIndex].vPos)	* fU +
					(pVertex[dwIndex + dwVertexCountX].vPos - pVertex[dwIndex].vPos) * fV;

				return;
			}
		}
	}
}

void ENGINE::CMouseCollision::PickObject(const COBBCollision::OBB_INFO* _pOBBInfo, const D3DXMATRIX* _pWorld, CCollisionFunctor* _pFunctor)
{
	CalculatePickingRay(_pWorld);

	float fClosest = FLT_MAX;
	float fU = 0.f;
	float fV = 0.f;
	float fDist = 0.f;

	D3DXVECTOR3 pOBBVertex[8];
	float fPosX = _pOBBInfo->fRadius[ANGLE_TYPE_X];
	float fPosY = _pOBBInfo->fRadius[ANGLE_TYPE_Y];
	float fPosZ = _pOBBInfo->fRadius[ANGLE_TYPE_Z];
	SetD3DXVector3(&pOBBVertex[0], fPosX * -1.f, fPosY, fPosZ * -1.f);
	SetD3DXVector3(&pOBBVertex[1], fPosX, fPosY, fPosZ * -1.f);
	SetD3DXVector3(&pOBBVertex[2], fPosX, fPosY * -1.f, fPosZ * -1.f);
	SetD3DXVector3(&pOBBVertex[3], fPosX * -1.f, fPosY * -1.f, fPosZ * -1.f);
	SetD3DXVector3(&pOBBVertex[4], fPosX * -1.f, fPosY, fPosZ);
	SetD3DXVector3(&pOBBVertex[5], fPosX, fPosY, fPosZ);
	SetD3DXVector3(&pOBBVertex[6], fPosX, fPosY * -1.f, fPosZ);
	SetD3DXVector3(&pOBBVertex[7], fPosX * -1.f, fPosY * -1.f, fPosZ);

	// x+
	if(D3DXIntersectTri(&pOBBVertex[1], &pOBBVertex[5], &pOBBVertex[6],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}
	if(D3DXIntersectTri(&pOBBVertex[1], &pOBBVertex[6], &pOBBVertex[2],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}

	// x-
	if(D3DXIntersectTri(&pOBBVertex[4], &pOBBVertex[0], &pOBBVertex[3],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}
	if(D3DXIntersectTri(&pOBBVertex[4], &pOBBVertex[3], &pOBBVertex[7],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}

	// y+
	if(D3DXIntersectTri(&pOBBVertex[4], &pOBBVertex[5], &pOBBVertex[1],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}
	if(D3DXIntersectTri(&pOBBVertex[4], &pOBBVertex[1], &pOBBVertex[0],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}

	// y-
	if(D3DXIntersectTri(&pOBBVertex[3], &pOBBVertex[2], &pOBBVertex[6],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}
	if(D3DXIntersectTri(&pOBBVertex[3], &pOBBVertex[6], &pOBBVertex[7],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}

	// z+
	if(D3DXIntersectTri(&pOBBVertex[5], &pOBBVertex[4], &pOBBVertex[7],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}
	if(D3DXIntersectTri(&pOBBVertex[5], &pOBBVertex[7], &pOBBVertex[6],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}

	// z-
	if(D3DXIntersectTri(&pOBBVertex[0], &pOBBVertex[1], &pOBBVertex[2],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}
	if(D3DXIntersectTri(&pOBBVertex[0], &pOBBVertex[2], &pOBBVertex[3],
		&m_vPivot, &m_vPickingRay, &fU, &fV, &fDist))
	{
		if (fDist < fClosest)
			fClosest = fDist;
	}

	if (fClosest == FLT_MAX)
	{
		// no picked
		SAFE_DELETE(_pFunctor);
	}
	else
	{
		// mouse가 갖고 있는 closest와 비교하고,
		// mouse에 들어있는 functor를 교체한다..
		CGameObject* pObj = ENGINE::GetManagement()->GetGameObject(L"MouseCursor");
		CMouseCursor* pCursor = static_cast<CMouseCursor*>(pObj);
		if (fClosest < pCursor->GetClosestDist())
		{
			pCursor->SetPickingInfo(fClosest, _pFunctor);
		}
	}
}

void ENGINE::CMouseCollision::CalculatePickingRay(const D3DXMATRIX* _pWorld)
{
	CalculatePickingRayInViewSpace();
	CalculatePickingRayInLocalSpace(_pWorld);
}

void ENGINE::CMouseCollision::CalculatePickingRayInViewSpace(void)
{
	POINT ptMouse;
	ENGINE::GetInputManager()->GetMousePos(&ptMouse);

	D3DXMATRIX matProj;
	ENGINE::GetDevice()->GetTransform(D3DTS_PROJECTION, &matProj);

	// 투영 창에서의 마우스 포인트..
	D3DXVECTOR3	vProjPoint(
		((float(ptMouse.x) / (WINCX >> 1)  - 1.f) / matProj._11),
		((float(-ptMouse.y) / (WINCY >> 1) + 1.f) / matProj._22),
		1.f);

	SetD3DXVector3(&m_vPivot, 0.f, 0.f, 0.f);
	m_vPickingRay = vProjPoint - m_vPivot;
	D3DXVec3Normalize(&m_vPickingRay, &m_vPickingRay);
}

void ENGINE::CMouseCollision::CalculatePickingRayInLocalSpace(const D3DXMATRIX* _pWorld)
{
	// matview 적용된 걸 벗겨낸다..
	D3DXMATRIX matView;
	ENGINE::GetDevice()->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);
	D3DXVec3TransformCoord(&m_vPivot, &m_vPivot, &matView);
	D3DXVec3TransformNormal(&m_vPickingRay, &m_vPickingRay, &matView);

	// matworld 적용된 걸 벗겨낸다..
	D3DXMATRIX matWorld;
	D3DXMatrixInverse(&matWorld, NULL, _pWorld);
	D3DXVec3TransformCoord(&m_vPivot, &m_vPivot, &matWorld);
	D3DXVec3TransformNormal(&m_vPickingRay, &m_vPickingRay, &matWorld);	
}

void ENGINE::CMouseCollision::Release(void)
{
	
}

VERTEX_COLOR* ENGINE::CMouseCollision::PickTileIndex(void)//int _iVertexLU, int _iVertexRU, int _iVertexLD, int _iVertexRD)
{
	ENGINE::GetManagement()->PrepareFind();
	CComponent* pComponent = ENGINE::GetManagement()->GetComponent(L"Terrain_Info");
	if (pComponent == NULL)
		return NULL;
	m_pTerrainInfo = static_cast<const ENGINE::CTerrainInfo*>(pComponent);

	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	CalculatePickingRay(&matIdentity);

	const VERTEX_COLOR* pVertex = m_pTerrainInfo->m_pVertexColor;
	DWORD dwVertexCountX = m_pTerrainInfo->m_dwVertexCountX;
	DWORD dwVertexCountZ = m_pTerrainInfo->m_dwVertexCountZ;

	VERTEX_COLOR*	pTempVertex = new VERTEX_COLOR[4];

	float fU = 0.f;
	float fV = 0.f;
	float fDist = 0.f;

	for(DWORD z = 0; z < dwVertexCountZ - 1; ++z)
	{
		for(DWORD x= 0; x < dwVertexCountX - 1; ++x)
		{
			DWORD dwIndex = z * dwVertexCountX + x;

			// 오른쪽 위 폴리곤
			if(D3DXIntersectTri(&pVertex[dwIndex + dwVertexCountX + 1].vPos,
				&pVertex[dwIndex + dwVertexCountX].vPos,
				&pVertex[dwIndex + 1].vPos,
				&m_vPivot,
				&m_vPickingRay,
				&fU, &fV, &fDist))
			{
				pTempVertex[0] = pVertex[dwIndex + dwVertexCountX];
				pTempVertex[1] = pVertex[dwIndex + dwVertexCountX + 1];
				pTempVertex[2] = pVertex[dwIndex + 1];
				pTempVertex[3] = pVertex[dwIndex];

				return pTempVertex;
			}

			// 왼쪽 아래 폴리곤
			if(D3DXIntersectTri(&pVertex[dwIndex].vPos, 
				&pVertex[dwIndex + 1].vPos,
				&pVertex[dwIndex + dwVertexCountX].vPos,
				&m_vPivot,
				&m_vPickingRay,
				&fU, &fV, &fDist))
			{
				pTempVertex[0] = pVertex[dwIndex + dwVertexCountX];
				pTempVertex[1] = pVertex[dwIndex + dwVertexCountX + 1];
				pTempVertex[2] = pVertex[dwIndex + 1];
				pTempVertex[3] = pVertex[dwIndex];

				return pTempVertex;
			}
		}
	}
	return NULL;
}
