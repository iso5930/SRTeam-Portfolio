/*!
 * \file Skill.h
 * \date 2016/06/06 14:43
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

#ifndef Skill_h__
#define Skill_h__

#include "Ability.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CSkill : public ENGINE::CAbility
{
public:
	static CSkill* Create(eObjectType _eObjectType, const wstring& _wstrName, eAbilityType _AbiliType1, int _iAbili1, 
		eAbilityType _AbiliType2 = ABILITY_END, int _iAbili2 = 0,
		eAbilityType _AbiliType3 = ABILITY_END, int _iAbili3 = 0);

private:
	virtual HRESULT Initialize(void);
	void			Release(void);
	HRESULT			Initialize(const wstring& _wstrName, eAbilityType _AbiliType1, int _iAbili1, 
		eAbilityType _AbiliType2 = ABILITY_END, int _iAbili2 = 0,
		eAbilityType _AbiliType3 = ABILITY_END, int _iAbili3 = 0);

public:
	virtual int Update(void);
	virtual void Render(void);

protected:
	explicit CSkill(eObjectType _eObjectType);

public:
	virtual ~CSkill(void);
};

END_NAMESPACE

#endif // Skill_h__