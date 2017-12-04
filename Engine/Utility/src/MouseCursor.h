/*!
 * \file MouseCursor.h
 * \date 2016/06/18 7:19
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

#ifndef MouseCursor_h__
#define MouseCursor_h__

#include "Engine_Include.h"
#include "GameObject.h"

BEGIN_NAMESPACE(ENGINE)
class CCollisionFunctor;
class ENGINE_DLL_SPECIFIER CMouseCursor : public CGameObject
{
	// member variable
private:
	float m_fClosest;
	CCollisionFunctor* m_pColFunctor;

	// member function
public:
	static CMouseCursor* Create(eObjectType _eObjectType);
	virtual int Update(void);
	virtual void Render(void);
private:
	virtual HRESULT Initialize(void);
	virtual void Release(void);

	// getter & setter
public:
	float GetClosestDist(void);
	void SetPickingInfo(float _fClosest, CCollisionFunctor* _pColFunctor);

	// constructor & destructor
private:
	explicit CMouseCursor(eObjectType _eObjectType);
public:
	~CMouseCursor(void);
	MAKE_UNCOPYABLE(CMouseCursor)
};
END_NAMESPACE

#endif // MouseCursor_h__