/*!
 * \file CubeObject.h
 * \date 2016/06/05 20:49
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

#ifndef CubeObject_h__
#define CubeObject_h__

#include "Client_Include.h"
#include "GameObject.h"

namespace ENGINE
{
	class CTransform;
	class CVIBuffer;
	class CTexture;

	class CTerrainCollision;
}
class CCubeObject : public ENGINE::CGameObject
{
	// member variable
private:
	ENGINE::CTransform* m_pInfo;
	ENGINE::CVIBuffer* m_pVIBuffer;
	ENGINE::CTexture* m_pTexture;

	const VERTEX_TEXTURE* m_pTerrainVertex;
	ENGINE::CTerrainCollision* m_pTerrainCollision;

	// member function
public:
	static CCubeObject* Create(eObjectType _eObjectType, const D3DXVECTOR3& _vPos);
	virtual int Update(void);
	virtual void Render(void);
private:
	virtual HRESULT Initialize(void);
	HRESULT AddComponent(void);
	void SetDirection(void);
	virtual void Release(void);

	// getter & setter
public:
	void SetPos(const D3DXVECTOR3& _vPos);

	// constructor & destructor
private:
	explicit CCubeObject(eObjectType _eObjectType);
public:
	~CCubeObject(void);
	MAKE_UNCOPYABLE(CCubeObject)
};

#endif // CubeObject_h__