/*!
 * \file Water.h
 * \date 2016/06/19 21:19
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief ½Åµ¿À±
 *
 * TODO: long description
 *
 * \note
*/
#ifndef Water_h__
#define Water_h__

#include "Client_Include.h"
#include "etc.h"

namespace ENGINE
{
	class CTerrainInfo;
}
class CWater : public ENGINE::Cetc
{
private:
	float					m_fSpeed;
	float					m_fTime;

	float					m_fDistance;
	float					m_fCameraAngle;

	float					m_fHight;
	bool					m_bControl;

private:
	void		MySetTransForm(void);

private:
	HRESULT		Initialize(void);
	HRESULT		Initialize(D3DXVECTOR3 _vPos, float fStart);
	void		SetDirection(void);
	HRESULT		AddComponent(void);

public:
	static	CWater*	Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos, float fStart);

	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

	void	SetPos(const D3DXVECTOR3& vPos);

private:
	explicit CWater(eObjectType _eObjectType);
public:
	virtual ~CWater();

};


#endif // Water_h__