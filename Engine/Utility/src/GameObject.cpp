#include "GameObject.h"

#include "Component.h"
#include "Movement.h"
#include "Transform.h"

ENGINE::CGameObject::CGameObject(eObjectType _eObjectType)
:m_eObjectType(_eObjectType)
{

}

ENGINE::CGameObject::~CGameObject(void)
{
	Release();
}

int ENGINE::CGameObject::Update(void)
{
	COMPONENT_MAP::iterator iter = m_ComponentMap.begin();
	COMPONENT_MAP::iterator iter_end = m_ComponentMap.end();
	for (; iter != iter_end; ++iter)
	{
		iter->second->Update();
	}

	return 0;
}

void ENGINE::CGameObject::Render(void)
{

}

void ENGINE::CGameObject::Release(void)
{
	COMPONENT_MAP::iterator iter = m_ComponentMap.begin();
	COMPONENT_MAP::iterator iter_end = m_ComponentMap.end();
	for (; iter != iter_end; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_ComponentMap.clear();
}

void ENGINE::CGameObject::PrepareFind(void)
{
	m_bAlreadyFound = false;
}

ENGINE::CComponent* ENGINE::CGameObject::GetComponent(const wstring& _strComponentKey)
{
	// 굳이 이 짓을 하는 이유는, layer.cpp에 주절주절 써놨음..
	if (m_bAlreadyFound)
		return NULL;

	COMPONENT_MAP::iterator iter = m_ComponentMap.find(_strComponentKey);
	if (iter == m_ComponentMap.end())
		return NULL;
	else
	{
		m_bAlreadyFound = true;

		return iter->second;
	}
}

eObjectType ENGINE::CGameObject::GetObjectType(void)
{
	return m_eObjectType;
}
