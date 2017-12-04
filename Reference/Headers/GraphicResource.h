/*!
 * \file GraphicResource.h
 * \date 2016/05/25 4:07
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

#ifndef GraphicResource_h__
#define GraphicResource_h__

#include "Engine_Include.h"
#include "Component.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CGraphicResource : public CComponent
{
	// member variable
protected:
	DWORD* m_pReferenceCount;

	// member function
public:
	// index�� buffer������ �Ⱦ���, texture������ ����.
	virtual void Render(int _iIndex = -1) PURE;
	virtual CGraphicResource* CloneResource(ENGINE::CGameObject* _pOwner) PURE;
protected:
	void Release(void);

	// getter & setter
public:
	void SetOwner(ENGINE::CGameObject* _pOwner);

	// constructor & destructor
protected:
	explicit CGraphicResource(void);
public:
	virtual ~CGraphicResource(void) PURE;
};
END_NAMESPACE

#endif // GraphicResource_h__