/*!
 * \file CubeTexture.h
 * \date 2016/06/05 19:45
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

#ifndef CubeTexture_h__
#define CubeTexture_h__

#include "Engine_Include.h"
#include "VIBuffer.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CCubeTexture : public CVIBuffer
{
	// member variable
private:
	// -

	// member function
public:
	static CCubeTexture* Create(void);
private:
	HRESULT Initialize(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CCubeTexture(void);
public:
	virtual ~CCubeTexture(void);
};
END_NAMESPACE

#endif // CubeTexture_h__