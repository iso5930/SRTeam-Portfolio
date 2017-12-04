/*!
 * \file Hedgehog.h
 * \date 2016/06/21 14:27
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

#ifndef Hedgehog_h__
#define Hedgehog_h__

#include "Client_Include.h"
#include "Monster.h"

class CHedgehog : public ENGINE::CMonster
{


public:
	static CHedgehog* Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);

public:
	virtual int Update(void);
	virtual int BattleUpdate(void);

private:
	HRESULT		AddComponent(void);

private:
	explicit CHedgehog(eObjectType _eObjectType);

protected:
	virtual void SetState(void);
	virtual void SetBattleState(void);
	virtual void SetAngle(void);

public:
	virtual ~CHedgehog(void);

};

#endif // Hedgehog_h__