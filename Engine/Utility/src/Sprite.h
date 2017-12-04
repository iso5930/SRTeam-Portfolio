/*!
 * \file Sprite.h
 * \date 2016/06/11 18:29
 *
 * \author ������
 * Contact: user@company.com
 *
 * \brief �÷��̾�, ����, ��Ÿ ������Ʈ�� ��������Ʈ �̹��� ���� ��ü
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Sprite_h__
#define Sprite_h__

#include "Engine_Include.h"
#include "Component.h"

BEGIN_NAMESPACE(ENGINE)

class ENGINE_DLL_SPECIFIER CSprite : public CComponent
{
private:
	FRAME	m_tFrame;
	bool	m_bFrameEnd;

public:
	static CSprite* Create(ENGINE::CGameObject* _pOwner, const FRAME& _Frame);

public:
	virtual int Update(void);

private:
	void FrameMove(void);

public:
	float	GetCurFrame(void);
	void	SetCurFrame(int _iCur);
	void	SetFrame(const FRAME& _Frame);
	bool	GetFrameEnd(void);

protected:
	explicit CSprite(ENGINE::CGameObject* _pOwner);

public:
	virtual ~CSprite(void);
};

END_NAMESPACE

#endif // Sprite_h__