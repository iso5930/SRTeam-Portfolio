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
		UTIL::SHOW_ERROR(L"null ������ �Ű�����", L"�ùٸ� ��ü �����͸� �Է��ϼ���.");
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
			//���� �׷��� ������ �ֱ����ؼ�....
			//������ ����....
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
		//! �ϴ� �Ǵ´�� �غ���..
		// ������Ʈ ����Ʈ�� �״�� �����°�.. �³�?
		// ���� ������Ʈ Ű�� ����. ������Ʈ Ÿ���� �ٸ� �� �ֳ�?
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
			// �̹��ϰ� �ذ��Ϸ��� ����..
			// list_iter�� ���� �Ѱܾ� �ϴ���?
			// list_iter���� group�� ������� ���� �ְ�, �� obj�� ������� ���� ����..
			// ��·��, �� �̻� �� obj�� �Ű澲�� �ʴ� ���� ���� �����, obj�� component�� ���� ���� �ʴٰ� ������ �ִ� ��..
			// Ȥ�� �� �̻� ã�� �ʿ� ���ٴ� '�޼���'�� �����ִ� ��..
			// �׷��� �װ� NULLüũ�� ��. ���� obj�� ���������� iter�� ������ �ʴ��� �� �� �̻� �ڽ��� ã�´ٸ� null�� �����ϰ� ��.
			// �ᱹ obj �ϳ��� ���� �Լ�ȣ���� �ι� �ϰ� �ǰ���..
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
