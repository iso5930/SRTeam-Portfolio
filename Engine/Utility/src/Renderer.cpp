#include "Renderer.h"

#include "Scene.h"
#include "Export_Function.h"

ENGINE::CRenderer::CRenderer(void)
:m_pScene(NULL)
,m_dwFrameCount(0)
{

}

ENGINE::CRenderer::~CRenderer(void)
{
	Release();
}

ENGINE::CRenderer* ENGINE::CRenderer::Create(void)
{
	CRenderer* pInstance = new CRenderer;
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	ENGINE::GetTimeManager()->CreateTimer(L"FPSTimer", 1.f);

	return pInstance;
}

void ENGINE::CRenderer::Render(void)
{
	ENGINE::GetDevice()->Clear(
		0,
		NULL,
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 0, 0, 0),
		1.f,
		0);

	ENGINE::GetDevice()->BeginScene();

	m_pScene->Render();

	DrawFPS();

	ENGINE::GetDevice()->EndScene();

	ENGINE::GetDevice()->Present(NULL, NULL, NULL, NULL);
}

HRESULT ENGINE::CRenderer::Initialize(void)
{
	m_FPS.SetPos(650.f, 50.f);

	//! 이걸 어디에..
	ENGINE::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	ENGINE::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//! 왜 이게 없으면 font 제대로 값 채워서 draw 할 때까지 draw가 안됨..
	// 존나 병ㅅ느같네..
	wsprintf(m_FPS.m_szContent, L"FPS : 0");

	return S_OK;
}

void ENGINE::CRenderer::DrawFPS(void)
{
	++m_dwFrameCount;

	if (ENGINE::GetTimer(L"FPSTimer")->CheckRound())
	{
		wsprintf(m_FPS.m_szContent, L"FPS : %d", m_dwFrameCount);
		m_dwFrameCount = 0;
	}

	m_FPS.Draw(D3DCOLOR_ARGB(255, 0, 255, 0));
}

void ENGINE::CRenderer::Release(void)
{
	ENGINE::GetTimeManager()->ReleaseTimer(L"FPSTimer");
}

void ENGINE::CRenderer::SetScene(CScene* _pScene)
{
	m_pScene = _pScene;
}
