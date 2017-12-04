/*!
 * \file Management.h
 * \date 2016/05/24 20:26
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
//! 이 페이지같이 reference로 카피해놓는 애들,
// client쪽에서 참조하는건 engine에 있는 본체가 아니라 reference에 있는 카피본인데,
// client쪽에서 에러가 나서 디버그를 하려고 하면 가끔 engine에 있는 본체가 아니라 reference에 있는 카피본이 열리는 것 같다.
// 실컷 수정해놓고 보니 본체는 수정이 안되어있고, (열려있는 카피본에서) 다시 로드하겠습니까? 따위가 뜨는 이유가 그거인듯..

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
	// 이게 뭐냐면, 오브젝트에는 관심없고, 순전히 오브젝트가 어떤 컴포넌트를 소유하고 있는지에만 관심..
	// 그래서 어떤 오브젝트가 특정 컴포넌트를 갖고있다면, 그 컴포넌트를 바로 뽑아다 리턴해준다..
	// 오브젝트들은 해당 레이어 내에서, 순차적으로 컴포넌트를 갖고 있는지 아닌지 탐색 들어감..
	// 그래서 갖고 있는 녀석들만, 자신의 컴포넌트를 내어준다..
	// 만약 모든 순회가 끝난다면 null을 리턴, 전혀 컴포넌트를 발견하지 못했어도 null을 리턴했겠지.
	// 여튼 null 리턴을 검사하면서 while 돌리고, null이 들어왔을 때 탈출 처리만 해주면 된다는 거시다!
	ENGINE::CComponent* GetComponent(const wstring& _strComponentKey);
	// 이건 특정 오브젝트 키를 가진 친구를 딱 찝어서, 해당 컴포넌트가 있는지 없는지 검사해주는 버전.
	ENGINE::CComponent* GetComponent(const wstring& _strObjectKey, const wstring& _strComponentKey);
	// 오브젝트 검사..
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
		// 만약 같은 id를 갖는 씬이 이미 존재했었다면..
		if (iter->first == _dwSceneID)
		{
			// life count가 0이었다면..
			if (iter->second->GetLifeCount() == 0)
			{
				HRESULT hr = NULL;
				// dynamic resource 불러오고 dynamic object 생성하는 작업 거친다..
				hr = iter->second->LoadDynamicResources();
				//hr = iter->second->CreateDynamicObjects();
			}

			// 해당 scene의 life count를 회복시킨다..
			iter->second->RestoreLifeCount();

			m_pScene = iter->second;
			m_pRenderer->SetScene(m_pScene);
			m_pScene->ResetEvent();

			bSceneExist = true;
			continue;
		}

		// 현재 발견한 씬이, 변경할 다음 씬이 아니라면..
		// life count가 0이라면..
		if (iter->second->GetLifeCount() == 0)
		{
			// 메모리에서 내리지 말고 씬 dynamic object, resource만 지워준다..
			//ENGINE::GetResourceManager()->ReleaseDynamic();
			//iter->second->ReleaseDynamicObject();
		}
		else
		{
			// life count가 0보다 크다면, 1 줄여준다..
			iter->second->DecreaseLifeCount();
		}
	}
	//cout << endl;

	// scene이 map에 들어있지 않았다면..
	if (!bSceneExist)
	{
		//_Functor를 이용하여 scene을 만든다.
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