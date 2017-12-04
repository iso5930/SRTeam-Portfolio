/*!
 * \file PoisonJelly.h
 * \date 2016/06/21 14:42
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

#ifndef PoisonJelly_h__
#define PoisonJelly_h__

#include "Client_Include.h"
#include "Monster.h"

class CPoisonJelly : public ENGINE::CMonster
{
public:
	static CPoisonJelly* Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);

public:
	virtual int Update(void);
	virtual int BattleUpdate(void);

protected:
	virtual void SetState(void);
	virtual void SetBattleState(void);
	virtual void SetAngle(void);

private:
	HRESULT		AddComponent(void);

private:
	explicit CPoisonJelly(eObjectType _eObjectType);

public:
	virtual ~CPoisonJelly(void);

};

#endif // PoisonJelly_h__