#include "StdAfx.h"
#include "MouseCollision.h"
#include "InfoSubject.h"
#include "Export_Function.h"

CMouseCollision::CMouseCollision(ENGINE::CGameObject* _pOwner)
:CCollision(_pOwner)
, m_vPivotPos(0.f, 0.f, 0.f)
, m_vRayDir(0.f, 0.f, 0.f)
, m_iVertexCountX(0)
, m_iVertexCountZ(0)
{
}

CMouseCollision::~CMouseCollision(void)
{
	Release();
}

CMouseCollision*	CMouseCollision::Create(ENGINE::CGameObject* _pOwner, int _iVertexCountX, int _iVertexCountZ)
{
	CMouseCollision*	pInstance = new CMouseCollision(_pOwner);
	HRESULT	hr = pInstance->Initialize(_iVertexCountX, _iVertexCountZ);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int	CMouseCollision::PickTerrainTexture(const VERTEX_TEXTURE* _pTerrainVertex)
{
	TranslationViewspace();

	D3DXMATRIX	matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	TranslationLocal(&matIdentity);

	const VERTEX_TEXTURE*	pVertex = _pTerrainVertex;

	float fU, fV, fDist;

	for(int z = 0; z < m_iVertexCountZ - 1; ++z)
	{
		for(int x= 0; x < m_iVertexCountX - 1; ++x)
		{
			int iIndex = z * m_iVertexCountX + x;

			if(D3DXIntersectTri(&pVertex[iIndex + m_iVertexCountX + 1].vPos, 
				&pVertex[iIndex + m_iVertexCountX].vPos,
				&pVertex[iIndex + 1].vPos,
				&m_vPivotPos,
				&m_vRayDir,
				&fU, &fV, &fDist))
			{
				return iIndex - z;
			}

			// ¿ÞÂÊ ¾Æ·¡ Æú¸®°ï
			if(D3DXIntersectTri(&pVertex[iIndex].vPos, 
				&pVertex[iIndex + 1].vPos,
				&pVertex[iIndex + m_iVertexCountX].vPos,
				&m_vPivotPos,
				&m_vRayDir,
				&fU, &fV, &fDist))
			{
				return iIndex - z;
			}
		}
	}
	return -1;
}

int CMouseCollision::PickTerrainHeight(const VERTEX_COLOR* _pTerrainVertex, eVertexDirect _eVertexDirect)
{
	TranslationViewspace();

	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	TranslationLocal(&matIdentity);

	const VERTEX_COLOR*	pVertex = _pTerrainVertex;

	float fU, fV, fDist;

	for(int z = 0; z < m_iVertexCountZ - 1; ++z)
	{
		for(int x= 0; x < m_iVertexCountX - 1; ++x)
		{
			int iIndex = z * m_iVertexCountX + x;

			if(D3DXIntersectTri(&pVertex[iIndex + m_iVertexCountX + 1].vPos, 
				&pVertex[iIndex + m_iVertexCountX].vPos,
				&pVertex[iIndex + 1].vPos,
				&m_vPivotPos,
				&m_vRayDir,
				&fU, &fV, &fDist))
			{
				switch(_eVertexDirect)
				{
				case VERTEX_DIRECT_LEFT_UP :
					return iIndex + m_iVertexCountX;					

				case VERTEX_DIRECT_RIGHT_UP :
					return iIndex + m_iVertexCountX + 1;

				case VERTEX_DIRECT_LEFT_DOWN :
					return iIndex;

				case VERTEX_DIRECT_RIGHT_DOWN :
					return iIndex + 1;
				}
			}

			// ¿ÞÂÊ ¾Æ·¡ Æú¸®°ï
			if(D3DXIntersectTri(&pVertex[iIndex].vPos, 
				&pVertex[iIndex + 1].vPos,
				&pVertex[iIndex + m_iVertexCountX].vPos,
				&m_vPivotPos,
				&m_vRayDir,
				&fU, &fV, &fDist))
			{
				switch(_eVertexDirect)
				{
				case VERTEX_DIRECT_LEFT_UP :
					return iIndex + m_iVertexCountX;					

				case VERTEX_DIRECT_RIGHT_UP :
					return iIndex + m_iVertexCountX + 1;

				case VERTEX_DIRECT_LEFT_DOWN :
					return iIndex;

				case VERTEX_DIRECT_RIGHT_DOWN :
					return iIndex + 1;
				}
			}
		}
	}


	return -1;
}


HRESULT	CMouseCollision::Initialize(int _iVertexCountX, int _iVertexCountZ)
{
	m_iVertexCountX = _iVertexCountX;
	m_iVertexCountZ = _iVertexCountZ;

	return S_OK;
}

void CMouseCollision::TranslationViewspace(void)
{
	POINT ptMouse;
	ENGINE::GetInputManager()->GetMousePos(&ptMouse);

	//cout << "X :" << ptMouse.x << endl;
	//cout << "Y :" << ptMouse.y << endl;

	//if(ptMouse.x < 0 || ptMouse.x > 800)
	//	return;

	//if(ptMouse.y > 600 || ptMouse.y < 0)
	//	return;


	D3DXMATRIX	matProj;
	ENGINE::GetDevice()->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXVECTOR3	vTemp;

	vTemp.x = (float(ptMouse.x) / (WINCX >> 1) - 1.f) / matProj._11;
	vTemp.y = (float(-ptMouse.y) / (WINCY >> 1) + 1.f) / matProj._22;
	vTemp.z = 1.f;

	m_vPivotPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_vRayDir = vTemp - m_vPivotPos;

	D3DXVec3Normalize(&m_vRayDir, &m_vRayDir);
}

void CMouseCollision::TranslationLocal(const D3DXMATRIX* _pWorld)
{
	D3DXMATRIX	matView;
	ENGINE::GetDevice()->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matView, NULL, &matView);
	D3DXVec3TransformCoord(&m_vPivotPos, &m_vPivotPos, &matView);
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &matView);

	D3DXMATRIX	matWorld;
	D3DXMatrixInverse(&matWorld, NULL, _pWorld);
	D3DXVec3TransformCoord(&m_vPivotPos, &m_vPivotPos, &matWorld);
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &matWorld);
}

void CMouseCollision::Release(void)
{
	
}
