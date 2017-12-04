#include "Layer.h"

#include "GameObject.h"

ENGINE::CLayer::CLayer(void)
{

}

ENGINE::CLayer::~CLayer(void)
{
	Release();
}

ENGINE::CLayer* ENGINE::CLayer::Create(void)
{
	return new CLayer;
}

HRESULT ENGINE::CLayer::AddObject(const wstring& _strObjectKey, CGameObject* _pObject)
{
	if (!_pObject)
	{
		UTIL::SHOW_ERROR(L"null 포인터 매개변수", L"올바른 객체 포인터를 입력하세요.");
		return E_FAIL;
	}

	OBJECT_LIST_MAP::iterator iter = m_ObjectListMap.find(_strObjectKey);
	if (iter == m_ObjectListMap.end())
		m_ObjectListMap[_strObjectKey] = OBJECT_LIST();

	m_ObjectListMap[_strObjectKey].push_back(_pObject);

	return S_OK;
}

int ENGINE::CLayer::Update(void)
{
	OBJECT_LIST_MAP::iterator map_iter = m_ObjectListMap.begin();
	OBJECT_LIST_MAP::iterator map_iter_end = m_ObjectListMap.end();

	for (; map_iter != map_iter_end;/* ++map_iter*/)
	{
		OBJECT_LIST::iterator list_iter = map_iter->second.begin();
		OBJECT_LIST::iterator list_iter_end = map_iter->second.end();
		for (; list_iter != list_iter_end;)// ++list_iter)
		{
			if((*list_iter)->Update() == 1)
			{
				SAFE_DELETE(*list_iter);
				list_iter = map_iter->second.erase(list_iter);
			}
			else
				++list_iter;
			//(*list_iter)->Update();
			//몬스터 그룹을 삭제해 주기위해서....
			//문제시 수정....
		}
		if(map_iter->second.size() == 0)
		{
			map_iter = m_ObjectListMap.erase(map_iter);
		}
		else
			++map_iter;
	}

	return 0;
}

void ENGINE::CLayer::Render(void)
{
	OBJECT_LIST_MAP::iterator map_iter = m_ObjectListMap.begin();
	OBJECT_LIST_MAP::iterator map_iter_end = m_ObjectListMap.end();
	for (; map_iter != map_iter_end; ++map_iter)
	{
		OBJECT_LIST::iterator list_iter = map_iter->second.begin();
		OBJECT_LIST::iterator list_iter_end = map_iter->second.end();
		for (; list_iter != list_iter_end; ++list_iter)
		{
			(*list_iter)->Render();
		}
	}
}

void ENGINE::CLayer::GetStaticObject(CLayer* _pLayer)
{
	OBJECT_LIST_MAP::iterator map_iter = _pLayer->m_ObjectListMap.begin();
	OBJECT_LIST_MAP::iterator map_iter_end = _pLayer->m_ObjectListMap.end();
	for (; map_iter != map_iter_end; ++map_iter)
	{
		//! 일단 되는대로 해보자..
		// 오브젝트 리스트를 그대로 들고오는게.. 맞나?
		// 같은 오브젝트 키를 갖고도. 오브젝트 타입이 다를 수 있나?
		if (map_iter->second.front()->GetObjectType() == OBJECT_TYPE_STATIC)
		{
			m_ObjectListMap.insert(OBJECT_LIST_MAP::value_type(map_iter->first, map_iter->second));
		}
	}
}

void ENGINE::CLayer::ReleaseDynamicObject(void)
{
	OBJECT_LIST_MAP::iterator map_iter = m_ObjectListMap.begin();
	OBJECT_LIST_MAP::iterator map_iter_end = m_ObjectListMap.end();
	for (; map_iter != map_iter_end;)
	{
		OBJECT_LIST::iterator list_iter = map_iter->second.begin();
		OBJECT_LIST::iterator list_iter_end = map_iter->second.end();
		for (; list_iter != list_iter_end;)
		{
			if ((*list_iter)->GetObjectType() == OBJECT_TYPE_DYNAMIC)
			{
				SAFE_DELETE(*list_iter);
				list_iter = map_iter->second.erase(list_iter);
			}
			else
			{
				++list_iter;
			}
		}

		if (map_iter->second.empty())
		{
			map_iter = m_ObjectListMap.erase(map_iter);
		}
		else
		{
			++map_iter;
		}
	}
}

void ENGINE::CLayer::Release(void)
{
	OBJECT_LIST_MAP::iterator map_iter = m_ObjectListMap.begin();
	OBJECT_LIST_MAP::iterator map_iter_end = m_ObjectListMap.end();
	for (; map_iter != map_iter_end; ++map_iter)
	{
		OBJECT_LIST::iterator list_iter = map_iter->second.begin();
		OBJECT_LIST::iterator list_iter_end = map_iter->second.end();
		for (; list_iter != list_iter_end; ++list_iter)
		{
			SAFE_DELETE(*list_iter);
		}
		map_iter->second.clear();
	}
	m_ObjectListMap.clear();
}

void ENGINE::CLayer::PrepareFind(void)
{
	m_map_finder = m_ObjectListMap.begin();
	m_map_finder_end = m_ObjectListMap.end();

	if (m_map_finder != m_map_finder_end)
	{
		m_list_finder = m_map_finder->second.begin();
		m_list_finder_end = m_map_finder->second.end();

		if (m_list_finder != m_list_finder_end)
			(*m_list_finder)->PrepareFind();
	}
}

ENGINE::CComponent* ENGINE::CLayer::GetComponent(const wstring& _strComponentKey)
{
	for (; m_map_finder != m_map_finder_end;)
	{
		for (; m_list_finder != m_list_finder_end;)
		{
			// 미묘하게 해결하려는 것이..
			// list_iter를 언제 넘겨야 하느냐?
			// list_iter에는 group이 들어있을 수도 있고, 걍 obj가 들어있을 수도 있음..
			// 어쨌든, 더 이상 이 obj에 신경쓰지 않는 가장 좋은 방법은, obj가 component를 갖고 있지 않다고 보장해 주는 것..
			// 혹은 더 이상 찾을 필요 없다는 '메세지'를 보내주는 것..
			// 그래서 그걸 NULL체크로 봄. 따라서 obj는 내부적으로 iter를 돌리지 않더라도 두 번 이상 자신을 찾는다면 null을 리턴하게 됨.
			// 결국 obj 하나에 대해 함수호출을 두번 하게 되겠지..
			ENGINE::CComponent* pComponent = (*m_list_finder)->GetComponent(_strComponentKey);
			if (pComponent != NULL)
				return pComponent;

			++m_list_finder;
			if (m_list_finder != m_list_finder_end)
				(*m_list_finder)->PrepareFind();
		}

		++m_map_finder;
		if (m_map_finder != m_map_finder_end)
		{
			m_list_finder = m_map_finder->second.begin();
			m_list_finder_end = m_map_finder->second.end();

			if (m_list_finder != m_list_finder_end)
				(*m_list_finder)->PrepareFind();
		}
	}

	return NULL;
}

ENGINE::CComponent* ENGINE::CLayer::GetComponent(const wstring& _strObjectKey, const wstring& _strComponentKey)
{
	ENGINE::CComponent* pComponent = NULL;

	OBJECT_LIST_MAP::iterator map_iter = m_ObjectListMap.find(_strObjectKey);
	if (map_iter == m_ObjectListMap.end())
		return NULL;

	OBJECT_LIST::iterator list_iter = map_iter->second.begin();
	OBJECT_LIST::iterator list_iter_end = map_iter->second.end();
	for (; list_iter != list_iter_end; ++list_iter)
	{
		(*list_iter)->PrepareFind();
		pComponent = (*list_iter)->GetComponent(_strComponentKey);
		if (pComponent != NULL)
			return pComponent;
	}

	return NULL;
}

ENGINE::CGameObject* ENGINE::CLayer::GetGameObject(const wstring& _strObjectKey)
{
	ENGINE::CGameObject* pComponent = NULL;

	OBJECT_LIST_MAP::iterator map_iter = m_ObjectListMap.find(_strObjectKey);
	if (map_iter == m_ObjectListMap.end())
		return NULL;

	return map_iter->second.front();
}
