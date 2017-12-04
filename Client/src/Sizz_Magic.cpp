#include "stdafx.h"
#include "Sizz_Magic.h"
#include "Transform.h"
#include "Export_Function.h"
#include "Component.h"
#include "Movement.h"
#include "Sprite.h"
#include "Texture.h"
#include "OBBCollision.h"
#include "CollisionFunctors.h"

CSizz_Magic::CSizz_Magic(eObjectType _eObjectType)
: CGameObject(_eObjectType)
, m_pInfo(NULL)
, m_pSprites(NULL)
, m_pMovement(NULL)
, m_pOBBCollsion(NULL)
, m_pCheck(NULL)
, m_pTargetID(NULL)
{

}

CSizz_Magic::~CSizz_Magic(void)
{
	SAFE_DELETE(m_pCheck);
}

CSizz_Magic* CSizz_Magic::Create(eObjectType _eObjectType, ENGINE::CGameObject* _pOwner, eMagicType _eMagicType, D3DXVECTOR3 _vPos, D3DXVECTOR3 _vTagetPos, int _iAtk, CGameObject* _pTarget)
{
	CSizz_Magic*	pMagic = new CSizz_Magic(_eObjectType);

	pMagic->SetMagicType(_eMagicType, _iAtk);

	pMagic->SetTargetID(_pTarget);

	if FAILED(pMagic->Initialize())
		SAFE_DELETE(pMagic);

	D3DXVECTOR3 vPos = _vPos;

	vPos.y += 10.f;

	pMagic->SetMagic(_pOwner, _eMagicType, vPos, _vTagetPos, _iAtk);

	return pMagic;
}

HRESULT CSizz_Magic::Initialize(void)
{
	m_pCheck = new bool;

	(*m_pCheck) = false;

	AddComponent();

	return S_OK;
}

void CSizz_Magic::SetMagic(CGameObject* _pOwner, eMagicType _eMagicType, D3DXVECTOR3 _vPos, D3DXVECTOR3 _vTagetPos, int _iAtk)
{
	m_pOwner = _pOwner;
	m_eMagicType = _eMagicType;
	m_pInfo->m_vPos = _vPos;
	m_vTargetPos = _vTagetPos;
	m_iAtk = _iAtk;

	if(m_eMagicType == MAGIC_METEO || m_eMagicType == MAGIC_NOVA)
	{
		SetMeteoTarget();
	}

	if(m_eMagicType == MAGIC_FIRERAIN)
	{
		m_vTargetPos = m_pInfo->m_vPos;
		m_vTargetPos.y = 0.f;
	}
}

int CSizz_Magic::Update()
{
	if(!ENGINE::GetBattleManeger()->GetBattleStart())
		return 1;

	if((*m_pCheck))
	{	
		ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, this, EFFECT_EXPLOSION, m_pInfo->m_vPos.x, m_pInfo->m_vPos.y, m_pInfo->m_vPos.z);
		ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
		return 1;
	}

	if(ENGINE::GetBattleManeger()->GetTurn())
	{
		m_pInfo->Update();

		SetBillboard();

		return 0;
	}

	if(m_eMagicType == MAGIC_FIREBALL || m_eMagicType == MAGIC_METEO || m_eMagicType == MAGIC_DARK || m_eMagicType == MAGIC_NOVA)
	{
		D3DXVECTOR3 vDist = m_vTargetPos - m_pInfo->m_vPos;

		float fLength = D3DXVec3Length(&vDist);

		if(fLength >= 0.5f)
		{
			m_pMovement->SetMove(true);
		}
		else if(m_pMovement->GetMove() == false)
		{
			ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, this, EFFECT_EXPLOSION, m_vTargetPos.x, m_vTargetPos.y, m_vTargetPos.z);
			ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
			return 1;
		}
		if(m_pInfo->m_vPos.y <= 0.5f) //메테오 전용.?
		{
			ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, this, EFFECT_EXPLOSION, m_pInfo->m_vPos.x, m_pInfo->m_vPos.y, m_pInfo->m_vPos.z);
			ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
			return 1;
		}
	}

	if(m_eMagicType == MAGIC_FIRERAIN)
	{
		D3DXVECTOR3 vDist = m_vTargetPos - m_pInfo->m_vPos;

		float fLength = D3DXVec3Length(&vDist);

		if(fLength >= 0.5f)
		{
			m_pMovement->SetMove(true);
		}
		else if(m_pMovement->GetMove() == false)
		{
			ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, this, EFFECT_EXPLOSION, m_vTargetPos.x, m_vTargetPos.y, m_vTargetPos.z);
			ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
			return 1;
		}
		else if((*m_pCheck))
		{
			ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, this, EFFECT_EXPLOSION, m_vTargetPos.x, m_vTargetPos.y, m_vTargetPos.z);
			ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
			return 1;
		}
	}
 
	CGameObject::Update();

	SetBillboard();

	return 0;
}

void CSizz_Magic::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Rectangle_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));

	pComponent = ENGINE::CMovement::Create(this, m_pInfo, &m_vTargetPos, 7.f); //원래 7.f
	m_pMovement = static_cast<ENGINE::CMovement*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Movement", pComponent));

	if(m_eMagicType == MAGIC_FIREBALL)
	{
		//m_pInfo->m_pAngle[ANGLE_TYPE_Z] = 45;

		pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 20.f, 10.f));
		m_pSprites = static_cast<ENGINE::CSprite*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));

		pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"FireBall");
		m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"FireBall", pComponent));

		pComponent = ENGINE::COBBCollision::Create(this, m_pInfo, m_pMovement, 0.3f, 0.3f, 0.3f, new ENGINE::CColMonsterToSkill(m_pCheck, m_pTargetID, m_iAtk), false);
		m_pOBBCollsion = static_cast<ENGINE::COBBCollision*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollsion));
	}
	else if(m_eMagicType == MAGIC_FIRERAIN)
	{
		pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 8.f, 10.f));
		m_pSprites = static_cast<ENGINE::CSprite*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));
		
		pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"FireRain");
		m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"FireRain", pComponent));

		pComponent = ENGINE::COBBCollision::Create(this, m_pInfo, m_pMovement, 0.3f, 0.3f, 0.3f, new ENGINE::CColMonsterToSkill(m_pCheck, NULL, m_iAtk), false);
		m_pOBBCollsion = static_cast<ENGINE::COBBCollision*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollsion));
	}
	else if(m_eMagicType == MAGIC_METEO)
	{
		pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 16.f, 15.f));
		m_pSprites = static_cast<ENGINE::CSprite*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));

		pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Meteo");
		m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Meteo", pComponent));

		pComponent = ENGINE::COBBCollision::Create(this, m_pInfo, m_pMovement, 0.5f, 0.5f, 0.5f, new ENGINE::CColMonsterToSkill(m_pCheck, NULL, m_iAtk), false);
		m_pOBBCollsion = static_cast<ENGINE::COBBCollision*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollsion));
	}
	else if(m_eMagicType == MAGIC_DARK)
	{
		pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 6.f, 10.f));
		m_pSprites = static_cast<ENGINE::CSprite*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));

		pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Dark");
		m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Dark", pComponent));

		pComponent = ENGINE::COBBCollision::Create(this, m_pInfo, m_pMovement, 0.3f, 0.3f, 0.3f, new ENGINE::CColCharacterToSkill(m_pCheck,  m_pTargetID, m_iAtk), false);
		m_pOBBCollsion = static_cast<ENGINE::COBBCollision*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollsion));
	}
	else if(m_eMagicType == MAGIC_NOVA)
	{
		pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 4.f, 2.f));
		m_pSprites = static_cast<ENGINE::CSprite*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));

		pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Nova");
		m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Nova", pComponent));

		pComponent = ENGINE::COBBCollision::Create(this, m_pInfo, m_pMovement, 0.3f, 0.3f, 0.3f, new ENGINE::CColCharacterToSkill(m_pCheck,  NULL, m_iAtk), false);
		m_pOBBCollsion = static_cast<ENGINE::COBBCollision*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"OBBCollision", m_pOBBCollsion));
	}
}

void CSizz_Magic::SetBillboard(void)
{
	D3DXMATRIX matBill;
	ENGINE::GetDevice()->GetTransform(D3DTS_VIEW, &matBill);
	ZeroMemory(matBill.m[3], sizeof(float) * 3);
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;
}

void CSizz_Magic::Render()
{
	LPDIRECT3DDEVICE9 pDevice = ENGINE::GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pTexture->Render((int)m_pSprites->GetCurFrame());
	m_pVIBuffer->Render();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pOBBCollsion->Render();
}

void CSizz_Magic::SetMagicType(eMagicType _MagicType, int _iAtk)
{
	m_iAtk = _iAtk;
	m_eMagicType = _MagicType;
}

void CSizz_Magic::SetTargetID(CGameObject* _pTarget)
{
	m_pTargetID = _pTarget;
}

void CSizz_Magic::SetMeteoTarget(void)
{
	D3DXVECTOR3 vDir(0.f, -1.f, 0.f);
	D3DXMATRIX matRot;
	D3DXMatrixRotationY(&matRot, D3DXToRadian(-35.f));
	D3DXVec3TransformNormal(&vDir, &vDir, &matRot);
	m_vTargetPos = m_pInfo->m_vPos + vDir * 20.f;
}

ENGINE::CGameObject* CSizz_Magic::GetOwner(void)
{
	return m_pOwner;
}