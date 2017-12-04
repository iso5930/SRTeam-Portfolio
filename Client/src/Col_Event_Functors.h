/*!
 * \file Col_Event_Functors.h
 * \date 2016/06/21 20:40
 *
 * \author 박정민
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Col_Event_Functors_h__
#define Col_Event_Functors_h__

#include "CollisionFunctors.h"


class CColSwitchOn : public ENGINE::CCollisionFunctor
{
private:
	wstring m_strSwitchKey;

public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal = NULL)
	{
		ENGINE::CCharacter* pChar = dynamic_cast<ENGINE::CCharacter*>(_pHittedObject);
		if (!pChar)
			return;

		// 리더만 들이받도록 하는 코드..
		if (pChar->GetOwner()->GetLeaderCharacter() == pChar)
		{
			//cout << "허허" << endl;
			ENGINE::CEventManager::GetInstance()->SwitchOn(m_strSwitchKey);
		}
	}
public:
	explicit CColSwitchOn(const wstring& _strSwitchKey)
		:m_strSwitchKey(_strSwitchKey) { }
	virtual ~CColSwitchOn(void){ }
};

class CColSwitchOnBill : public ENGINE::CCollisionFunctor
{
private:
	wstring m_strSwitchKey;

public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal = NULL)
	{
		//ENGINE::CCharacter* pChar = dynamic_cast<ENGINE::CCharacter*>(_pHittedObject);
		//if (!pChar)
		//	return;

		// 리더만 들이받도록 하는 코드..
		//if (pChar->GetOwner()->GetLeaderCharacter() == pChar)
		//{
		//	cout << "허허" << endl;
			ENGINE::CEventManager::GetInstance()->SwitchOn(m_strSwitchKey);
		//}
	}
public:
	explicit CColSwitchOnBill(const wstring& _strSwitchKey)
		:m_strSwitchKey(_strSwitchKey) { }
	virtual ~CColSwitchOnBill(void){ }
};

class CColSwitchOnByKey : public ENGINE::CCollisionFunctor
{
private:
	wstring m_strSwitchKey;
	KEY_STATE m_KeyState;

public:
	virtual void operator ()(ENGINE::CGameObject* _pHittedObject, ENGINE::CGameObject* _pFunctorOwner, D3DXVECTOR3* _pNormal = NULL)
	{
		if ((m_KeyState == KEY_STATE_NO && ENGINE::GetInputManager()->IsEventProgressKeyDownNow()) ||
			ENGINE::GetInputManager()->IsKeyDownNow(m_KeyState))
		{
			//cout << "허허" << endl;
			ENGINE::CEventManager::GetInstance()->SwitchOn(m_strSwitchKey);
		}
	}
public:
	explicit CColSwitchOnByKey(const wstring& _strSwitchKey, const KEY_STATE& _KeyState = KEY_STATE_NO)
		:m_strSwitchKey(_strSwitchKey)
		,m_KeyState(_KeyState) { }
	virtual ~CColSwitchOnByKey(void){ }
};

#endif // Col_Event_Functors_h__