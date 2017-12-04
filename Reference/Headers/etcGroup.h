/*!
 * \file etcGroup.h
 * \date 2016/06/20 16:59
 *
 * \author 신동윤
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef etcGroup_h__
#define etcGroup_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class Cetc;

class ENGINE_DLL_SPECIFIER CetcGroup : public CGameObject
{
private:
	vector<Cetc*>	m_vecetc;

	// get component helper
	vector<Cetc*>::iterator m_finder;
	vector<Cetc*>::iterator m_finder_end;

public:
	static CetcGroup* Create(eObjectType _eObjectType);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);

public:
	virtual int		Update(void);
	virtual void	Render(void);

public:
	vector<Cetc*>* GetetcGroup(void);

public:
	void	Addetc(Cetc* _petc);

	//! 이렇게 객체의 wrapper로 작동하는 친구들은, get component를 오버라이딩 해줘야함..
	virtual void PrepareFind(void);
	virtual ENGINE::CComponent* GetComponent(const wstring& _strComponentKey);

private:
	explicit CetcGroup(eObjectType _eObjectType);

public:
	virtual ~CetcGroup(void);	
};

END_NAMESPACE

#endif // etcGroup_h__