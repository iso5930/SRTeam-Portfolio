/*!
 * \file Chimera.h
 * \date 2016/06/21 14:38
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

#ifndef Chimera_h__
#define Chimera_h__

#include "Client_Include.h"
#include "Monster.h"

class CChimera : public ENGINE::CMonster
{
public:
	static CChimera* Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos);

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
	explicit CChimera(eObjectType _eObjectType);

public:
	virtual ~CChimera(void);

};

#endif // Chimera_h__