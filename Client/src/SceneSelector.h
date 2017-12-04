/*!
 * \file SceneSelector.h
 * \date 2016/05/24 21:20
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

#ifndef SceneSelector_h__
#define SceneSelector_h__

#include "Logo.h"
#include "MainMenuScene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
class CScene;
class CSceneSelector
{
	// member variable
private:
	eSceneID m_eSceneID;

	// member function
public:
	HRESULT operator ()(ENGINE::CScene** _ppScene)
	{
		switch (m_eSceneID)
		{
		case SCENE_ID_LOGO:
			*_ppScene = CLogo::Create(*_ppScene);
			break;

		case SCENE_ID_MAIN_MENU:
			*_ppScene = CMainMenuScene::Create(*_ppScene);
			break;

		case SCENE_ID_STAGE_1:
			*_ppScene = CStage1::Create(*_ppScene);
			break;

		case SCENE_ID_STAGE_2:
			*_ppScene = CStage2::Create(*_ppScene);
			break;

		case SCENE_ID_STAGE_3:
			*_ppScene = CStage3::Create(*_ppScene);
			break;

		case SCENE_ID_STAGE_4:
			*_ppScene = CStage4::Create(*_ppScene);
			break;

		case SCENE_ID_STAGE_5:
			*_ppScene = CStage5::Create(*_ppScene);
			break;
		}
		if (*_ppScene == NULL)
			return E_FAIL;

		return S_OK;
	}

	// constructor & destructor
public:
	explicit CSceneSelector(eSceneID _eSceneID)
		:m_eSceneID(_eSceneID)
	{

	}
	~CSceneSelector(void)
	{

	}
};

#endif // SceneSelector_h__