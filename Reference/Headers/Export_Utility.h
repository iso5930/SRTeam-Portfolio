/*!
 * \file Export_Utility.h
 * \date 2016/06/09 5:05
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

#ifndef Export_Utility_h__
#define Export_Utility_h__

#include "Management.h"
#include "InfoSubject.h"
#include "EventManager.h"

BEGIN_NAMESPACE(ENGINE)

inline CManagement* GetManagement(void);
inline CInfoSubject* GetInfoSubject(void);
inline CEventManager* GetEventManager(void);

#include "Export_Utility.inl"

END_NAMESPACE

#endif // Export_Utility_h__