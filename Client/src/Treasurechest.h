/*!
 * \file Treasurechest.h
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
#ifndef Treasurechest_h__
#define Treasurechest_h__

#include "Client_Include.h"
#include "etc.h"

namespace ENGINE
{
	class CTerrainInfo;
	class CGroupObserver;

	class CMouseCollision;
	class COBBCollision;
}
class CTreasurechest : public ENGINE::Cetc
{
private:
	ENGINE::CGroupObserver* m_pGroupObserver;
	D3DXVECTOR3				m_vPosSave;
	D3DXVECTOR3				m_vTagPos;

	float					m_fSpeed;
	float					m_fTime;

	float					m_fDistance;
	float					m_fCameraAngle;

	float					m_fOpen;
	bool					m_bOpen;
	float					m_fOpenSave;
	bool					m_bControl;

	int						m_iFrame;

	ENGINE::CMouseCollision* m_pMouseCollision;
	ENGINE::COBBCollision* m_pOBBCollision;

private:
	void		MySetTransForm(void);

private:
	HRESULT		Initialize(void);
	HRESULT		Initialize(D3DXVECTOR3 _vPos, int iFrame);
	void		SetDirection(void);
	HRESULT		AddComponent(void);

public:
	static	CTreasurechest*	Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos, int iFrame);

	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

	void	SetPos(const D3DXVECTOR3& vPos);

private:
	explicit CTreasurechest(eObjectType _eObjectType);
public:
	virtual ~CTreasurechest();

};


#endif // Treasurechest_h__