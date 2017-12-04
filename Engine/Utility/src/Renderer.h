/*!
 * \file Renderer.h
 * \date 2016/05/24 20:37
 *
 * \author 박정민
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 //! 이 친구가 진화해서 렌더매니저 역할을 하거나, 아니면..
 가능한다면 비슷한 renderstate등을 모아서, 그려주는게 좋을 거다..
*/

#ifndef Renderer_h__
#define Renderer_h__

#include "Engine_Include.h"
#include "SmartText.h"

BEGIN_NAMESPACE(ENGINE)
class CScene;
class ENGINE_DLL_SPECIFIER CRenderer
{
	// member variable
private:
	CScene* m_pScene;

	DWORD m_dwFrameCount;
	ENGINE::SMART_TEXT m_FPS;

	// member function
public:
	static CRenderer* Create(void);
	void Render(void);
private:	
	HRESULT Initialize(void);
	void DrawFPS(void);
	void Release(void);

	// getter & setter
public:
	void SetScene(CScene* _pScene);

	// constructor & destructor
private:
	explicit CRenderer(void);
public:
	~CRenderer(void);
MAKE_UNCOPYABLE(CRenderer)
};
END_NAMESPACE

#endif // Renderer_h__