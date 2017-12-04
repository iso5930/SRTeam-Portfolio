#include "stdafx.h"
#include "BillboardObject.h"

#include "Export_Function.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "TerrainCollision.h"
#include "MouseCollision.h"
#include "OBBCollision.h"
#include "Component.h"
#include "Export_Utility.h"
#include "Col_Event_Functors.h"

CBillboardObject::CBillboardObject(eObjectType _eObjectType)
:CGameObject(_eObjectType)
,m_pBuffer(NULL)
,m_pTexture(NULL)
,m_pInfo(NULL)
,m_pTerrainCollision(NULL)
,m_pMouseCollision(NULL)
,m_pOBBCollision(NULL)
{

}

CBillboardObject::~CBillboardObject(void)
{
	Release();
}

CBillboardObject* CBillboardObject::Create(eObjectType _eObjectType, const wstring& _strTextureKey)
{
	CBillboardObject* pInstance = new CBillboardObject(_eObjectType);
	pInstance->SetTextureKey(_strTextureKey);
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CBillboardObject::Update(void)
{
	if (ENGINE::GetBattleManeger()->GetBattleStart())
	{
		m_pInfo->Update();
		D3DXMATRIX matBill;
		ENGINE::GetDevice()->GetTransform(D3DTS_VIEW, &matBill);

		ZeroMemory(matBill.m[3], sizeof(float) * 3);
		D3DXMatrixInverse(&matBill, NULL, &matBill);
		m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;

		return 0;
	}

	ENGINE::CGameObject::Update();
	
	ENGINE::CCharacter* pChar = static_cast<ENGINE::CCharacterGroup*>(ENGINE::GetManagement()->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_SIZZ);
	D3DXVECTOR3 vDist = pChar->GetPos() - m_pInfo->m_vPos;
	float fLength = D3DXVec3Length(&vDist);
	if (fLength <= 1.5f && ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_LBUTTON))
	{
		if (!ENGINE::GetEventManager()->IsSwitchOn(L"stage2_npctalk_finish"))
		{
			m_pMouseCollision->PickObject(m_pOBBCollision->GetOBBInfo(), &m_pInfo->m_matWorld, new CColSwitchOnBill(L"stage2_talk_11"));
		}
		else
		{
			m_pMouseCollision->PickObject(m_pOBBCollision->GetOBBInfo(), &m_pInfo->m_matWorld, new CColSwitchOnBill(L"stage2_talk_15"));
		}
	}
	// functor에 switch 켜는 걸 넣는다.. 대화.. 
	// 플레이어와 거리 확인..


	D3DXMATRIX matBill;
	ENGINE::GetDevice()->GetTransform(D3DTS_VIEW, &matBill);

	ZeroMemory(matBill.m[3], sizeof(float) * 3);
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;

	return 0;
}

void CBillboardObject::Render(void)
{
	ENGINE::GetDevice()->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	LPDIRECT3DDEVICE9 pDevice = ENGINE::GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	int i = SetAngle();
	//cout << i << endl;
	m_pTexture->Render(i);

	//m_pTexture->Render((int)m_pSpriteFrame->GetCurFrame());
	m_pBuffer->Render();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pOBBCollision->Render();
}

HRESULT CBillboardObject::Initialize(void)
{
	HRESULT hr = AddComponent();
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CBillboardObject::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Rectangle_Texture");
	m_pBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Buffer", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, m_strTextureKey);
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Texture", pComponent));

	m_pInfo = ENGINE::CTransform::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", m_pInfo));

	m_pTerrainCollision = ENGINE::CTerrainCollision::Create(this, m_pInfo, new ENGINE::CColStop(m_pInfo, NULL));
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"TerrainCollision", m_pTerrainCollision));

	m_pOBBCollision = ENGINE::COBBCollision::Create(this, m_pInfo, NULL, 0.25f, 0.5f, 0.25f, NULL/*new ENGINE::CColSliding*/);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollision));

	m_pMouseCollision = ENGINE::CMouseCollision::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"MouseCollision", m_pMouseCollision));


	return S_OK;
}

void CBillboardObject::Release(void)
{

}

void CBillboardObject::SetTextureKey(const wstring& _strTextureKey)
{
	m_strTextureKey = _strTextureKey;
}

void CBillboardObject::SetPos(float _fX, float _fZ)
{
	m_pInfo->m_vPos.x = _fX;
	m_pInfo->m_vPos.z = _fZ;
}

int CBillboardObject::SetAngle(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::GetManagement()->GetComponent(L"Camera", L"Transform");
	float fCameraAngle = ((ENGINE::CTransform*)pComponent)->m_pAngle[ANGLE_TYPE_Y];

	D3DXMATRIX matRot;
	D3DXMatrixRotationY(&matRot, fCameraAngle);

	D3DXVECTOR3 vDist = D3DXVECTOR3(0.f, 0.f, -1.f) - m_pInfo->m_vPos;

	vDist.y = 0.f;

	D3DXVec3Normalize(&vDist, &vDist);

	D3DXVECTOR3 vSource(1.f, 0.f, 0.f);

	D3DXVec3TransformNormal(&vSource, &vSource, &matRot);

	float fAngle = D3DXVec3Dot(&vDist, &vSource);

	fAngle = acosf(fAngle);

	D3DXVECTOR3 vDestPos = D3DXVECTOR3(0.f, 0.0, -1.f);
	D3DXVECTOR3 vPos = m_pInfo->m_vPos;

	D3DXMatrixRotationY(&matRot, -fCameraAngle);

	D3DXVec3TransformNormal(&vDestPos, &vDestPos, &matRot);
	D3DXVec3TransformNormal(&vPos, &vPos, &matRot);

	if(vPos.z < vDestPos.z)
	{
		fAngle = 2 * D3DX_PI - fAngle;
	}

	float fSource = 0.f;
	int iIndex = 0;

	fAngle = D3DXToDegree(fAngle);

	for(int i = 1; i < 5; ++i)
	{
		fSource = 90.f * i;

		if(fSource >= fAngle)
		{
			iIndex = i;
			break;
		}
	}

	return (iIndex - 1);
}