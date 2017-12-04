/*!
 * \file Wall.h
 * \date 2016/06/23 2:10
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
#ifndef Wall_h__
#define Wall_h__

#include "Client_Include.h"
#include "etc.h"

namespace ENGINE
{
	class CTerrainInfo;
	class COBBCollision;
}
class CWall : public ENGINE::Cetc
{
private:
	float					m_fSpeed;
	float					m_fTime;

	float					m_fDistance;
	float					m_fCameraAngle;

	float					m_fAngle;
	int						m_iNum;

	ENGINE::COBBCollision* m_pOBBCollision;

private:
	void		MySetTransForm(void);

private:
	HRESULT		Initialize(void);
	HRESULT		Initialize(D3DXVECTOR3 _vPos, int iNum, float fAngle);
	void		SetDirection(void);
	HRESULT		AddComponent(void);

public:
	static	CWall*	Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos, int iNum, float fAngle);

	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

	void	SetPos(const D3DXVECTOR3& vPos);

private:
	explicit CWall(eObjectType _eObjectType);
public:
	virtual ~CWall();

};


#endif // Wall_h__