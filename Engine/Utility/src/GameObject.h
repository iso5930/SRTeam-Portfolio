/*!
 * \file GameObject.h
 * \date 2016/05/29 3:29
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
#ifndef GameObject_h__
#define GameObject_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class CComponent;
class ENGINE_DLL_SPECIFIER CGameObject
{
protected:
	typedef map<wstring, CComponent*> COMPONENT_MAP;

	// member variable
protected:
	COMPONENT_MAP m_ComponentMap;
	const eObjectType m_eObjectType;

	bool m_bAlreadyFound;

	// member function
public:
	virtual int Update(void);
	virtual void Render(void);
protected:
	virtual HRESULT Initialize(void) PURE;
	virtual void Release(void);

	// getter & setter
public:
	virtual void PrepareFind(void);
	virtual ENGINE::CComponent* GetComponent(const wstring& _strComponentKey);

	eObjectType GetObjectType(void);

	// constructor & destructor
protected:
	explicit CGameObject(eObjectType _eObjectType);
public:
	virtual ~CGameObject(void) PURE;
	MAKE_UNCOPYABLE(CGameObject)
};
END_NAMESPACE

#endif // GameObject_h__
