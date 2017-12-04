/*!
 * \file Layer.h
 * \date 2016/05/29 2:56
 *
 * \author ¹ÚÁ¤¹Î
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Layer_h__
#define Layer_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class CGameObject;
class CComponent;
class ENGINE_DLL_SPECIFIER CLayer
{
private:
	typedef list<CGameObject*> OBJECT_LIST;
	typedef map<wstring, OBJECT_LIST> OBJECT_LIST_MAP;

	// member variable
private:
	OBJECT_LIST_MAP m_ObjectListMap;

	// getcomponent helper
	OBJECT_LIST_MAP::iterator m_map_finder;
	OBJECT_LIST_MAP::iterator m_map_finder_end;

	OBJECT_LIST::iterator m_list_finder;
	OBJECT_LIST::iterator m_list_finder_end;

	// member function
public:
	static CLayer* Create(void);
	HRESULT AddObject(const wstring& _strObjectKey, CGameObject* _pObject);
	int Update(void);
	void Render(void);

	void GetStaticObject(CLayer* _pLayer);
	void ReleaseDynamicObject(void);
private:
	void Release(void);

	// getter & setter
public:
	void PrepareFind(void);
	ENGINE::CComponent* GetComponent(const wstring& _strComponentKey);
	ENGINE::CComponent* GetComponent(const wstring& _strObjectKey, const wstring& _strComponentKey);
	ENGINE::CGameObject* GetGameObject(const wstring& _strObjectKey);

	// constructor & destructor
private:
	explicit CLayer(void);
public:
	~CLayer(void);
	MAKE_UNCOPYABLE(CLayer)
};
END_NAMESPACE

#endif // Layer_h__