#include "Sprite.h"

#include "Export_Function.h"

ENGINE::CSprite::CSprite(ENGINE::CGameObject* _pOwner)
:CComponent(_pOwner)
{

}

ENGINE::CSprite::~CSprite(void)
{

}

ENGINE::CSprite* ENGINE::CSprite::Create(ENGINE::CGameObject* _pOwner, const FRAME& _Frame)
{
	CSprite* pSprite = new CSprite(_pOwner);

	pSprite->SetFrame(_Frame);

	return pSprite;
}

int ENGINE::CSprite::Update(void)
{
	FrameMove();

	return 0;
}

void ENGINE::CSprite::FrameMove(void)
{
	m_tFrame.fCurFrame += m_tFrame.fFrameTime * ENGINE::GetTimeDelta();

	m_bFrameEnd = false;

	if(m_tFrame.fCurFrame > m_tFrame.fEndFrame)
	{
		m_tFrame.fCurFrame = m_tFrame.fStartFrame;
		m_bFrameEnd = true;
	}
}

float ENGINE::CSprite::GetCurFrame(void)
{
	return m_tFrame.fCurFrame;
}

void ENGINE::CSprite::SetFrame(const FRAME& _Frame)
{
	m_tFrame = _Frame;
}

bool ENGINE::CSprite::GetFrameEnd(void)
{
	return m_bFrameEnd;
}

void ENGINE::CSprite::SetCurFrame(int _iCur)
{
	m_tFrame.fCurFrame = (float)_iCur;
}