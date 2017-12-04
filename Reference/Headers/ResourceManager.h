/*!
 * \file ResourceManager.h
 * \date 2016/05/25 1:09
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
//! �����ߴ���, add ����, clone ���� �Ұ� �ƴ϶�, ������ add�ؼ� ���� ����������.. �����ұ�?

#ifndef ResourceManager_h__
#define ResourceManager_h__

#include "Engine_Include.h"
#include "VIBuffer.h"

BEGIN_NAMESPACE(ENGINE)
class CComponent;
class ENGINE_DLL_SPECIFIER CResourceManager
{
	DECLARE_SINGLETON(CResourceManager)

private:
	typedef map<wstring, CGraphicResource*> RESOURCE_MAP;

	// member variable
private:
	RESOURCE_MAP m_pResourceMap[RESOURCE_TYPE_END];

	// member function
public:
	HRESULT AddBuffer(
		eResourceType _eResourceType,
		CVIBuffer::eBufferType _eBufferType,
		const wstring& _strResourceKey,
		DWORD _dwCountX = 0,
		DWORD _dwCountZ = 0,
		DWORD _dwInterval = 1);
	HRESULT AddBuffers(void);

	HRESULT AddTexture(
		eResourceType _eResourceType,
		eTextureType _eTextureType,
		const wstring& _strResourceKey,
		const wstring& _strFilePath,
		DWORD _dwCount);

	HRESULT	 AddSprite(
		eResourceType _eResourceType,
		const wstring& _strResourceKey,
		const wstring& _strFilePath,
		DWORD _dwCount = 1,
		D3DCOLOR _Color = NULL);

	CComponent* CloneResource(ENGINE::CGameObject* _pOwner, eResourceType _eResourceType, const wstring& _strResourceKey);
	void ReleaseDynamic(void);

	void ReadVerticies(eResourceType _eResourceType, const wstring& _strResourceKey, void* _pVerticies);
	void WriteVerticies(eResourceType _eResourceType, const wstring& _strResourceKey, void* _pVerticies);
private:
	void Release(void);

	// getter & setter
public:
	TEXINFO* GetSpriteTexture(eResourceType _eResourceType, const wstring& _strResourceKey, DWORD _dwCount);

	// constructor & destructor
private:
	explicit CResourceManager(void);
	~CResourceManager(void);
};
END_NAMESPACE

#endif // ResourceManager_h__