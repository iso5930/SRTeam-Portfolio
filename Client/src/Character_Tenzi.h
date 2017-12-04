/*!
 * \file Character_Tenzi.h
 * \date 2016/06/17 11:23
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

#ifndef Character_Tenzi_h__
#define Character_Tenzi_h__

#include "Client_Include.h"
#include "Character.h"

class CCharacter_Tenzi : public ENGINE::CCharacter
{
public:
	static CCharacter_Tenzi* Create(eObjectType _eObjectType);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);

public:
	virtual int		Update(void);
	virtual void	SetCamera(void);
	virtual int		BattleUpdate(void);


private:
	HRESULT AddComponent(void);
	virtual void SetState(void);
	virtual void BattleState(void);
	virtual void SetBattleAngle(void);

private:
	explicit CCharacter_Tenzi(eObjectType _eObjectType);

public:
	virtual ~CCharacter_Tenzi(void);
};

#endif // Character_Tenzi_h__