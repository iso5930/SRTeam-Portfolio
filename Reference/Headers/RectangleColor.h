/*!
 * \file RectangleColor.h
 * \date 2016/05/25 2:17
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

#ifndef RectangleColor_h__
#define RectangleColor_h__

#include "Engine_Include.h"
#include "VIBuffer.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CRectangleColor : public CVIBuffer
{
	// member variable
private:
	// -

	// member function
public:
	static CRectangleColor* Create(void);
private:
	HRESULT Initialize(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CRectangleColor(void);
public:
	virtual ~CRectangleColor(void);
};
END_NAMESPACE

#endif // RectangleColor_h__