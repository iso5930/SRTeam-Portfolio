/*!
 * \file TriangleColor.h
 * \date 2016/05/25 1:33
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

#ifndef TriangleColor_h__
#define TriangleColor_h__

#include "Engine_Include.h"
#include "VIBuffer.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CTriangleColor : public CVIBuffer
{
	// member variable
private:
	// -

	// member function
public:
	static CTriangleColor* Create(void);
private:
	HRESULT Initialize(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CTriangleColor(void);
public:
	virtual ~CTriangleColor(void);
};
END_NAMESPACE

#endif // TriangleColor_h__