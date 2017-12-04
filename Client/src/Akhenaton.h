/*!
 * \file Akhenaton.h
 * \date 2016/06/21 14:45
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Akhenaton_h__
#define Akhenaton_h__

#include "Client_Include.h"
#include "Monster.h"

class CAkhenaton : public ENGINE::CMonster
{
public:
	static CAkhenaton* Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos);

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
	explicit CAkhenaton(eObjectType _eObjectType);

public:
	virtual ~CAkhenaton(void);

};


#endif // Akhenaton_h__