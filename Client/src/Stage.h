/*!
 * \file Stage.h
 * \date 2016/06/17 7:42
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

#ifndef Stage_h__
#define Stage_h__

#include "Client_Include.h"
#include "Scene.h"

class CPlaneObject;
class CStage : public ENGINE::CScene
{
protected:
	enum eLayerID
	{
		LAYER_ID_ENVIRONMENT,
		LAYER_ID_INGAME,
		LAYER_ID_UI,
		LAYER_ID_CURSOR
	};

	static bool m_bStaticsLoaded;

	static CPlaneObject* m_pTalkbox;
	static CPlaneObject* m_pSizzTalk;
	static CPlaneObject* m_pMariaTalk;
	static CPlaneObject* m_pElluardTalk;
	static CPlaneObject* m_pTenziTalk;

	// member variable
private:
	// -

	// member function
public:
	virtual int Update(void) PURE;
	virtual void Render(void) PURE;

	virtual HRESULT LoadDynamicResources(void) PURE;
	virtual HRESULT CreateDynamicObjects(void) PURE;
protected:
	virtual HRESULT Initialize(CScene* _pScene = NULL) PURE;
	virtual void Release(void) PURE;

	HRESULT AddStatics(CScene* _pScene = NULL);
private:
	HRESULT CreateLayers(void);
	HRESULT AddStaticObjects(void);
	HRESULT LoadIngameStaticTextures(void);
	HRESULT LoadIngameUIResources(void);

	// getter & setter
public:
	// -

	// constructor & destructor
protected:
	explicit CStage(void);
public:
	~CStage(void) PURE;
	MAKE_UNCOPYABLE(CStage)
};

#endif // Stage_h__