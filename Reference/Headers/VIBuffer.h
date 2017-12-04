/*!
 * \file VIBuffer.h
 * \date 2016/05/25 1:12
 *
 * \author 박정민
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 순수 가상이 아닌 이유.. 프로토타입 패턴의 구현에 따라 이 친구가 복사되어 나간다.
 왜 그 아래 친구들이 나가지 않느냐면.. 이미 그 친구들은 init할 때 자기 몫을 다 했고,
 나머지는 VIBuffer랑 똑같이 행동하기 때문이다. 실제로 VIBuffer를 포함하는 이하 클래스들은
 외부 인터페이스라고 할 것이 Render밖에 없음. 그니까 얘가 복사되어 나가도 문제없이 작동하는거.
*/

#ifndef VIBuffer_h__
#define VIBuffer_h__

#include "Engine_Include.h"
#include "GraphicResource.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CVIBuffer : public CGraphicResource
{
public:
	enum eBufferType
	{
		BUFFER_TYPE_TRIANGLE_COLOR,
		BUFFER_TYPE_RECTANGLE_COLOR,
		BUFFER_TYPE_CUBE_COLOR,
		BUFFER_TYPE_RECTANGLE_TERRAIN,
		BUFFER_TYPE_TRIANGLE_TEXTURE,
		BUFFER_TYPE_RECTANGLE_TEXTURE,
		BUFFER_TYPE_CUBE_TEXTURE,
		BUFFER_TYPE_WAVE_TEXTURE
	};

	// member variable
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;

	DWORD m_dwVertexSize;
	DWORD m_dwVertexCount;
	DWORD m_dwVertexFVF;
	DWORD m_dwTriangleCount;

	DWORD m_dwIndexSize;
	D3DFORMAT m_IndexFormat;

	// member function
public:
	virtual CGraphicResource* CloneResource(ENGINE::CGameObject* _pOwner);

	virtual void Render(int _iIndex = -1);

	void ReadVerticies(void* _pVerticies) const;
	void WriteVerticies(void* _pVerticies) const;
protected:
	HRESULT Initialize(void);
private:
	void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
protected:
	explicit CVIBuffer(void);
public:
	virtual ~CVIBuffer(void);
};
END_NAMESPACE

#endif // VIBuffer_h__