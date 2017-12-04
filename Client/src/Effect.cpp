#include "Effect.h"
#include "Transform.h"
#include "Texture.h"
#include "Sprite.h"
#include "Export_Function.h"
#include "Character.h"
#include "Monster.h"

ENGINE::CEffect::CEffect(eObjectType _eObjType)
: CGameObject(_eObjType)
, m_pInfo(NULL)
, m_pSprite(NULL)
{

}

ENGINE::CEffect::~CEffect(void)
{

}

ENGINE::CEffect* ENGINE::CEffect::Create(eObjectType _eObjType, ENGINE::CGameObject* _pOwner, eEffectType _eEffectType, float _fX, float _fY, float _fZ)
{
	CEffect*	pEffect = new CEffect(_eObjType);
	pEffect->SetEffect(_pOwner, _eEffectType, _fX, _fY, _fZ);

	if(FAILED(pEffect->Initialize()))
		SAFE_DELETE(pEffect);	

	return pEffect;
}

HRESULT ENGINE::CEffect::Initialize(void)
{
	ENGINE::CComponent* pComponent = NULL;

	pComponent = ENGINE::CTransform::Create(this);
	m_pInfo = static_cast<ENGINE::CTransform*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", pComponent));

	pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Buffer_Rectangle_Texture");
	m_pVIBuffer = static_cast<ENGINE::CVIBuffer*>(pComponent);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"VIBuffer", pComponent));

	if(m_eEffectType == EFFECT_DAMAGE)
	{
		pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 14.f, 15.f));
		m_pSprite = static_cast<ENGINE::CSprite*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));	

		pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Damage_Effect");
		m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Damage_Effect", pComponent));
	}

	if(m_eEffectType == EFFECT_EXPLOSION)
	{
		pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 24.f, 15.f));
		m_pSprite = static_cast<ENGINE::CSprite*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));

		pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Explosion_Effect");
		m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Explosion_Effect", pComponent));
	}

	m_pInfo->m_vPos = vTemp;

	if(m_eEffectType == EFFECT_GUARD)
	{
		pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 7.f, 8.f));
		m_pSprite = static_cast<ENGINE::CSprite*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));

		pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Explosion_Effect");
		m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Guard_Effect", pComponent));
	}

	if(m_eEffectType == EFFECT_REDPARTICLE)
	{
		pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 40.f, 15.f));
		m_pSprite = static_cast<ENGINE::CSprite*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));

		pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Red_Particle_Effect");
		m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Red_Particle_Effect", pComponent));
	}

	if(m_eEffectType == EFFECT_BLING)
	{
		pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 8.f, 10.f));
		m_pSprite = static_cast<ENGINE::CSprite*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));

		pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Bling_Effect");
		m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Bling_Effect", pComponent));
	}

	if(m_eEffectType == EFFECT_CHARGE)
	{
		pComponent = ENGINE::CSprite::Create(this, FRAME(0.f, 0.f, 0.f));
		m_pSprite = static_cast<ENGINE::CSprite*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"SpriteFrame", pComponent));

		pComponent = ENGINE::GetResourceManager()->CloneResource(this, RESOURCE_TYPE_STATIC, L"Skill_Charge");
		m_pTexture = static_cast<ENGINE::CTexture*>(pComponent);
		m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Skill_Charge", pComponent));

		m_pInfo->m_vScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	}
	return S_OK;
}

int ENGINE::CEffect::Update(void)
{
	if(m_eEffectType == EFFECT_CHARGE)
	{
		if(m_pInfo->m_vScale.x <= 0.8f)
		{
			m_pInfo->m_vScale += D3DXVECTOR3(0.1f, 0.1f, 0.1f) * 10.f * ENGINE::GetTimeDelta();

			CGameObject::Update();

			SetBillboard();

			return 0;
		}
		else
		{
			ENGINE::CCharacter* pCharacter = dynamic_cast<ENGINE::CCharacter*>(m_pOwner);
			ENGINE::CMonster* pMonster = dynamic_cast<ENGINE::CMonster*>(m_pOwner); //혹시 모르니..
			//pCharacter->SetCharge(true); //<- 이런식으로 셋팅....
			pCharacter->SetSkillCharge(true);

			return 1;
		}
	}

	CGameObject::Update();

	SetBillboard();

	if(m_pSprite->GetFrameEnd() == true)
		return 1;

	return 0;
}

void ENGINE::CEffect::Render(void)
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

	m_pTexture->Render((int)m_pSprite->GetCurFrame());
	m_pVIBuffer->Render();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void ENGINE::CEffect::SetEffect(CGameObject* _pOwner, eEffectType _eEffectType, float _fX, float _fY, float _fZ)
{
	m_pOwner = _pOwner;
	vTemp = D3DXVECTOR3(_fX, _fY, _fZ);
	m_eEffectType = _eEffectType;
}

void ENGINE::CEffect::SetBillboard(void)
{
	D3DXMATRIX matBill;
	ENGINE::GetDevice()->GetTransform(D3DTS_VIEW, &matBill);
	ZeroMemory(matBill.m[3], sizeof(float) * 3);
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;
}