/*!
 * \file Stage1.h
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

#ifndef Stage1_h__
#define Stage1_h__

#include "Client_Include.h"
#include "Stage.h"

class CStage1 : public CStage
{
	// member variable
private:
	// -
public:
	// member function
public:
	static CStage1* Create(CScene* _pScene = NULL);
	virtual int Update(void);
	virtual void Render(void);

	virtual HRESULT LoadDynamicResources(void);
	virtual HRESULT CreateDynamicObjects(void);
	void ResetEvent(void);
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
	explicit CStage1(void);
public:
	~CStage1(void);
MAKE_UNCOPYABLE(CStage1)
};

#endif // Stage1_h__