/*!
 * \file BattleUI.h
 * \date 2016/06/18 20:10
 *
 * \author 이진형
 * Contact: user@company.com
 *
 * \brief 
 *		//스프라이트 객체를 사용해서 UI를 띄울것..
 * TODO: long description
 *
 * \note
*/

#ifndef BattleUI_h__
#define BattleUI_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)

class CGroupObserver;
class CMonsterGroup;
class CMouseCollision;
class CVIBuffer;
class CMonster;

class ENGINE_DLL_SPECIFIER CBattleUI : public CGameObject
{
private:
	CMonster*			m_pMonster;
	CGroupObserver*		m_pCharacterGroupObserver;
	CMonsterGroup*		m_pMonsterGroup;
	eBattleMessage		m_eBattleMessage;
	D3DXVECTOR3			m_vTargetPos;
	D3DXVECTOR3			m_vMovePos;
	vector<RECT>		m_vecCollision;
	bool				m_bFirstClick;
	bool				m_bMessageEnd;
	bool				m_bMessageBoxClose;
	int					m_iMouseOver;
	CVIBuffer*			m_pRcCol;
	int					m_iAbilityIndex;

private:
	bool* m_pCheck;

private:
	CMouseCollision*	m_pMouseCollision;
	
public:
	static CBattleUI* Create(eObjectType _eObjectType);

private:
	virtual HRESULT Initialize(void);
	virtual void	Release(void);

public:
	virtual int		Update(void);
	virtual void	Render(void);
	
private:
	void DrawSprite(eResourceType _eResourceType, const TCHAR* _ResourceKey, float _fX, float _fY, const int _iCnt, const RECT* _rcRect);
	void DrawText(TCHAR* _pText, D3DCOLOR _Color, float _fX, float _fY);

private:
	void	MonsterTargeting(void);
	void	MoveTargeting(void);
	void	SelectAbility(void);

public:
	int		MessageBoxUpdate(void);
	int		GetAbilityIndex(void);
	void	MessageRender(void);
	void	RageGaugeRender(int iCharCur);

public:
	void			SetBattleMessage(eBattleMessage _Message);
	eBattleMessage	GetBattleMessage(void);
	D3DXVECTOR3*	GetTargetPos(void);
	D3DXVECTOR3*	GetMovePos(void);
	void			SetFirstClick(bool _Check);
	void			SetMonsterGroup(CMonsterGroup* _pMonsterGroup);
	VOID			DrawFont_Int(int _iText, float _fX, float _fY, float _fIntervalX, float _fIntervalY, wstring wstrKey);
	void			DrawFont(char* _pName, float _fX, float _fY, float _fIntervalX, float _fIntervalY);
	CMonster*		GetMonsterTarget(void);

private:
	explicit CBattleUI(eObjectType _eObjectType);

public:
	virtual ~CBattleUI(void);
};

END_NAMESPACE

#endif // BattleUI_h__