#include "stdafx.h"
#include "Treasurechest4-1.h"
#include "Transform.h"
#include "RectangleTexture.h"
#include "Export_Function.h"
#include "Texture.h"
#include "Sprite.h"
#include "Character.h"
#include "TerrainInfo.h"
#include "RectangleWave.h"
#include "CharacterGroup.h"
#include "GroupObserver.h"
#include "MouseCollision.h"
#include "Col_Event_Functors.h"
#include "OBBCollision.h"


CTreasurechest4A::CTreasurechest4A(eObjectType _eObjectType)
:Cetc(_eObjectType)
, m_fOpen(0.f)
, m_bOpen(false)
, m_bControl(false)
, m_fSpeed(0.0001f)
, m_fOpenSave(0.f)
{
}

CTreasurechest4A::~CTreasurechest4A()
{
	Release();
}

void CTreasurechest4A::SetDirection(void)
{
}

CTreasurechest4A* CTreasurechest4A::Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos, int iFrame)
{
	CTreasurechest4A*		pTreasurechest4A = new CTreasurechest4A(_eObjectType);

	pTreasurechest4A->Initialize(_vPos, iFrame);

	return pTreasurechest4A;
}

HRESULT CTreasurechest4A::Initialize(void)
{
	return S_OK;
}

HRESULT CTreasurechest4A::Initialize(D3DXVECTOR3 _vPos, int iFrame)
{
	HRESULT hr = AddComponent();
	m_pInfo->m_vScale /= 3.f;
	m_pInfo->m_vScale.y /= 3.f;
	m_pInfo->m_vPos = _vPos;
	m_vPosSave = _vPos;

	m_iFrame = iFrame;

	m_pGroupObserver = ENGINE::CGroupObserver::Create(this);
	ENGINE::GetInfoSubject()->Subscribe(m_pGroupObserver);

	return S_OK;
}

int CTreasurechest4A::Update(void)
{
	float fTimeDelta = ENGINE::GetTimeDelta();

	m_vTagPos = m_pGroupObserver->GetCharacterGroup()->GetLeaderCharacter()->GetInfo()->m_vPos;

	ENGINE::CGameObject::Update();

	ENGINE::CCharacter* pChar = static_cast<ENGINE::CCharacterGroup*>(ENGINE::GetManagement()->GetGameObject(L"CharacterGroup"))->GetCharacter(CHARACTER_SIZZ);
	D3DXVECTOR3 vDist = pChar->GetPos() - m_pInfo->m_vPos;
	float fLength = D3DXVec3Length(&vDist);
	if (fLength <= 2.f && ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_LBUTTON))
	{
		if (!ENGINE::GetEventManager()->IsSwitchOn(L"stage4_box_a_open"))
		{
			m_pMouseCollision->PickObject(m_pOBBCollision->GetOBBInfo(), &m_pInfo->m_matWorld, new CColSwitchOnBill(L"stage4_talk_11"));
		}
		else
		{
			m_pMouseCollision->PickObject(m_pOBBCollision->GetOBBInfo(), &m_pInfo->m_matWorld, new CColSwitchOnBill(L"stage4_talk_12"));
		}
	}

	if(m_iFrame == 1)
	{
		float fRoot = 
			(m_vTagPos.x - m_pInfo->m_vPos.x) * (m_vTagPos.x - m_pInfo->m_vPos.x)
			+ (m_vTagPos.z - m_pInfo->m_vPos.z) * (m_vTagPos.z - m_pInfo->m_vPos.z);
		if(fRoot < 2.f)
			m_bOpen = false;
		else
			m_bOpen = true;

		if(m_pInfo->m_pAngle[ANGLE_TYPE_X] < D3DXToRadian(45.f) && m_bOpen == false)
		{
			m_pInfo->m_pAngle[ANGLE_TYPE_X] += 2.f * fTimeDelta;
		}
		if(m_pInfo->m_pAngle[ANGLE_TYPE_X] > D3DXToRadian(0.f) && m_bOpen == true)
		{
			m_pInfo->m_pAngle[ANGLE_TYPE_X] -= 2.f * fTimeDelta;
		}
		m_fOpenSave = (m_pInfo->m_pAngle[ANGLE_TYPE_X] / D3DXToRadian(45.f));

		m_pInfo->m_vPos.y = m_vPosSave.y + (D3DXToRadian(90.f * (m_fOpenSave / 6.f))) - (m_fOpenSave / 10.f) - 0.05f;
		m_pInfo->m_vPos.z = m_vPosSave.z + (D3DXToRadian(90.f * (m_fOpenSave / 6.f))) - (m_fOpenSave / 10.f);
	}

	return 0;
}	

void CTreasurechest4A::Render(void)
{
	LPDIRECT3DDEVICE9 pDevice = ENGINE::GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	ENGINE::GetDevice()->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pTexture->Render(m_iFrame);
	m_pVIBuffer->Render();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pOBBCollision->Render();
}

void CTreasurechest4A::Release(void)
{
}

HRESULT CTreasurechest4A::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Cube_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_DYNAMIC, L"Treasurechest_Nomal");
	m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Treasurechest_Nomal", pComponent));

	m_pOBBCollision = ENGINE::COBBCollision::Create(this, m_pInfo, NULL, 0.5f, 0.5f, 0.5f, NULL/*new ENGINE::CColSliding*/);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollision));

	m_pMouseCollision = ENGINE::CMouseCollision::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"MouseCollision", m_pMouseCollision));


	return S_OK;
}

void CTreasurechest4A::SetPos(const D3DXVECTOR3& vPos)
{
	m_pInfo->m_vPos = vPos;
}
