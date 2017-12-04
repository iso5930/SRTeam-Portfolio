#include "MouseCursor.h"

#include "CollisionFunctors.h"

ENGINE::CMouseCursor::CMouseCursor(eObjectType _eObjectType)
:CGameObject(_eObjectType)
,m_fClosest(FLT_MAX)
,m_pColFunctor(NULL)
{

}

ENGINE::CMouseCursor::~CMouseCursor(void)
{

}

ENGINE::CMouseCursor* ENGINE::CMouseCursor::Create(eObjectType _eObjectType)
{
	CMouseCursor* pInstance = new CMouseCursor(_eObjectType);
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int ENGINE::CMouseCursor::Update(void)
{
	if (m_pColFunctor)
		(*m_pColFunctor)(NULL, NULL);

	m_fClosest = FLT_MAX;
	SAFE_DELETE(m_pColFunctor);

	return 0;
}

void ENGINE::CMouseCursor::Render(void)
{
	ENGINE::GetDevice()->EndScene();
	ENGINE::GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	TEXINFO* pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"Mouse_Cur", 0);

	D3DXMATRIX matTrans;

	D3DXVECTOR3 vPos;

	ENGINE::GetInputManager()->GetMousePos(&vPos);

	D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);

	ENGINE::GetSprite()->SetTransform(&matTrans);

	//float fX = pTexInfo->ImgInfo.Width / 2.f;
	//float fY = pTexInfo->ImgInfo.Height / 2.f;
	
	//fX -= 15;
	//fY -= 15;

	ENGINE::GetSprite()->Draw(pTexInfo->pTexture, NULL, &D3DXVECTOR3(0.f, 0.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	ENGINE::GetSprite()->End();
	ENGINE::GetDevice()->BeginScene();
	// cursor image draw
}

HRESULT ENGINE::CMouseCursor::Initialize(void)
{
	ShowCursor(FALSE);
	return S_OK;
}

void ENGINE::CMouseCursor::Release(void)
{

}

float ENGINE::CMouseCursor::GetClosestDist(void)
{
	return m_fClosest;
}

void ENGINE::CMouseCursor::SetPickingInfo(float _fClosest, CCollisionFunctor* _pColFunctor)
{
	m_fClosest = _fClosest;
	if (m_pColFunctor)
		SAFE_DELETE(m_pColFunctor);
	m_pColFunctor = _pColFunctor;
}
