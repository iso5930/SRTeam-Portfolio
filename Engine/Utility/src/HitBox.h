/*!
 * \file HitBox.h
 * \date 2016/06/21 21:51
 *
 * \author ������
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

//��ų�̳� �Ϲݰ����� ���������� 
//�������� ��Ʈ �ڽ��� �׷��� 
//���濡�� �������� ������ Ŭ����...
//������ ���������� �˾ƾ� �ϴµ�...
//������, ����, 

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
	bool			m_bPlayer; //�÷��̾��ΰ� �ƴѰ��� �Ǵ��ϴ� ����
	bool			m_bCreate; //���� ������ �Ǿ��ٸ� �Ǵ� ���� ƽ�� �ٷ� ������ ���ټ� �ֵ���...
		
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