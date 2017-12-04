/*!
 * \file Character_Maria.h
 * \date 2016/06/08 10:57
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

#ifndef Character_Maria_h__
#define Character_Maria_h__

#include "Client_Include.h"
#include "Character.h"

class CCharacter_Maria : public ENGINE::CCharacter
{
public:
	static CCharacter_Maria* Create(eObjectType _eObjectType);

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
	explicit CCharacter_Maria(eObjectType _eObjectType);

public:
	virtual ~CCharacter_Maria(void);
};

#endif // Character_Maria_h__