/*!
 * \file Scene.h
 * \date 2016/05/24 20:45
 *
 * \author 박정민
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
//! 씬 체인지 구조..
// 씬 넘길 때, layer를 통째로 넘겨주면..
// 플레이어 등이 들어있는 레이어, UI레이어 등..
// 남아있지 않을까?
// 그 이전에 이전 씬의 data 보존해야 하는데,
// 그건 어떻게?
// 메모리에 올려놓는건 편하지만, 결과적으로 문제가..
// 파일입출력으로 넣었다 뺐다? 이걸 해놓는게 가장 속편할 수도 있다..
//! save & load까지 올라가나?
// 그 경우에 uncopyable이 문제를 일으킬수도 있는건가..?

//! return 0가 아닌 객체들, 지울 때 어떻게 지워야 하는가?

#ifndef Scene_h__
#define Scene_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)
class CLayer;
class CGameObject;
class CComponent;
class CGameEvent;
class ENGINE_DLL_SPECIFIER CScene
{
protected:
	wstring		m_wstrBgmKey;

protected:
	typedef map<DWORD, CLayer*> LAYER_MAP;
public:
	typedef vector<CGameEvent*> EVENT_VEC;

	// member variable
protected:
	LAYER_MAP m_LayerMap;

	unsigned int m_uLifeCount;

	// GetComponent Helper
	LAYER_MAP::iterator m_finder;
	LAYER_MAP::iterator m_finder_end;

	// event container..
	EVENT_VEC m_EventVec;

	// member function
public:
	virtual int Update(void);
	virtual void Render(void);

	virtual HRESULT LoadDynamicResources(void) PURE;
	virtual HRESULT CreateDynamicObjects(void) PURE;

	HRESULT GetStaticObject(CScene* _pScene);
	void ReleaseDynamicObject(void);

	HRESULT AddEvent(CGameEvent* _pEvent);
	virtual void ResetEvent(void) PURE;
protected:
	virtual HRESULT Initialize(CScene* _pScene = NULL) PURE;
	virtual void Release(void);

	// getter & setter
public:
	void PrepareFind(void);
	wstring GetBgmKey(void);
	void SetBgmKey(wstring _wstrBgmKey);
	ENGINE::CComponent* GetComponent(const wstring& _strComponentKey);
	ENGINE::CComponent* GetComponent(const wstring& _strObjectKey, const wstring& _strComponentKey);
	ENGINE::CGameObject* GetGameObject(const wstring& _strObjectKey);

	unsigned int GetLifeCount(void);
	void DecreaseLifeCount(void);
	void RestoreLifeCount(void);

public:
	void	AddGameObject(const wstring& _strObjKey, DWORD _dwLayerID, CGameObject* _pGameObject);

	// constructor & destructor
protected:
	explicit CScene(void);
public:
	virtual ~CScene(void) PURE;
MAKE_UNCOPYABLE(CScene)
};
END_NAMESPACE

#endif // Scene_h__