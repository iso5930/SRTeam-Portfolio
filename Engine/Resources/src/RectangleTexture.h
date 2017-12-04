/*!
 * \file RectangleTexture.h
 * \date 2016/05/27 9:37
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

#ifndef RectangleTexture_h__
#define RectangleTexture_h__

#include "Engine_Include.h"
#include "VIBuffer.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CRectangleTexture : public CVIBuffer
{
	// member variable
private:
	// -

	// member function
public:
	static CRectangleTexture* Create(void);
private:
	HRESULT Initialize(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CRectangleTexture(void);
public:
	virtual ~CRectangleTexture(void);
};
END_NAMESPACE

#endif // RectangleTexture_h__