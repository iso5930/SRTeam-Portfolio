/*!
 * \file CubeColor.h
 * \date 2016/06/11 3:37
 *
 * \author ������
 * Contact: user@company.com
 *
 * \brief �浹�ڽ����Դϴ�
 *
 * TODO: long description
 *
 * \note
*/

#ifndef CubeColor_h__
#define CubeColor_h__

#include "Engine_Include.h"
#include "VIBuffer.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CCubeColor : public CVIBuffer
{
	// member variable
private:
	// -

	// member function
public:
	static CCubeColor* Create(void);
private:
	HRESULT Initialize(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CCubeColor(void);
public:
	virtual ~CCubeColor(void);
};
END_NAMESPACE

#endif // CubeColor_h__