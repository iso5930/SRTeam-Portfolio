/*!
 * \file Skeleton.h
 * \date 2016/06/21 14:44
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

#ifndef Skeleton_h__
#define Skeleton_h__

#include "Client_Include.h"
#include "Monster.h"

class CSkeleton : public ENGINE::CMonster
{
public:
	static CSkeleton* Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos);

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
	explicit CSkeleton(eObjectType _eObjectType);

public:
	virtual ~CSkeleton(void);

};

#endif // Skeleton_h__