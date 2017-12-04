/*!
 * \file Export_System.h
 * \date 2016/06/09 4:02
 *
 * \author ¹ÚÁ¤¹Î
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Export_System_h__
#define Export_System_h__

#include "GraphicDevice.h"
#include "TimeManager.h"
#include "CustomTimer.h"
#include "InputManager.h"
#include "BattleManager.h"
#include "SoundManager.h"

BEGIN_NAMESPACE(ENGINE)

inline CGraphicDevice* GetDeviceManager(void);
inline const LPDIRECT3DDEVICE9 GetDevice(void);
inline const LPD3DXSPRITE GetSprite(void);
inline const LPD3DXFONT GetFont(void);

inline CTimeManager* GetTimeManager(void);
inline const float GetTimeDelta(void);
inline const CCustomTimer* GetTimer(const wstring& _strTimerKey);

inline CInputManager* GetInputManager(void);
inline CBattleManager* GetBattleManeger(void);

inline CSoundManager* GetSoundManager(void);

#include "Export_System.inl"

END_NAMESPACE

#endif // Export_System_h__