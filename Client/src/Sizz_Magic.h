/*!
 * \file Magic.h
 * \date 2016/06/23 13:05
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

#ifndef Sizz_Magic_h__
#define Sizz_Magic_h__

#include "GameObject.h"

namespace ENGINE
{
	class CTransform;
	class CVIBuffer;
	class CTexture;
	class CSprite;
	class CMovement;
	class COBBCollision;
}

class CSizz_Magic : public ENGINE::CGameObject
{
private:
	CGameObject*			m_pTargetID;
	eMagicType				m_eMagicType;
	D3DXVECTOR3				m_vTargetPos;
	int						m_iAtk;
	bool*					m_pCheck;

private:
	ENGINE::CTransform*		m_pInfo;
	ENGINE::CVIBuffer*		m_pVIBuffer;
	ENGINE::CGameObject*	m_pOwner;
	ENGINE::CTexture*		m_pTexture;
	ENGINE::CSprite*		m_pSprites;
	ENGINE::CMovement*		m_pMovement;
	ENGINE::COBBCollision*	m_pOBBCollsion;

public:
	static CSizz_Magic*	Create(eObjectType _eObjectType, ENGINE::CGameObject* _pOwner, eMagicType _eMagicType, D3DXVECTOR3 _vPos, D3DXVECTOR3 _vTagetPos, int _iAtk, CGameObject* _pTarget);

private:
	virtual HRESULT Initialize(void);

private:
	void	SetMagic(CGameObject* _pOwner, eMagicType _eMagicType, D3DXVECTOR3 _vPos, D3DXVECTOR3 _vTagetPos, int _iAtk);
	void	SetBillboard(void);
	void	AddComponent(void);
	void	SetMagicType(eMagicType _MagicType, int _iAtk);
	void	SetTargetID(CGameObject* _pTarget);
	void	SetMeteoTarget(void);
	CGameObject* GetOwner(void);

public:
	virtual int		Update(void);
	virtual void	Render(void);

private:
	explicit CSizz_Magic(eObjectType _eObjectType);

public:
	virtual ~CSizz_Magic(void);
};

#endif // Sizz_Magic_h__