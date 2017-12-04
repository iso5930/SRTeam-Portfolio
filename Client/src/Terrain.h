/*!
 * \file Terrain.h
 * \date 2016/05/27 10:38
 *
 * \author ¹ÚÁ¤¹Î
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/


#ifndef Terrain_h__
#define Terrain_h__

#include "Client_Include.h"
#include "GameObject.h"

namespace ENGINE
{
	class CTransform;
	class CVIBuffer;

	class CTerrainInfo;
}
class CTile;
class CTerrain : public ENGINE::CGameObject
{
	// member variable
private:
	ENGINE::CTransform* m_pInfo;
	ENGINE::CVIBuffer* m_pVIBuffer;

	vector<CTile*> m_vecTile;
	ENGINE::CTerrainInfo* m_pTerrainInfo;

	wstring m_strResourceKey;

	// member function
public:
	static CTerrain* Create(eObjectType _eObjectType, wstring _wstrFilePath, wstring _wstrKey);
	virtual int Update(void);
	virtual void Render(void);

	ENGINE::CTerrainInfo* GetTerrainInfo(void)
	{
		return m_pTerrainInfo;
	}

private:
	HRESULT	Initialize(wstring _wstrFilePath, wstring _wstrKey);
	virtual HRESULT Initialize(void);
	HRESULT AddComponent(void);
	virtual void Release(void);
	void	LoadMapBuffer(wstring	_wstrFilePath, wstring	_wstrKey);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CTerrain(eObjectType _eObjectType);
public:
	~CTerrain(void);
	MAKE_UNCOPYABLE(CTerrain)
};

#endif // Terrain_h__