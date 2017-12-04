/*!
 * \file Terrain.h
 * \date 2016/06/04 20:06
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

#pragma once

#include "GameObject.h"

namespace ENGINE
{
	class CTransform;
	class CVIBuffer;
}

class CTile;
class CTerrain : public ENGINE::CGameObject
{
public:
	int	m_iCountX;
	int	m_iCountZ;
	int m_iInterval;
	int	m_iCountTotal;

public:
	vector<CTile*>* m_vecTile;

private:
	ENGINE::CTransform* m_pInfo;

	// member function
public:
	static CTerrain* Create(void);
	virtual int Update(void);
	virtual void Render(void);

private:
	virtual HRESULT Initialize(void);
	HRESULT AddComponent(void);
	virtual void Release(void);

public:
	CTerrain(void);
	~CTerrain(void);
};
