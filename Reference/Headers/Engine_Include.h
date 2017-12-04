/*!
 * \file Engine_Include.h
 * \date 2016/05/23 21:08
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

#ifndef Engine_Include_h__
#define Engine_Include_h__

#include <map>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <io.h>
#include <algorithm>

using std::map;
using std::wstring;
using std::vector;
using std::list;
using std::deque;
//using std::cout;
using std::endl;

#include "fmod.h"
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_errors.h"

#pragma comment (lib, "fmodex_vc.lib")

#include "Common_Include.h"

// 메모리 릭 위치 띄워주는.. 그런 코드인건가..
#if _DEBUG
#ifndef _SR_TOOL
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

#define BEGIN_NAMESPACE(_NamespaceName) namespace _NamespaceName {
#define END_NAMESPACE }

#ifdef ENGINE_EXPORTS
#define ENGINE_DLL_SPECIFIER _declspec(dllexport)
#else
#define ENGINE_DLL_SPECIFIER _declspec(dllimport)
#endif

inline void SetIndex32(INDEX32* _pIndex32, DWORD _dwX, DWORD _dwY, DWORD _dwZ)
{
	_pIndex32->_1 = _dwX;
	_pIndex32->_2 = _dwY;
	_pIndex32->_3 = _dwZ;
}

enum
{
	SCENE_LIFE = 4
};

#endif // Engine_Include_h__