#include "InfoSubject.h"

IMPLEMENT_SINGLETON(ENGINE::CInfoSubject)

ENGINE::CInfoSubject::CInfoSubject(void)
{

}

ENGINE::CInfoSubject::~CInfoSubject(void)
{
	Release();
}

void ENGINE::CInfoSubject::AddData(int _iMessage, void* _pData)
{
	if (_pData == NULL)
	{
		UTIL::SHOW_ERROR(L"NULL ������ �Է�", L"NULL�� �ƴ� �����͸� �Է��ϼ���!");
		return;
	}

	//! �ߺ� �Է� ����?
	DATA_LIST_MAP::iterator iter = m_DataListMap.find(_iMessage);
	if (iter == m_DataListMap.end())
	{
		m_DataListMap[_iMessage] = DATA_LIST();
	}

	m_DataListMap[_iMessage].push_back(_pData);

	Notify(_iMessage);
}

void ENGINE::CInfoSubject::RemoveData(int _iMessage, void* _pData)
{
	if (_pData == NULL)
	{
		UTIL::SHOW_ERROR(L"NULL ������ �Է�", L"NULL�� �ƴ� �����͸� �Է��ϼ���!");
		return;
	}

	DATA_LIST_MAP::iterator map_iter = m_DataListMap.find(_iMessage);
	if (map_iter != m_DataListMap.end())
	{
		DATA_LIST::iterator list_iter = map_iter->second.begin();
		DATA_LIST::iterator list_iter_end = map_iter->second.end();
		for (; list_iter != list_iter_end; ++list_iter)
		{
			if((*list_iter) == _pData)
			{
				map_iter->second.erase(list_iter);
				return;
			}
			//! list�� �� ��� �̰͵� �׳� map���� �̾Ƴ���?
		}
	}
}

const ENGINE::CInfoSubject::DATA_LIST* ENGINE::CInfoSubject::GetDataList(int _iMessage)
{
	DATA_LIST_MAP::iterator iter = m_DataListMap.find(_iMessage);
	if (iter == m_DataListMap.end())
	{
		return NULL;
	}

	return &iter->second;
}

void ENGINE::CInfoSubject::Release(void)
{
	DATA_LIST_MAP::iterator iter = m_DataListMap.begin();
	DATA_LIST_MAP::iterator iter_end = m_DataListMap.end();
	for (; iter != iter_end; ++iter)
	{
		iter->second.clear();
	}
	m_DataListMap.clear();
}
