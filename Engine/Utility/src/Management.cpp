#include "Management.h"

#include "Renderer.h"
#include "Scene.h"

#include "Export_Function.h"

IMPLEMENT_SINGLETON(ENGINE::CManagement)

ENGINE::CManagement::CManagement(void)
:m_pRenderer(NULL)
,m_pScene(NULL)
{

}

ENGINE::CManagement::~CManagement(void)
{
	Release();
}

HRESULT ENGINE::CManagement::InitManagement(void)
{
	m_pRenderer = CRenderer::Create();
	if (m_pRenderer == NULL)
		return E_FAIL;

	return S_OK;
}

int ENGINE::CManagement::Update(void)
{
	m_pScene->Update();

	return 0;
}

void ENGINE::CManagement::Render(void)
{
	m_pRenderer->Render();
}

void ENGINE::CManagement::Release(void)
{
	SAFE_DELETE(m_pRenderer);
	SAFE_DELETE(m_pScene);
}

void ENGINE::CManagement::PrepareFind(void)
{
	m_pScene->PrepareFind();
}

ENGINE::CComponent* ENGINE::CManagement::GetComponent(const wstring& _strComponentKey)
{
	return m_pScene->GetComponent(_strComponentKey);
}

ENGINE::CComponent* ENGINE::CManagement::GetComponent(const wstring& _strObjectKey, const wstring& _strComponentKey)
{
	return m_pScene->GetComponent(_strObjectKey, _strComponentKey);
}

ENGINE::CGameObject* ENGINE::CManagement::GetGameObject(const wstring& _strObjectKey)
{
	return m_pScene->GetGameObject(_strObjectKey);
}

void ENGINE::CManagement::AddGameObject(const wstring& _strObjectKey, DWORD _dwLayerID, ENGINE::CGameObject* _pGameObject)
{
	m_pScene->AddGameObject(_strObjectKey, _dwLayerID, _pGameObject);
}

wstring ENGINE::CManagement::GetBgmKey(void)
{
	return m_pScene->GetBgmKey();
}

void ENGINE::CManagement::SetBgm(wstring _wstring)
{
	TCHAR szTemp[MAX_PATH];
	lstrcpy(szTemp, _wstring.c_str());
	ENGINE::GetSoundManager()->PlayBGM(szTemp);
}
