/*!
 * \file Stage5.h
 * \date 2016/05/24 21:16
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Stage5_h__
#define Stage5_h__

#include "Client_Include.h"
#include "Stage.h"

class CStage5 : public CStage
{
	// member variable
private:
	// -

	// member function
public:
	static CStage5* Create(CScene* _pScene = NULL);
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
	explicit CStage5(void);
public:
	~CStage5(void);
	MAKE_UNCOPYABLE(CStage5)
};

#endif // Stage5_h__