/*!
 * \file Stage2.h
 * \date 2016/05/24 21:16
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

#ifndef Stage2_h__
#define Stage2_h__

#include "Client_Include.h"
#include "Stage.h"

class CStage2 : public CStage
{
	// member variable
private:
	// -

	// member function
public:
	static CStage2* Create(CScene* _pScene = NULL);
	virtual int Update(void);
	virtual void Render(void);

	virtual HRESULT LoadDynamicResources(void);
	virtual HRESULT CreateDynamicObjects(void);
	void ResetEvent();
private:
	virtual HRESULT Initialize(CScene* _pScene = NULL);
	HRESULT AddEnvironmentLayerObject(void);
	HRESULT AddIngameLayerObject(void);
	HRESULT AddUIAndCursorLayerObject(void);
	virtual void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CStage2(void);
public:
	~CStage2(void);
	MAKE_UNCOPYABLE(CStage2)
};

#endif // Stage2_h__