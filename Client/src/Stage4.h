/*!
 * \file Stage4.h
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

#ifndef Stage4_h__
#define Stage4_h__

#include "Client_Include.h"
#include "Stage.h"

class CStage4 : public CStage
{
	// member variable
private:
	// -

	// member function
public:
	static CStage4* Create(CScene* _pScene = NULL);
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
	explicit CStage4(void);
public:
	~CStage4(void);
	MAKE_UNCOPYABLE(CStage4)
};

#endif // Stage4_h__