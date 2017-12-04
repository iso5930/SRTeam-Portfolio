/*!
 * \file EventManager.h
 * \date 2016/06/20 16:09
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

#ifndef EventManager_h__
#define EventManager_h__

#include "Engine_Include.h"
#include "Scene.h"

BEGIN_NAMESPACE(ENGINE)
class CGameEvent;
class ENGINE_DLL_SPECIFIER CEventManager
{
	DECLARE_SINGLETON(CEventManager)

private:
	typedef bool SWITCH; // 스위치들은 씬 상관없이, map 하나에 몰아서 생성한다.
	typedef map<wstring, SWITCH> SWITCH_MAP;

	// member variable
private:
	SWITCH_MAP m_SwitchMap;

	// member function
public:
	int Update(CScene::EVENT_VEC* _pEventVec);

	void CreateSwitch(const wstring& _strSwitchKey);
	void SwitchOn(const wstring& _strSwitchKey);
	void SwitchOff(const wstring& _strSwitchKey);
	bool IsSwitchOn(const wstring& _strSwitchKey);
private:
	bool CheckEventConditions(CGameEvent* _pEvent);
	void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CEventManager(void);
	~CEventManager(void);
};
END_NAMESPACE

#endif // EventManager_h__