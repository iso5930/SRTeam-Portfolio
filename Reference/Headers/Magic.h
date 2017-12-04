/*!
 * \file Magic.h
 * \date 2016/06/06 14:42
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

#ifndef Magic_h__
#define Magic_h__

#include "Ability.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CMagic : public ENGINE::CAbility
{
public:
	static CMagic* Create(eObjectType _eObjectType, const wstring& _wstrName, eAbilityType _AbiliType1, int _iAbili1, 
							eAbilityType _AbiliType2 = ABILITY_END, int _iAbili2 = 0,
							eAbilityType _AbiliType3 = ABILITY_END, int _iAbili3 = 0);

private:
	HRESULT Initialize(const wstring& _wstrName, eAbilityType _AbiliType1, int _iAbili1, 
						eAbilityType _AbiliType2 = ABILITY_END, int _iAbili2 = 0,
						eAbilityType _AbiliType3 = ABILITY_END, int _iAbili3 = 0);

	virtual HRESULT Initialize(void);
	void	Release(void);

public:
	virtual int Update(void);
	virtual void Render(void);

protected:
	explicit CMagic(eObjectType _eObjectType);

public:
	virtual ~CMagic(void);
};

END_NAMESPACE

#endif // Magic_h__