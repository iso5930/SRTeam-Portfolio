/*!
 * \file Renderer.h
 * \date 2016/05/24 20:37
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 //! �� ģ���� ��ȭ�ؼ� �����Ŵ��� ������ �ϰų�, �ƴϸ�..
 �����Ѵٸ� ����� renderstate���� ��Ƽ�, �׷��ִ°� ���� �Ŵ�..
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