/*!
 * \file RectangleTerrain.h
 * \date 2016/05/27 9:56
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

#ifndef RectangleTerrain_h__
#define RectangleTerrain_h__

#include "Engine_Include.h"
#include "VIBuffer.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CRectangleTerrain : public CVIBuffer
{
	// member variable
private:
	// -

	// member function
public:
	static CRectangleTerrain* Create(DWORD _dwCountX, DWORD _dwCountZ, DWORD _dwInterval);
private:
	HRESULT Initialize(DWORD _dwCountX, DWORD _dwCountZ, DWORD _dwInterval);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CRectangleTerrain(void);
public:
	virtual ~CRectangleTerrain(void);
};
END_NAMESPACE

#endif // RectangleTerrain_h__