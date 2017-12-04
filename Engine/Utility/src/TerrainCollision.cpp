#include "TerrainCollision.h"

#include "Export_Function.h"
#include "GameObject.h"
#include "TerrainInfo.h"
#include "Transform.h"

ENGINE::CTerrainCollision::CTerrainCollision(ENGINE::CGameObject* _pOwner)
:CCollision(_pOwner)
,m_pOwnersInfo(NULL)
,m_pTerrainInfo(NULL)
,m_pColFunctor(NULL)
,COS_CANNOT_CLIMB(0.9f) // 빗변 지나갈 수 있는지 / 아닌지 결정하는 cos 값..
{

}

ENGINE::CTerrainCollision::~CTerrainCollision(void)
{
	Release();
}

ENGINE::CTerrainCollision* ENGINE::CTerrainCollision::Create(ENGINE::CGameObject* _pOwner, ENGINE::CTransform* _pOwnersInfo, ENGINE::CCollisionFunctor* _ColFunctor)
{
	CTerrainCollision* pInstance = new CTerrainCollision(_pOwner);
	HRESULT hr = pInstance->Initialize(_pOwnersInfo, _ColFunctor);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int ENGINE::CTerrainCollision::Update(void)
{
	//! init에서 하면 scene이 null일 때라 검색이 안된다 젠장..
		ENGINE::GetManagement()->PrepareFind();
		CComponent* pComponent = ENGINE::GetManagement()->GetComponent(L"Terrain_Info");
		if (pComponent == NULL)
			return E_FAIL;
		m_pTerrainInfo = static_cast<const ENGINE::CTerrainInfo*>(pComponent);

	D3DXVECTOR3 vTargetPos = m_pOwnersInfo->m_vPos;

	VERTEX_COLOR* pVertexColor = m_pTerrainInfo->m_pVertexColor;
	DWORD dwVertexCountX = m_pTerrainInfo->m_dwVertexCountX;
	DWORD dwVertexCountZ = m_pTerrainInfo->m_dwVertexCountZ;


	int iIndex = (int(vTargetPos.z) / VTXITV) * dwVertexCountX + (int(vTargetPos.x) / VTXITV);

	float fRatioX = (vTargetPos.x - pVertexColor[iIndex + dwVertexCountX].vPos.x) / VTXITV;
	float fRatioZ = (pVertexColor[iIndex + dwVertexCountX].vPos.z - vTargetPos.z) / VTXITV;

	D3DXPLANE Plane;
	D3DXVECTOR3 vNormal(0.f, 0.f, 0.f);
	if(fRatioX > fRatioZ) // 오른쪽 위
	{
		D3DXPlaneFromPoints(&Plane,
			&pVertexColor[iIndex + dwVertexCountX].vPos,
			&pVertexColor[iIndex + dwVertexCountX + 1].vPos,
			&pVertexColor[iIndex + 1].vPos);

		D3DXVECTOR3 vVec1 = pVertexColor[iIndex + dwVertexCountX].vPos - pVertexColor[iIndex + dwVertexCountX + 1].vPos;
		D3DXVECTOR3 vVec2 = pVertexColor[iIndex + dwVertexCountX + 1].vPos - pVertexColor[iIndex + 1].vPos;
		D3DXVec3Cross(&vNormal, &vVec1, &vVec2);
		D3DXVec3Normalize(&vNormal, &vNormal);
	}
	else // 왼쪽 아래
	{
		D3DXPlaneFromPoints(&Plane,
			&pVertexColor[iIndex + dwVertexCountX].vPos, 
			&pVertexColor[iIndex + 1].vPos,
			&pVertexColor[iIndex].vPos);

		D3DXVECTOR3 vVec1 = pVertexColor[iIndex + dwVertexCountX].vPos - pVertexColor[iIndex + 1].vPos;
		D3DXVECTOR3 vVec2 = pVertexColor[iIndex + 1].vPos - pVertexColor[iIndex].vPos;
		D3DXVec3Cross(&vNormal, &vVec1, &vVec2);
		D3DXVec3Normalize(&vNormal, &vNormal);
	}


	float fCos = D3DXVec3Dot(&vNormal, &D3DXVECTOR3(0.f, 1.f, 0.f));
	if (fCos < COS_CANNOT_CLIMB)
	{
		(*m_pColFunctor)(NULL, NULL, &vNormal);
	}
	else
		m_pOwnersInfo->m_vPos.y = (-Plane.a * vTargetPos.x - Plane.c * vTargetPos.z - Plane.d) / Plane.b + 1.f;

	return 0;
}

HRESULT ENGINE::CTerrainCollision::Initialize(ENGINE::CTransform* _pOwnersInfo, ENGINE::CCollisionFunctor* _ColFunctor)
{
	m_pOwnersInfo = _pOwnersInfo;

	m_pColFunctor = _ColFunctor;

	return S_OK;
}

void ENGINE::CTerrainCollision::Release(void)
{
	SAFE_DELETE(m_pColFunctor);
}
