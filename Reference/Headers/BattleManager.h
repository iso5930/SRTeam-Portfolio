/*!
 * \file BattleManager.h
 * \date 2016/06/18 20:04
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

#ifndef BattleManager_h__
#define BattleManager_h__

#include "Engine_Include.h"

BEGIN_NAMESPACE(ENGINE)

class CBattleUI;
class CCharacterGroup;
class CMonsterGroup;

class ENGINE_DLL_SPECIFIER CBattleManager
{
	DECLARE_SINGLETON(CBattleManager)
private:
	bool				m_bBattleStart;
	CBattleUI*			m_pBattleUI;
	CCharacterGroup*	m_pCharacterGroup;
	CMonsterGroup*		m_pMonsterGroup;
	vector<float>		m_vecCharacterTime;
	vector<float>		m_vecMonsterTime;
	bool				m_bTurn;
	int					m_iTurnIndex;

	int					m_iGetExp;
	bool				m_bBattleEnd;

public:
	void CreateBattle(CCharacterGroup* _pCharacterGroup, CMonsterGroup* _pMonsterGroup); //전투 이벤트가 발생했을때 새로운 그룹이 들어온다는것을 알려주는것..

private:
	void EndBattle(void);
	void Release(void);

public:
	int		Update(void);
	void	Render(void);
private:
	void	TurnSpeedRender(void);
public:
	void	DrawSprite(eResourceType _eResourceType, const TCHAR* _ResourceKey, float _fX, float _fY, const int _iCnt, const RECT* _rcRect);
	void	DrawFont(char* _pName, float _fX, float _fY, float _fIntervalX, float _fIntervalY);

public:
	bool	GetBattleStart(void);
	bool	GetTurn(void);
	int		GetTurnIndex(void);
	ENGINE::CMonsterGroup*		GetMonsterGroup(void);

private:
	explicit CBattleManager(void);
	~CBattleManager(void);
};

END_NAMESPACE

#endif // BattleManager_h__