/*!
 * \file Character_Elluard.h
 * \date 2016/06/17 11:22
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

#ifndef Character_Elluard_h__
#define Character_Elluard_h__

#include "Client_Include.h"
#include "Character.h"

class CCharacter_Elluard : public ENGINE::CCharacter
{
public:
	static CCharacter_Elluard* Create(eObjectType _eObjectType);

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
	explicit CCharacter_Elluard(eObjectType _eObjectType);

public:
	virtual ~CCharacter_Elluard(void);
};

#endif // Character_Elluard_h__