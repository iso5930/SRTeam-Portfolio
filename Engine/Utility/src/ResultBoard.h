/*!
 * \file ResultBoard.h
 * \date 2016/06/23 17:32
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

#ifndef ResultBoard_h__
#define ResultBoard_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class CCharacterGroup;

class ENGINE_DLL_SPECIFIER CResultBoard : public CGameObject
{
private:
	CCharacterGroup*	m_pCharGroup;
	bool				m_bCreate;	//이게 켜져 있는 동안은 바깥의 플레이어들 못움직이게... 해야함
	bool				m_bExit;
	int					m_iExp;
	bool				m_bLevelUp;
	bool				m_bBattleEnd;

public:
	static CResultBoard* Create(eObjectType _eObjectType, int _iExp, CCharacterGroup* _pCharGroup);

private:
	virtual HRESULT Initialize(void);

public:
	virtual int		Update(void);
	virtual void	Render(void);

private:
	void	SetCharacterAndExp(CCharacterGroup* _pGroup, int _iExp);
	int		ResultBoard(void);
	void	DrawSprite(eResourceType _eResourceType, const TCHAR* _ResourceKey, float _fX, float _fY, const int _iCnt, const RECT* _rcRect);
	void	DrawFont_Int(int _iText, float _fX, float _fY, float _fIntervalX, float _fIntervalY);

private:
	explicit CResultBoard(eObjectType _eObjectType);

public:
	virtual ~CResultBoard(void);
};

END_NAMESPACE

#endif // ResultBoard_h__