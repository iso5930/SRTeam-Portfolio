/*!
 * \file Client_Include.h
 * \date 2016/05/23 20:08
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

#ifndef Client_Include_h__
#define Client_Include_h__

#include "Common_Include.h"

// 메모리 릭 위치 띄워주는.. 그런 코드인건가..
#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

extern HWND g_hWnd;

enum eSceneID
{
	SCENE_ID_LOGO,
	SCENE_ID_MAIN_MENU,
	SCENE_ID_STAGE_1,
	SCENE_ID_STAGE_2,
	SCENE_ID_STAGE_3,
	SCENE_ID_STAGE_4,
	SCENE_ID_STAGE_5,
	SCENE_ID_END
};

extern bool g_bKeyDisable;

#endif // Client_Include_h__