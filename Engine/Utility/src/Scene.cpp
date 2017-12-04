#include "Scene.h"

#include "Layer.h"
#include "Export_Function.h"
#include "GameEvent.h"

ENGINE::CScene::CScene(void)
: m_uLifeCount(SCENE_LIFE)
, m_wstrBgmKey(L"")
{

}

ENGINE::CScene::~CScene(void)
{
	Release();
}

int ENGINE::CScene::Update(void)
{
	//if (!ENGINE::GetInputManager()->GetOnEvent())
	//{
		LAYER_MAP::iterator iter = m_LayerMap.begin();
		LAYER_MAP::iterator iter_end = m_LayerMap.end();
		for (; iter != iter_end; ++iter)
		{
			iter->second->Update();
		}
	//}

	//! event_vec�� ����.. �ڿ��� ����ġ�� �Ѱ�, �� �� �տ��� ����Ǿ�� �Ѵٸ�.. ��������� ���� �ѵ�..

	//! event�� ������ ����, update�� ���ƾ� �ϳ�..
	// �ƴϸ� � ������ ���� �帧�� �������� �ϴ°ǰ�..
	CEventManager::GetInstance()->Update(&m_EventVec);

	return 0;
}

void ENGINE::CScene::Render(void)
{
	LAYER_MAP::iterator iter = m_LayerMap.begin();
	LAYER_MAP::iterator iter_end = m_LayerMap.end();
	for (; iter != iter_end; ++iter)
	{
		iter->second->Render();
	}

	/*if(ENGINE::GetBattleManeger()->GetBattleStart())
	{
		ENGINE::GetBattleManeger()->Render();
	}*/
}

HRESULT ENGINE::CScene::GetStaticObject(CScene* _pScene)
{
	if (!_pScene)
		return S_OK;

	LAYER_MAP::iterator iter = _pScene->m_LayerMap.begin();
	LAYER_MAP::iterator iter_end = _pScene->m_LayerMap.end();

	LAYER_MAP::iterator my_iter = m_LayerMap.begin();
	for (; iter != iter_end; ++iter, ++my_iter)
	{
		my_iter->second->GetStaticObject(iter->second);
	}

	return S_OK;
}

void ENGINE::CScene::ReleaseDynamicObject(void)
{
	LAYER_MAP::iterator iter = m_LayerMap.begin();
	LAYER_MAP::iterator iter_end = m_LayerMap.end();
	for (; iter != iter_end; ++iter)
	{
		iter->second->ReleaseDynamicObject();
	}
}

HRESULT ENGINE::CScene::AddEvent(CGameEvent* _pEvent)
{
	m_EventVec.push_back(_pEvent);

	return S_OK;
}

void ENGINE::CScene::Release(void)
{
	LAYER_MAP::iterator iter = m_LayerMap.begin();
	LAYER_MAP::iterator iter_end = m_LayerMap.end();
	for (; iter != iter_end; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_LayerMap.clear();

	
	unsigned int uEventVecSize = m_EventVec.size();
	for (unsigned int i = 0; i < uEventVecSize; ++i)
	{
		SAFE_DELETE(m_EventVec[i]);
	}
	m_EventVec.clear();
}

void ENGINE::CScene::PrepareFind(void)
{
	m_finder = m_LayerMap.begin();
	m_finder_end = m_LayerMap.end();

	if (m_finder != m_finder_end)
		m_finder->second->PrepareFind();
}

ENGINE::CComponent* ENGINE::CScene::GetComponent(const wstring& _strComponentKey)
{
	for (; m_finder != m_finder_end;)
	{
		ENGINE::CComponent* pComponent = m_finder->second->GetComponent(_strComponentKey);
		if (pComponent != NULL)
			return pComponent;

		++m_finder;
		if (m_finder != m_finder_end)
			m_finder->second->PrepareFind();
	}

	return NULL;
}

ENGINE::CComponent* ENGINE::CScene::GetComponent(const wstring& _strObjectKey, const wstring& _strComponentKey)
{
	ENGINE::CComponent* pComponent = NULL;

	LAYER_MAP::iterator iter = m_LayerMap.begin();
	LAYER_MAP::iterator iter_end = m_LayerMap.end();
	for (; iter != iter_end; ++iter)
	{
		pComponent = iter->second->GetComponent(_strObjectKey, _strComponentKey);
		if (pComponent != NULL)
			return pComponent;
	}

	return NULL;
}

ENGINE::CGameObject* ENGINE::CScene::GetGameObject(const wstring& _strObjectKey)
{
	ENGINE::CGameObject* pObject = NULL;

	LAYER_MAP::iterator iter = m_LayerMap.begin();
	LAYER_MAP::iterator iter_end = m_LayerMap.end();
	for (; iter != iter_end; ++iter)
	{
		pObject = iter->second->GetGameObject(_strObjectKey);
		if (pObject != NULL)
			return pObject;
	}

	return NULL;
}

unsigned int ENGINE::CScene::GetLifeCount(void)
{
	return m_uLifeCount;
}

void ENGINE::CScene::DecreaseLifeCount(void)
{
	--m_uLifeCount;
}

void ENGINE::CScene::RestoreLifeCount(void)
{
	m_uLifeCount = SCENE_LIFE;
}

void ENGINE::CScene::AddGameObject(const wstring& _strObjKey, DWORD _dwLayerID, CGameObject* _pGameObject)
{
	m_LayerMap[_dwLayerID]->AddObject(_strObjKey, _pGameObject);
}

wstring ENGINE::CScene::GetBgmKey(void)
{
	return m_wstrBgmKey;
}

void ENGINE::CScene::SetBgmKey(wstring _wstrBgmKey)
{
	m_wstrBgmKey = _wstrBgmKey;
}

