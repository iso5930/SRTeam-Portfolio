#include "VIBuffer.h"

#include "Export_Function.h"

ENGINE::CVIBuffer::CVIBuffer(void)
:m_pVertexBuffer(NULL)
,m_pIndexBuffer(NULL)
,m_dwVertexSize(0)
,m_dwVertexCount(0)
,m_dwVertexFVF(0)
,m_dwTriangleCount(0)
,m_dwIndexSize(0)
{

}

ENGINE::CVIBuffer::~CVIBuffer(void)
{
	Release();
}

ENGINE::CGraphicResource* ENGINE::CVIBuffer::CloneResource(ENGINE::CGameObject* _pOwner)
{
	++(*m_pReferenceCount);

	CVIBuffer* pInstance = new CVIBuffer(*this);
	pInstance->SetOwner(_pOwner);
	return pInstance;
}

void ENGINE::CVIBuffer::Render(int _iIndex /*= -1*/)
{
	// 스트림 소스를 버텍스 버퍼와 연결하여 버퍼의 기하정보를 렌더링 파이프라인에 보낼 수 있도록 한다..
	ENGINE::GetDevice()->SetStreamSource(
		0,
		m_pVertexBuffer,
		0,
		m_dwVertexSize);

	ENGINE::GetDevice()->SetFVF(m_dwVertexFVF);

	ENGINE::GetDevice()->SetIndices(m_pIndexBuffer);

	ENGINE::GetDevice()->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		0,
		m_dwVertexCount,
		0,
		m_dwTriangleCount);
}	

void ENGINE::CVIBuffer::ReadVerticies(void* _pVerticies) const
{
	void* pOriginalVerticies = NULL;
	m_pVertexBuffer->Lock(0, 0, &pOriginalVerticies, 0);

	memcpy(_pVerticies, pOriginalVerticies, m_dwVertexSize * m_dwVertexCount);

	m_pVertexBuffer->Unlock();
}

void ENGINE::CVIBuffer::WriteVerticies(void* _pVerticies) const
{
	void* pOriginalVerticies = NULL;
	m_pVertexBuffer->Lock(0, 0, &pOriginalVerticies, 0);

	memcpy(pOriginalVerticies, _pVerticies, m_dwVertexSize * m_dwVertexCount);

	m_pVertexBuffer->Unlock();
}

HRESULT ENGINE::CVIBuffer::Initialize(void)
{
	HRESULT hr = NULL;

	hr = ENGINE::GetDevice()->CreateVertexBuffer(
		m_dwVertexSize * m_dwVertexCount,
		0,
		m_dwVertexFVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		NULL);
	if FAILED(hr)
	{
		UTIL::SHOW_ERROR(hr, L"CreateVertexBuffer() Failed!");
		return hr;
	}

	hr = ENGINE::GetDevice()->CreateIndexBuffer(
		m_dwIndexSize * m_dwTriangleCount,
		0,
		m_IndexFormat,
		D3DPOOL_MANAGED,
		&m_pIndexBuffer,
		NULL);
	if FAILED(hr)
	{
		UTIL::SHOW_ERROR(hr, L"CreateIndexBuffer() Failed!");
		return hr;
	}

	return S_OK;
}

void ENGINE::CVIBuffer::Release(void)
{
	if ((*m_pReferenceCount) == 0)
	{
		SAFE_RELEASE(m_pIndexBuffer);
		SAFE_RELEASE(m_pVertexBuffer);

		CGraphicResource::Release();
	}
	else
	{
		--(*m_pReferenceCount);
	}
}
