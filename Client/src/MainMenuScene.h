/*!
 * \file MainMenuScene.h
 * \date 2016/05/24 21:14
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

#ifndef MainMenuScene_h__
#define MainMenuScene_h__

#include "Client_Include.h"
#include "Scene.h"

class CMainMenuScene : public ENGINE::CScene	
{
private:
	enum eLayerID
	{
		LAYER_ID_BACK,
		LAYER_ID_UI,
		LAYER_ID_CURSOR
	};

	// member variable
private:
	// -

	// member function
public:
	static CMainMenuScene* Create(CScene* _pScene = NULL);
	virtual int Update(void);
	virtual void Render(void);

	virtual HRESULT LoadDynamicResources(void);
	virtual HRESULT CreateDynamicObjects(void);
	void ResetEvent(void);
private:
	virtual HRESULT Initialize(CScene* _pScene = NULL);
	HRESULT AddObject(void);
	virtual void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CMainMenuScene(void);
public:
	~CMainMenuScene(void);
MAKE_UNCOPYABLE(CMainMenuScene)
};

#endif // MainMenuScene_h__