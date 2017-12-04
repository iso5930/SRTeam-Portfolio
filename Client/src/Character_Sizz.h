/*!
 * \file Character_Sizz.h
 * \date 2016/06/07 15:38
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

#ifndef Character_Sizz_h__
#define Character_Sizz_h__

#include "Client_Include.h"
#include "Character.h"

class CCharacter_Sizz : public ENGINE::CCharacter
{
public:
	static CCharacter_Sizz* Create(eObjectType _eObjectType);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);

public:
	virtual int		Update(void);
	virtual int		BattleUpdate(void);
	virtual void	SetCamera(void);

private:
	HRESULT AddComponent(void);
	virtual void SetState(void);
	virtual void BattleState(void);
	virtual void SetBattleAngle(void);
	
private:
	explicit CCharacter_Sizz(eObjectType _eObjectType);

public:
	virtual ~CCharacter_Sizz(void);
};

#endif // Character_Sizz_h__