#include "stdafx.h"
#include "Talkbox.h"

#include "Export_Function.h"
#include "PlaneObject.h"

CTalkbox::CTalkbox(eObjectType _eObjectType)
:CGameObject(_eObjectType)
,m_bDraw(false)
{

}

CTalkbox::~CTalkbox(void)
{
	Release();
}

CTalkbox* CTalkbox::Create(eObjectType _eObjectType, ENGINE::SMART_TEXT& _pText, CPlaneObject* _pTalkbox, CPlaneObject* _pTalkersFace /*= NULL*/)
{
	CTalkbox* pInstance = new CTalkbox(_eObjectType);
	HRESULT hr = pInstance->Initialize(_pText, _pTalkbox, _pTalkersFace);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CTalkbox::Update(void)
{
	ENGINE::CGameObject::Update();

	return 0;
}

void CTalkbox::Render(void)
{
	if (!m_bDraw)
		return;

	if (m_pTalkersFace)
		m_pTalkersFace->Render();
	m_pTalkbox->Render();
	m_Text.TalkboxDraw(D3DCOLOR_ARGB(255, 0, 0, 0));
}

HRESULT CTalkbox::Initialize(ENGINE::SMART_TEXT& _pText, CPlaneObject* _pTalkbox, CPlaneObject* _pTalkersFace /*= NULL*/)
{
	m_Text = _pText;
	m_pTalkbox = _pTalkbox;
	m_pTalkersFace = _pTalkersFace;
	HRESULT hr = AddComponent();
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT CTalkbox::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	return S_OK;
}

void CTalkbox::Release(void)
{

}
