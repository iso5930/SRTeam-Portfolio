/*!
 * \file Tool_Include.h
 * \date 2016/06/01 19:18
 *
 * \author ¼­ÇÏ´Ã
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Tool_Include_h__
#define Tool_Include_h__

#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using std::wstring;
using std::cout;
using std::endl;

#include "Common_Include.h"

enum eVertexDirect
{
	VERTEX_DIRECT_LEFT_UP,
	VERTEX_DIRECT_LEFT_DOWN,
	VERTEX_DIRECT_RIGHT_UP,
	VERTEX_DIRECT_RIGHT_DOWN
};


extern HWND g_hWnd;

#endif // Tool_Include_h__