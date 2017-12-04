/*!
 * \file Effect.h
 * \date 2016/06/22 22:26
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

#ifndef Effect_h__
#define Effect_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class CTransform;
class CVIBuffer;
class CTexture;
class CSprite;

class ENGINE_DLL_SPECIFIER CEffect : public CGameObject
{
private:
	CTransform*		m_pInfo;
	CGameObject*	m_pOwner;
	eEffectType		m_eEffectType;
	CSprite*		m_pSprite;
	CVIBuffer*		m_pVIBuffer;
	CTexture*		m_pTexture;

private:
	D3DXVECTOR3 vTemp;

public:
	static CEffect* Create(eObjectType _eObjType, ENGINE::CGameObject* _pOwner, eEffectType _eEffectType, float _fX, float _fY, float _fZ);

private:
	virtual HRESULT Initialize(void);

private:
	void		SetEffect(CGameObject* _pOwner, eEffectType _eEffectType, float _fX, float _fY, float _fZ);
	void		SetBillboard(void);

public:
	virtual int Update(void);
	void		Render(void);

private:
	explicit CEffect(eObjectType _eObjType);

public:
	~CEffect(void);

};

END_NAMESPACE

#endif // Effect_h__