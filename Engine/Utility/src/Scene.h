/*!
 * \file Scene.h
 * \date 2016/05/24 20:45
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
//! �� ü���� ����..
// �� �ѱ� ��, layer�� ��°�� �Ѱ��ָ�..
// �÷��̾� ���� ����ִ� ���̾�, UI���̾� ��..
// �������� ������?
// �� ������ ���� ���� data �����ؾ� �ϴµ�,
// �װ� ���?
// �޸𸮿� �÷����°� ��������, ��������� ������..
// ������������� �־��� ����? �̰� �س��°� ���� ������ ���� �ִ�..
//! save & load���� �ö󰡳�?
// �� ��쿡 uncopyable�� ������ ����ų���� �ִ°ǰ�..?

//! return 0�� �ƴ� ��ü��, ���� �� ��� ������ �ϴ°�?

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