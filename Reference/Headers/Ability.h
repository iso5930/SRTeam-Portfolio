/*!
 * \file Ability.h
 * \date 2016/06/07 15:55
 *
 * \author 이진형
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Ability_h__
#define Ability_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CAbility : public CGameObject
{
protected:
	FRAME					m_tAbiliIconFrame;
	DWORD					m_dwTime;
	vector<eAbilityType>	m_vecAbilityType;
	vector<int>				m_vecAbilityValue;
	wstring					m_wstrAbilityName;
	float					m_fY;
	bool					m_bField; //필드에서 사용할수 있는 스킬인지? 아닌지
	int						m_iDamage;

	
public:
	virtual int		Update(void);
	virtual void	Render(void);

public:
	void DrawAbility(float _fY);
	void SetField(bool _bField);
	const wstring GetAbilityName(void);
	void SetDamage(int _iDamage);

protected:
	explicit CAbility(eObjectType _eObjectType);

public:
	virtual ~CAbility(void);
};

END_NAMESPACE

#endif // Ability_h__