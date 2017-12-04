/*!
 * \file PoisonSpider.h
 * \date 2016/06/21 14:40
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

#ifndef PoisonSpider_h__
#define PoisonSpider_h__

#include "Client_Include.h"
#include "Monster.h"

class CPoisonSpider : public ENGINE::CMonster
{
public:
	static CPoisonSpider* Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);

public:
	virtual int Update(void);
	virtual int BattleUpdate(void);

private:
	HRESULT		AddComponent(void);

protected:
	virtual void SetState(void);
	virtual void SetBattleState(void);
	virtual void SetAngle(void);

private:
	explicit CPoisonSpider(eObjectType _eObjectType);

public:
	virtual ~CPoisonSpider(void);

};

#endif // PoisonSpider_h__