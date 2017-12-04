/*!
 * \file CharacterGroup.h
 * \date 2016/06/07 21:20
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

#ifndef CharacterGroup_h__
#define CharacterGroup_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class CCharacter;
class CMainUIObserver;

class ENGINE_DLL_SPECIFIER CCharacterGroup : public CGameObject
{
private:
	typedef vector<CCharacter*> CHAR_VEC;
private:
	vector<CCharacter*> m_vecCharacter;

	// get component helper
	CHAR_VEC::iterator m_finder;
	CHAR_VEC::iterator m_finder_end;

	//MainUIObserver
	CMainUIObserver*	m_pMainUIObserver;

public:
	static CCharacterGroup* Create(eObjectType _eObjectType);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);

public:
	virtual int		Update(void);
	virtual void	Render(void);
	int		BattleUpdate(void);

public:
	vector<CCharacter*>* GetCharacterGroup(void);

public:
	void		AddCharacter(eCharacterID _eCharID, CCharacter* _pCharacter);
	HRESULT		GroupSort(vector<eCharacterID>* _pvecCharID);
	HRESULT		GroupSort(void);
	CCharacter* GetCharacter(eCharacterID _eCharID);
	CCharacter* GetLeaderCharacter(void);

	//! 이렇게 객체의 wrapper로 작동하는 친구들은, get component를 오버라이딩 해줘야함..
	virtual void PrepareFind(void);
	virtual ENGINE::CComponent* GetComponent(const wstring& _strComponentKey);

private:
	explicit CCharacterGroup(eObjectType _eObjectType);

public:
	virtual ~CCharacterGroup(void);
};

END_NAMESPACE

#endif // CharacterGroup_h__