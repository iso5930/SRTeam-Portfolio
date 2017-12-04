#include "StdAfx.h"
#include "BackGround.h"
#include "Device.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "ResourceManager.h"
#include "GraphicDevice.h"
#include "Pipeline.h"
#include "GameObject.h"
#include "StaticCamera.h"
#include "Transform.h"
#include "TimeManager.h"
#include "Export_Function.h"
#include "MouseCollision.h"
#include "TileTerrain.h"
#include "RectangleTerrain.h"
#include "RectangleTexture.h"

CBackGround::CBackGround(void)
: m_bTerrainFix(true)
, m_bTextureFix(false)
, m_pStaticCamera(NULL)
, m_pGameObject(NULL)
, m_iTextureIndex(1)
, m_bCreateTerrain(false)
, m_eVertexDirect(VERTEX_DIRECT_LEFT_DOWN)
, m_eTextureRotation(TEXTURE_ROTATION_UP)
, m_fHeightValue(0.1f)
, m_pVertexTexture(NULL)
, m_pMouseCollision(NULL)
{
}

CBackGround::~CBackGround(void)
{
	Release();
}


void CBackGround::SetMainView(CToolView* _pView)
{
	m_pMainView = _pView;
}

void CBackGround::Initialize(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(NULL); //! game object 포인터 들어갈 자리에.. 이런게 몇개 있다..
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
}

void CBackGround::Update(void)
{
	KeyCheck();

	ENGINE::CPipeline::MakeWorldMatrix(
		&m_pInfo->m_matWorld,
		&D3DXVECTOR3(1.f, 1.f, 1.f),
		m_pInfo->m_pAngle,
		&m_pInfo->m_vPos);

	SetDirection();
}

void CBackGround::Render(void)
{

	ENGINE::CComponent*		pComponent = NULL;

	ENGINE::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	

	if(m_pMainView->m_wstrTerrainKey != L"")
	{
		if(m_bTerrainFix)
		{
			ENGINE::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			pComponent = ENGINE::GetResourceManager()->CloneResource(NULL, RESOURCE_TYPE_DYNAMIC,	m_pMainView->m_wstrTerrainKey);
			dynamic_cast<ENGINE::CVIBuffer*>(pComponent)->Render();
		}

		if(m_bTextureFix)
		{
			ENGINE::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			ENGINE::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			m_pGameObject = m_pMainView->m_pGameObject;
			m_pVertexTexture = dynamic_cast<CTileTerrain*>(m_pGameObject)->m_pVertexTexture;
			m_pGameObject->Render();
			SetTextureHeight();

		}
	}

}

void CBackGround::Release(void)
{
	if(m_pMouseCollision != NULL)
		SAFE_DELETE(m_pMouseCollision);

	/*if(m_pGameObject != NULL)
		SAFE_DELETE(m_pGameObject);*/

	SAFE_DELETE(m_pInfo);
}

void CBackGround::KeyCheck(void)
{
	float fElapsedTime = ENGINE::GetTimeDelta();
	int iTileIndex = -1;
	int iVertexIndex = -1;

	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_UP))
		m_pInfo->m_vPos += m_pInfo->m_vDir * 10 * fElapsedTime;
	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_DOWN))
		m_pInfo->m_vPos -= m_pInfo->m_vDir * 10 * fElapsedTime;

	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_LEFT))
		m_pInfo->m_pAngle[ANGLE_TYPE_Y] -= D3DXToRadian(10.f) * 10 * fElapsedTime;
	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_RIGHT))
		m_pInfo->m_pAngle[ANGLE_TYPE_Y] += D3DXToRadian(10.f) * 10 * fElapsedTime;

	if(ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
	{
		POINT ptMouse;
		ENGINE::GetInputManager()->GetMousePos(&ptMouse);

		//cout << "X :" << ptMouse.x << endl;
		//cout << "Y :" << ptMouse.y << endl;

		if(ptMouse.x < 0 || ptMouse.x > 800)
			return;

		if(ptMouse.y > 600 || ptMouse.y < 0)
			return;

		//타일 텍스쳐 변경
		if(m_pGameObject != NULL && m_bTextureFix == true)
		{
			/*const*/ VERTEX_TEXTURE* vTemp = dynamic_cast<CTileTerrain*>(m_pGameObject)->m_pVertexTexture;
			iTileIndex = m_pMouseCollision->PickTerrainTexture(vTemp);

			if(iTileIndex == -1)
				return;

			dynamic_cast<CTileTerrain*>(m_pGameObject)->SetTileTexture(iTileIndex, m_iTextureIndex, m_eTextureRotation);
		}

		//높이 값 조정.
		if(m_bCreateTerrain == true && m_bTerrainFix == true)
		{	
			iVertexIndex = m_pMouseCollision->PickTerrainHeight(m_pVertexColor, m_eVertexDirect);

			if(iVertexIndex == -1)
				return;

			m_pVertexColor[iVertexIndex].vPos.y += m_fHeightValue;
			SetVertexColorHeight(iVertexIndex);
		}
	}

	//오른쪽 마우스 높이 값 조정
	if(ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_RBUTTON))
	{
		if(m_bCreateTerrain == true && m_bTerrainFix == true)
		{	
			iVertexIndex = m_pMouseCollision->PickTerrainHeight(m_pVertexColor, m_eVertexDirect);

			if(iVertexIndex == -1)
				return;

			m_pVertexColor[iVertexIndex].vPos.y -= m_fHeightValue;
			SetVertexColorHeight(iVertexIndex);
		}
	}
}

void CBackGround::SetCollsionMouse(int _iVertexCountX, int _iVertexCountZ)
{
	m_pMouseCollision = CMouseCollision::Create(NULL, _iVertexCountX, _iVertexCountZ);
}

void CBackGround::SetDirection(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &D3DXVECTOR3(0.f, 0.f, 1.f), &m_pInfo->m_matWorld);
	D3DXVec3Normalize(&m_pInfo->m_vDir, &m_pInfo->m_vDir);
}

void CBackGround::SetReadVertexColor(int _iCountX, int _iCountZ, wstring _wstrKey)
{
	m_pVertexColor = new VERTEX_COLOR[_iCountX * _iCountZ];
	ENGINE::GetResourceManager()->ReadVerticies(RESOURCE_TYPE_DYNAMIC, _wstrKey.c_str(), m_pVertexColor);
}

void CBackGround::SetVertexColorHeight(int iVertexIndex)
{
	ENGINE::CComponent*		pComponent = NULL;
	pComponent = ENGINE::GetResourceManager()->CloneResource(NULL, RESOURCE_TYPE_DYNAMIC,	m_pMainView->m_wstrTerrainKey);
	ENGINE::CRectangleTerrain* pTemp = ((ENGINE::CRectangleTerrain*)(pComponent));

	pTemp->WriteVerticies(m_pVertexColor);
}

void CBackGround::SetTextureHeight(void)
{
	DWORD dwCountX, dwCountZ;
	int iIndex = 0;
	int iIndex2 = 0;
	dwCountX = dynamic_cast<CTileTerrain*>(m_pGameObject)->m_iCountX;
	dwCountZ = dynamic_cast<CTileTerrain*>(m_pGameObject)->m_iCountZ;
	ENGINE::CRectangleTexture* pRcTex;

	for(DWORD z = 0; z < dwCountZ - 1; ++z)
	{
		for(DWORD x = 0; x < dwCountX - 1; ++x)
		{
			iIndex = z * dwCountX + x;
			iIndex2 = z * (dwCountX - 1) + x;

			VERTEX_TEXTURE*	pTileVertex = new VERTEX_TEXTURE[4];
			VERTEX_TEXTURE* pTemp = dynamic_cast<CTileTerrain*>(m_pGameObject)->m_vecTile[iIndex2]->m_pVertex;

			pTemp[0].vPos.y = m_pVertexColor[iIndex + dwCountX].vPos.y;

			pTemp[1].vPos.y = m_pVertexColor[iIndex + dwCountX + 1].vPos.y;
			
			pTemp[2].vPos.y = m_pVertexColor[iIndex + 1].vPos.y;

			pTemp[3].vPos.y = m_pVertexColor[iIndex].vPos.y;

			SAFE_DELETE(pTileVertex);

			pRcTex = dynamic_cast<CTileTerrain*>(m_pGameObject)->m_vecTile[iIndex2]->m_pRcTex;
			pRcTex->WriteVerticies(pTemp);
		}
	}
}

void CBackGround::SetTextureHeight(int _iCountX, int _iCountZ)
{
	DWORD dwCountX, dwCountZ;
	int iIndex = 0;
	int iIndex2 = 0;
	dwCountX = _iCountX;
	dwCountZ = _iCountZ;
//	ENGINE::CRectangleTexture* pRcTex;

	m_pGameObject = m_pMainView->m_pGameObject;

	for(DWORD z = 0; z < dwCountZ - 1; ++z)
	{
		for(DWORD x = 0; x < dwCountX - 1; ++x)
		{
			iIndex = z * dwCountX + x;
			iIndex2 = z * (dwCountX - 1) + x;

			VERTEX_TEXTURE*	pTileVertex = new VERTEX_TEXTURE[4];
			VERTEX_TEXTURE* pTemp = dynamic_cast<CTileTerrain*>(m_pGameObject)->m_vecTile[iIndex2]->m_pVertex;

			pTemp[0].vPos.y = m_pVertexColor[iIndex + dwCountX].vPos.y;

			pTemp[1].vPos.y = m_pVertexColor[iIndex + dwCountX + 1].vPos.y;

			pTemp[2].vPos.y = m_pVertexColor[iIndex + 1].vPos.y;

			pTemp[3].vPos.y = m_pVertexColor[iIndex].vPos.y;

			//pRcTex = dynamic_cast<CTileTerrain*>(m_pGameObject)->m_vecTile[iIndex2]->m_pRcTex;
			//pRcTex->WriteVerticies(pTemp);
		}
	}
}

