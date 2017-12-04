/*!
 * \file RectangleWave.h
 * \date 2016/06/20 7:07
 *
 * \author ½Åµ¿À±
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef RectangleWave_h__
#define RectangleWave_h__

#include "Engine_Include.h"
#include "VIBuffer.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CRectangleWave : public CVIBuffer
{
	// member variable
private:
	// -
	float		m_fHight;

	// member function
public:
	static CRectangleWave* Create(DWORD _dwCountX, DWORD _dwCountZ, DWORD _dwInterval);
private:
	HRESULT Initialize(DWORD _dwCountX, DWORD _dwCountZ, DWORD _dwInterval);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CRectangleWave(void);
public:
	virtual ~CRectangleWave(void);
};
END_NAMESPACE

#endif // RectangleWave_h__