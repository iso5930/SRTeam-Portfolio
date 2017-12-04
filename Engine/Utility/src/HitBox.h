/*!
 * \file HitBox.h
 * \date 2016/06/21 21:51
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

//스킬이나 일반공격을 실행했을때 
//실질적인 히트 박스를 그려서 
//상대방에게 데미지를 입히는 클래스...
//누구의 소유인지를 알아야 하는데...
//데미지, 범위, 

#ifndef HitBox_h__
#define HitBox_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class COBBCollision;

class ENGINE_DLL_SPECIFIER CHitBox : public CGameObject
{
private:
	CGameObject*	m_pTarget;
	COBBCollision*	m_pOBBCollision;
	bool*			m_pCheck;

private:
	CGameObject*	m_pOwner;
	bool			m_bPlayer; //플레이어인가 아닌가를 판단하는 변수
	bool			m_bCreate; //지금 생성이 되었다를 판단 다음 틱에 바로 삭제를 해줄수 있도록...
		
public:
	static CHitBox* Create(eObjectType _eObjectType, CGameObject* _pOwner, CGameObject* _pTarget, float _fCX, float _fCY, float _fCZ, int _iAtk, bool _bPush, bool _bPlayer = false);

private:
	virtual HRESULT Initialize(void);

private:
	HRESULT			AddOBBCollision(float _fCX, float _fCY, float _fCZ, int _iAtk, bool _bPush);
	void			SetOwner(CGameObject* _pOwner, bool _bPlayer = false);
	CGameObject*	GetOwner(void);
	void			SetTarget(CGameObject* _pTarget);

public:
	virtual int		Update(void);
	virtual void	Render(void);
private:
	explicit CHitBox(eObjectType _eObjectType);

public:
	~CHitBox(void);
};

END_NAMESPACE

#endif // HitBox_h__