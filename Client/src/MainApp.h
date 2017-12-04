/*!
 * \file MainApp.h
 * \date 2016/05/23 20:10
 *
 * \author ¹ÚÁ¤¹Î
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef MainApp_h__
#define MainApp_h__

#include "Client_Include.h"

class CMainApp
{
	// member variable
private:
	// -

	// member function
public:
	static CMainApp* Create(void);
	int Update(void);
	void Render(void);
private:
	HRESULT Initialize(void);
	void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CMainApp(void);
public:
	~CMainApp(void);
MAKE_UNCOPYABLE(CMainApp)
};

#endif // MainApp_h__