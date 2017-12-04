/*!
 * \file etc.h
 * \date 2016/06/20 16:18
 *
 * \author ½Åµ¿À±
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef etc_h__
#define etc_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class CTransform;
class CVIBuffer;
class CTexture;
class CSprite;
class COBBCollision;
class CTerrainCollision;

class ENGINE_DLL_SPECIFIER Cetc : public CGameObject
{
protected:
	CTransform*		m_pInfo;
	CVIBuffer*		m_pVIBuffer;
	CTexture*		m_pTexture;
	CSprite*		m_pSprite;
	COBBCollision*	m_pOBBCollision;

public:
	virtual int Update(void);

protected:
	explicit Cetc(eObjectType _eObjectType);

public:
	virtual ~Cetc(void);
};

END_NAMESPACE

#endif // etc_h__