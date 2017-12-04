#include "ResourceManager.h"

#include "TriangleColor.h"
#include "RectangleColor.h"
#include "RectangleTexture.h"
#include "RectangleTerrain.h"
#include "CubeTexture.h"
#include "CubeColor.h"
#include "RectangleWave.h"

#include "Texture.h"
#include "SpriteTexture.h"

IMPLEMENT_SINGLETON(ENGINE::CResourceManager)

ENGINE::CResourceManager::CResourceManager(void)
{

}

ENGINE::CResourceManager::~CResourceManager(void)
{
	Release();
}

HRESULT ENGINE::CResourceManager::AddBuffer(eResourceType _eResourceType,
											CVIBuffer::eBufferType _eBufferType,
											const wstring& _strResourceKey,
											DWORD _dwCountX /*= 0*/,
											DWORD _dwCountZ /*= 0*/,
											DWORD _dwInterval /*= 1*/)
{
	RESOURCE_MAP::iterator iter = m_pResourceMap[_eResourceType].find(_strResourceKey);
	if (iter != m_pResourceMap[_eResourceType].end())
	{
		//! 다른 리소스를 같은 키로 저장하려고 할 때.. 문제 생기겠지만, 이젠 나도 모르겠다

		//UTIL::SHOW_ERROR(_strResourceKey.c_str(), L"리소스 중복 삽입 시도를 발견하였습니다.");
		//return E_FAIL;

		return S_OK;
	}

	CGraphicResource* pResource = NULL;
	switch(_eBufferType)
	{
	case CVIBuffer::BUFFER_TYPE_TRIANGLE_COLOR:
		pResource = CTriangleColor::Create();
		break;

	case CVIBuffer::BUFFER_TYPE_RECTANGLE_COLOR:
		pResource = CRectangleColor::Create();
		break;

	case CVIBuffer::BUFFER_TYPE_CUBE_COLOR:
		pResource = CCubeColor::Create();
		break;

	case CVIBuffer::BUFFER_TYPE_RECTANGLE_TERRAIN:
		pResource = CRectangleTerrain::Create(_dwCountX, _dwCountZ, _dwInterval);
		break;

	case CVIBuffer::BUFFER_TYPE_TRIANGLE_TEXTURE:
		break;

	case CVIBuffer::BUFFER_TYPE_RECTANGLE_TEXTURE:
		pResource = CRectangleTexture::Create();
		break;

	case CVIBuffer::BUFFER_TYPE_CUBE_TEXTURE:
		pResource = CCubeTexture::Create();
		break;

	case CVIBuffer::BUFFER_TYPE_WAVE_TEXTURE:
		pResource = CRectangleWave::Create(_dwCountX, _dwCountZ, _dwInterval);
		break;
	}
	if (pResource == NULL)
		return E_FAIL;

	m_pResourceMap[_eResourceType].insert(RESOURCE_MAP::value_type(_strResourceKey, pResource));

	return S_OK;
}

HRESULT ENGINE::CResourceManager::AddBuffers(void)
{
	HRESULT hr = NULL;

	hr = AddBuffer(RESOURCE_TYPE_STATIC, CVIBuffer::BUFFER_TYPE_TRIANGLE_COLOR, L"Buffer_Triangle_Color");
	if FAILED(hr)
		return hr;

	hr = AddBuffer(RESOURCE_TYPE_STATIC, CVIBuffer::BUFFER_TYPE_RECTANGLE_COLOR, L"Buffer_Rectangle_Color");
	if FAILED(hr)
		return hr;

	hr = AddBuffer(RESOURCE_TYPE_STATIC, CVIBuffer::BUFFER_TYPE_CUBE_COLOR, L"Buffer_Cube_Color");
	if FAILED(hr)
		return hr;

	//! 채우자..
	/*hr = AddBuffer(RESOURCE_TYPE_STATIC, CVIBuffer::BUFFER_TYPE_TRIANGLE_TEXTURE, L"Buffer_Triangle_Texture");
	if FAILED(hr)
		return hr;*/

	hr = AddBuffer(RESOURCE_TYPE_STATIC, CVIBuffer::BUFFER_TYPE_RECTANGLE_TEXTURE, L"Buffer_Rectangle_Texture");
	if FAILED(hr)
		return hr;

	hr = AddBuffer(RESOURCE_TYPE_STATIC, CVIBuffer::BUFFER_TYPE_CUBE_TEXTURE, L"Buffer_Cube_Texture");
	if FAILED(hr)
		return hr;

	hr = AddBuffer(RESOURCE_TYPE_STATIC, CVIBuffer::BUFFER_TYPE_WAVE_TEXTURE, L"Buffer_Wave_Texture", 33, 33);
	if FAILED(hr)
		return hr;

	return S_OK;
}

HRESULT ENGINE::CResourceManager::AddTexture(eResourceType _eResourceType,
											 eTextureType _eTextureType,
											 const wstring& _strResourceKey,
											 const wstring& _strFilePath,
											 DWORD _dwCount)
{
	RESOURCE_MAP::iterator iter = m_pResourceMap[_eResourceType].find(_strResourceKey);
	if (iter != m_pResourceMap[_eResourceType].end())
	{
		//UTIL::SHOW_ERROR(_strResourceKey.c_str(), L"리소스 중복 삽입 시도를 발견하였습니다.");
		//return E_FAIL;

		return S_OK;
	}

	CGraphicResource* pResource = CTexture::Create(_eTextureType, _strFilePath, _dwCount);
	if (pResource == NULL)
		return E_FAIL;

	m_pResourceMap[_eResourceType].insert(RESOURCE_MAP::value_type(_strResourceKey, pResource));

	return S_OK;
}

HRESULT ENGINE::CResourceManager::AddSprite(eResourceType _eResourceType,
											const wstring& _strResourceKey,
											const wstring& _strFilePath,
											DWORD _dwCount /*= 1*/,
											D3DCOLOR _Color/* = NULL*/)
{
	RESOURCE_MAP::iterator iter = m_pResourceMap[_eResourceType].find(_strResourceKey);
	if (iter != m_pResourceMap[_eResourceType].end())
	{
		/*UTIL::SHOW_ERROR(_strResourceKey.c_str(), L"리소스 중복 삽입 시도를 발견하였습니다.");
		return E_FAIL;*/

		return S_OK;
	}

	CGraphicResource* pResource = CSpriteTexture::Create(_strFilePath.c_str(), _dwCount, _Color);

	if(pResource == NULL)
	{
		return E_FAIL;
	}

	m_pResourceMap[_eResourceType].insert(RESOURCE_MAP::value_type(_strResourceKey, pResource));

	return S_OK;
}

ENGINE::CComponent* ENGINE::CResourceManager::CloneResource(ENGINE::CGameObject* _pOwner, eResourceType _eResourceType, const wstring& _strResourceKey)
{
	RESOURCE_MAP::iterator iter = m_pResourceMap[_eResourceType].find(_strResourceKey);
	if (iter == m_pResourceMap[_eResourceType].end())
	{
		UTIL::SHOW_ERROR(_strResourceKey.c_str(), L"존재하지 않는 리소스입니다.");
		return NULL;
	}

	return iter->second->CloneResource(_pOwner);
}

void ENGINE::CResourceManager::ReleaseDynamic(void)
{
	RESOURCE_MAP::iterator iter = m_pResourceMap[RESOURCE_TYPE_DYNAMIC].begin();
	RESOURCE_MAP::iterator iter_end = m_pResourceMap[RESOURCE_TYPE_DYNAMIC].end();
	for (; iter != iter_end; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_pResourceMap[RESOURCE_TYPE_DYNAMIC].clear();
}

void ENGINE::CResourceManager::ReadVerticies(eResourceType _eResourceType, const wstring& _strResourceKey, void* _pVerticies)
{
	RESOURCE_MAP::iterator iter = m_pResourceMap[_eResourceType].find(_strResourceKey);
	if (iter == m_pResourceMap[_eResourceType].end())
	{
		UTIL::SHOW_ERROR(_strResourceKey.c_str(), L"버텍스 키를 찾을 수 없습니다!");
		return;
	}

	static_cast<CVIBuffer*>(iter->second)->ReadVerticies(_pVerticies);
}

void ENGINE::CResourceManager::WriteVerticies(eResourceType _eResourceType, const wstring& _strResourceKey, void* _pVerticies)
{
	RESOURCE_MAP::iterator iter = m_pResourceMap[_eResourceType].find(_strResourceKey);
	if (iter == m_pResourceMap[_eResourceType].end())
	{
		UTIL::SHOW_ERROR(_strResourceKey.c_str(), L"버텍스 키를 찾을 수 없습니다!");
		return;
	}

	static_cast<CVIBuffer*>(iter->second)->WriteVerticies(_pVerticies);
}

void ENGINE::CResourceManager::Release(void)
{
	for (int i = 0; i < RESOURCE_TYPE_END; ++i)
	{
		RESOURCE_MAP::iterator iter = m_pResourceMap[i].begin();
		RESOURCE_MAP::iterator iter_end = m_pResourceMap[i].end();
		for (; iter != iter_end; ++iter)
		{
			SAFE_DELETE(iter->second);
		}
		m_pResourceMap[i].clear();
	}
}

TEXINFO* ENGINE::CResourceManager::GetSpriteTexture(eResourceType _eResourceType, const wstring& _strResourceKey, DWORD _dwCount)
{
	RESOURCE_MAP::iterator iter = m_pResourceMap[_eResourceType].find(_strResourceKey);
	if (iter == m_pResourceMap[_eResourceType].end())
	{
		UTIL::SHOW_ERROR(_strResourceKey.c_str(), L"SpriteTexture Not Find!!");
		return NULL;
	}
	
	CSpriteTexture* pSpriteTexture = dynamic_cast<CSpriteTexture*>(iter->second);

	return pSpriteTexture->GetTexInfo(_dwCount);
}
