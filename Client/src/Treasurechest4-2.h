/*!
 * \file Treasurechest4B.h
 * \date 2016/06/19 21:19
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief �ŵ���
 *
 * TODO: long description
 *
 * \note
*/
#ifndef Treasurechest4B_h__
#define Treasurechest4B_h__

#include "Client_Include.h"
#include "etc.h"

namespace ENGINE
{
	class CTerrainInfo;
	class CGroupObserver;

	class CMouseCollision;
	class COBBCollision;
}
class CTreasurechest4B : public ENGINE::Cetc
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
	static	CTreasurechest4B*	Create(eObjectType _eObjectType, D3DXVECTOR3 _vPos, int iFrame);

	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

	void	SetPos(const D3DXVECTOR3& vPos);

private:
	explicit CTreasurechest4B(eObjectType _eObjectType);
public:
	virtual ~CTreasurechest4B();

};


#endif // Treasurechest4B_h__