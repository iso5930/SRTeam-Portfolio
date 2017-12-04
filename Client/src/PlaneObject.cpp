#include "stdafx.h"
#include "PlaneObject.h"

#include "Export_Function.h"

CPlaneObject::CPlaneObject(eObjectType _eObjectType, bool _bDraw)
:CGameObject(_eObjectType)
,m_fX(0.f)
,m_fY(0.f)
,m_Color(D3DCOLOR_ARGB(255, 255, 255, 255))
,m_bDraw(_bDraw)
{

}

CPlaneObject::~CPlaneObject(void)
{
	Release();
}

CPlaneObject* CPlaneObject::Create(eObjectType _eObjectType, const wstring& _strTextureKey, bool _bDraw)
{
	CPlaneObject* pInstance = new CPlaneObject(_eObjectType, _bDraw);
	pInstance->SetTextureKey(_strTextureKey);
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CPlaneObject::Update(void)
{
	ENGINE::CGameObject::Update();

	return 0;
}

void CPlaneObject::Render(void)
{
	if (!m_bDraw)
		return;

	ENGINE::GetDevice()->EndScene();
	ENGINE::GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	TEXINFO* pTexInfo =
		ENGINE::GetResourceManager()->GetSpriteTexture(
		RESOURCE_TYPE_DYNAMIC,
		m_strTextureKey,
		0);
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, m_fX, m_fY, 0.f);
	ENGINE::GetSprite()->SetTransform(&matTrans);
	ENGINE::GetSprite()->Draw(pTexInfo->pTexture,
		NULL,
		&D3DXVECTOR3(pTexInfo->ImgInfo.Width / 2.f,
		pTexInfo->ImgInfo.Height / 2.f, 0.f),
		NULL,
		m_Color);

	ENGINE::GetSprite()->End();
	ENGINE::GetDevice()->BeginScene();
}

HRESULT CPlaneObject::Initialize(void)
{
	HRESULT hr = AddComponent();
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CPlaneObject::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	return S_OK;
}

void CPlaneObject::Release(void)
{

}

void CPlaneObject::SetTextureKey(const wstring& _strTextureKey)
{
	m_strTextureKey = _strTextureKey;
}
