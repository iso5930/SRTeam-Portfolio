/*!
 * \file WildBoar.h
 * \date 2016/06/18 22:14
 *
 * \author ÀÌÁøÇü
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef WildBoar_h__
#define WildBoar_h__

#include "Client_Include.h"
#include "Monster.h"

class CWildBoar : public ENGINE::CMonster
{
public:
	static CWildBoar* Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);
	HRESULT	AddComponent(void);

public:
	virtual int		Update(void);
	virtual int		BattleUpdate(void);

protected:
	void	SetState(void);
	void	SetBattleState(void);
	void	SetAngle(void);
	
private:
	explicit CWildBoar(eObjectType _eObjectType);

public:
	virtual ~CWildBoar(void);
};

#endif // WildBoar_h__