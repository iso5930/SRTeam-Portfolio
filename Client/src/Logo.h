/*!
 * \file Logo.h
 * \date 2016/05/24 21:14
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

#ifndef Logo_h__
#define Logo_h__

#include "Client_Include.h"
#include "Scene.h"

class CLogo : public ENGINE::CScene	
{
private:
	enum eLayerID
	{
		LAYER_ID_LOGO
	};

	// member variable
private:
	// -

	// member function
public:
	static CLogo* Create(CScene* _pScene = NULL);
	virtual int Update(void);
	virtual void Render(void);

	virtual HRESULT LoadDynamicResources(void);
	virtual HRESULT CreateDynamicObjects(void);
	void ResetEvent(void)
	{

	}
private:
	virtual HRESULT Initialize(CScene* _pScene = NULL);
	HRESULT AddObject(void);
	virtual void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CLogo(void);
public:
	~CLogo(void);
MAKE_UNCOPYABLE(CLogo)
};

#endif // Logo_h__