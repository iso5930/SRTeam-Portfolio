/*!
 * \file Management.h
 * \date 2016/05/24 20:26
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
//! �� ���������� reference�� ī���س��� �ֵ�,
// client�ʿ��� �����ϴ°� engine�� �ִ� ��ü�� �ƴ϶� reference�� �ִ� ī�Ǻ��ε�,
// client�ʿ��� ������ ���� ����׸� �Ϸ��� �ϸ� ���� engine�� �ִ� ��ü�� �ƴ϶� reference�� �ִ� ī�Ǻ��� ������ �� ����.
// ���� �����س��� ���� ��ü�� ������ �ȵǾ��ְ�, (�����ִ� ī�Ǻ�����) �ٽ� �ε��ϰڽ��ϱ�? ������ �ߴ� ������ �װ��ε�..

#ifndef Management_h__
#define Management_h__

#include "Engine_Include.h"
#include "Renderer.h"

BEGIN_NAMESPACE(ENGINE)
class CScene;
class CGameObject;
class CComponent;
class ENGINE_DLL_SPECIFIER CManagement
{
	DECLARE_SINGLETON(CManagement)

private:
	typedef map<DWORD, CScene*> SCENE_MAP;

	// member variable
private:
	CRenderer* m_pRenderer;
	CScene* m_pScene;

	SCENE_MAP m_SceneMap;

	// member function
public:
	HRESULT InitManagement(void);
	int Update(void);
	void Render(void);
public:
	wstring GetBgmKey(void);
	void	SetBgm(wstring _wstring);

public:
	template <typename T>
	HRESULT ChangeScene(DWORD _dwSceneID, T& _Functor);
private:
	void Release(void);

	// getter & setter
public:
	void PrepareFind(void);
	// �̰� ���ĸ�, ������Ʈ���� ���ɾ���, ������ ������Ʈ�� � ������Ʈ�� �����ϰ� �ִ������� ����..
	// �׷��� � ������Ʈ�� Ư�� ������Ʈ�� �����ִٸ�, �� ������Ʈ�� �ٷ� �̾ƴ� �������ش�..
	// ������Ʈ���� �ش� ���̾� ������, ���������� ������Ʈ�� ���� �ִ��� �ƴ��� Ž�� ��..
	// �׷��� ���� �ִ� �༮�鸸, �ڽ��� ������Ʈ�� �����ش�..
	// ���� ��� ��ȸ�� �����ٸ� null�� ����, ���� ������Ʈ�� �߰����� ���߾ null�� �����߰���.
	// ��ư null ������ �˻��ϸ鼭 while ������, null�� ������ �� Ż�� ó���� ���ָ� �ȴٴ� �Žô�!
	ENGINE::CComponent* GetComponent(const wstring& _strComponentKey);
	// �̰� Ư�� ������Ʈ Ű�� ���� ģ���� �� ��, �ش� ������Ʈ�� �ִ��� ������ �˻����ִ� ����.
	ENGINE::CComponent* GetComponent(const wstring& _strObjectKey, const wstring& _strComponentKey);
	// ������Ʈ �˻�..
	ENGINE::CGameObject* GetGameObject(const wstring& _strObjectKey);

public:
	void	AddGameObject(const wstring& _strObjectKey, DWORD _dwLayerID, ENGINE::CGameObject* _pGameObject);
	// constructor & destructor
private:
	explicit CManagement(void);
	~CManagement(void);
};

template <typename T>
HRESULT CManagement::ChangeScene(DWORD _dwSceneID, T& _Functor)
{
	bool bSceneExist = false;

	SCENE_MAP::iterator iter = m_SceneMap.begin();
	SCENE_MAP::iterator iter_end = m_SceneMap.end();
	for (; iter != iter_end; ++iter)
	{
		//cout << iter->first << " ";
		// ���� ���� id�� ���� ���� �̹� �����߾��ٸ�..
		if (iter->first == _dwSceneID)
		{
			// life count�� 0�̾��ٸ�..
			if (iter->second->GetLifeCount() == 0)
			{
				HRESULT hr = NULL;
				// dynamic resource �ҷ����� dynamic object �����ϴ� �۾� ��ģ��..
				hr = iter->second->LoadDynamicResources();
				//hr = iter->second->CreateDynamicObjects();
			}

			// �ش� scene�� life count�� ȸ����Ų��..
			iter->second->RestoreLifeCount();

			m_pScene = iter->second;
			m_pRenderer->SetScene(m_pScene);
			m_pScene->ResetEvent();

			bSceneExist = true;
			continue;
		}

		// ���� �߰��� ����, ������ ���� ���� �ƴ϶��..
		// life count�� 0�̶��..
		if (iter->second->GetLifeCount() == 0)
		{
			// �޸𸮿��� ������ ���� �� dynamic object, resource�� �����ش�..
			//ENGINE::GetResourceManager()->ReleaseDynamic();
			//iter->second->ReleaseDynamicObject();
		}
		else
		{
			// life count�� 0���� ũ�ٸ�, 1 �ٿ��ش�..
			iter->second->DecreaseLifeCount();
		}
	}
	//cout << endl;

	// scene�� map�� ������� �ʾҴٸ�..
	if (!bSceneExist)
	{
		//_Functor�� �̿��Ͽ� scene�� �����.
		HRESULT hr = _Functor(&m_pScene);
		if FAILED(hr)
			return hr;
		m_SceneMap.insert(SCENE_MAP::value_type(_dwSceneID, m_pScene));

		m_pRenderer->SetScene(m_pScene);
	}

	return S_OK;
}
END_NAMESPACE

#endif // Management_h__