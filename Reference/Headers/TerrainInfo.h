/*!
 * \file TerrainInfo.h
 * \date 2016/06/16 1:23
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef TerrainInfo_h__
#define TerrainInfo_h__

#include "Engine_Include.h"
#include "Component.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CTerrainInfo : public CComponent
{
	// member variable
public:
	VERTEX_COLOR*	m_pVertexColor;

	DWORD			m_dwVertexCountX;
	DWORD			m_dwVertexCountZ;

	// member function
public:
	static CTerrainInfo* Create(ENGINE::CGameObject* _pOwner, DWORD _dwVertexCountX, DWORD _dwVertexCountZ);
private:
	HRESULT Initialize(DWORD _dwVertexCountX, DWORD _dwVertexCountZ);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CTerrainInfo(ENGINE::CGameObject* _pOwner);
public:
	virtual ~CTerrainInfo(void);
	MAKE_UNCOPYABLE(CTerrainInfo)
};
END_NAMESPACE

#endif // TerrainInfo_h__