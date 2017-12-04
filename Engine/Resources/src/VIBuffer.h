/*!
 * \file VIBuffer.h
 * \date 2016/05/25 1:12
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 ���� ������ �ƴ� ����.. ������Ÿ�� ������ ������ ���� �� ģ���� ����Ǿ� ������.
 �� �� �Ʒ� ģ������ ������ �ʴ��ĸ�.. �̹� �� ģ������ init�� �� �ڱ� ���� �� �߰�,
 �������� VIBuffer�� �Ȱ��� �ൿ�ϱ� �����̴�. ������ VIBuffer�� �����ϴ� ���� Ŭ��������
 �ܺ� �������̽���� �� ���� Render�ۿ� ����. �״ϱ� �갡 ����Ǿ� ������ �������� �۵��ϴ°�.
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