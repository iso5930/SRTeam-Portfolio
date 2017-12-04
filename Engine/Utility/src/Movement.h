/*!
 * \file Movement.h
 * \date 2016/06/13 15:48
 *
 * \author 이진형
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Movement_h__
#define Movement_h__

#include "Engine_Include.h"
#include "Component.h"

BEGIN_NAMESPACE(ENGINE)

class CTransform;

class ENGINE_DLL_SPECIFIER CMovement : public CComponent
{
private:
	CTransform*		m_pInfo;
	D3DXVECTOR3*	m_pDestPos; //이동 지점
	D3DXVECTOR3		m_vDir;
	D3DXVECTOR3		m_vDeltaMove;
	float			m_fSpeed;
	float			m_fDeltaTime;
	float			m_fDist;
	bool			m_bMove;

public:
	static CMovement* Create(ENGINE::CGameObject* _pOwner, CTransform* _pInfo, D3DXVECTOR3* _pDest, float _fSpeed);

private:
	HRESULT Init(CTransform* _pInfo, D3DXVECTOR3* _pDest, float _fSpeed);
	void	Move(void);

public:
	virtual	int Update(void);

public:
	D3DXVECTOR3 GetDeltaMove(void);
	void		SetDeltaMove(D3DXVECTOR3 _vDeltaMove);
	void		SetMove(bool _bMove);
	bool		GetMove(void);
	void SetSpeed(float _fSpeed)
	{
		m_fSpeed = _fSpeed;
	}

protected:
	explicit CMovement(ENGINE::CGameObject* _pOwner);

public:
	virtual ~CMovement(void);
};

END_NAMESPACE

#endif // Movement_h__