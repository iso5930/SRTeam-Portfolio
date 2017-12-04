/*!
 * \file StaticCamera.h
 * \date 2016/06/04 16:43
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 //! ī�޶��� ������..
 �÷��̾��� �̵��ӵ��� ���� ���ݾ� Ȯ��, ��Ұ� �̷�����.
 ���콺 ��Ŭ�� �� �巡�� & ����� ���� ī�޶� y�� ȸ��(���� ȸ������ �÷��̾� ��ġ)�� �̷�����.
 ���콺 ��Ŭ���� ���� �÷��̾� �̵��� �÷��̾ ���󰣴�. 
 �� �߾Ӻ��� ��¦ ���� �÷��̾ ��ġ�ϵ��� ����� �ִ�..
 ȭ�� ��Ʈ�Ӹ����� ���� ���� �� �÷��̾ �߾ӿ��� ��Ż�Ѵ� -> ī�޶� �� �� �ִ� ���� �Ѱ谡 �ִ� �� ���δ�.
*/

#ifndef StaticCamera_h__
#define StaticCamera_h__

#include "Client_Include.h"
#include "Camera.h"

namespace ENGINE
{
	class CTransform;
	class CTerrainCollision;
	class CMouseCollision;
	class COBBCollision;

	class CTerrainInfo;
}
class CStaticCamera : public ENGINE::CCamera
{
	enum eVi {VI_0, VI_1, VI_2, VI_3};
	// member variable
private:
	ENGINE::CTransform* m_pInfo;
	const ENGINE::CTransform* m_pTargetInfo;
	float m_fTargetDistance;
	float m_fTargetDistanceSave;
	float m_fAngle;
	float fX;
	ENGINE::COBBCollision* m_pOBBCollision;
	float m_f25;

private:
	float	m_fSpeed;
	POINT	m_ptMouseScroll; // ���콺 ��ġ�� ����ϴ� ����
	bool	m_bKeyInput;
	bool	m_bLeftTurnCheak;
	bool	m_bRightTurnCheak;
	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vAt;
	float	m_fInertiaCamera;
	bool	m_bHighAngle;
	bool	m_bHighAngleFinal;
	float	m_fAngleYSave;
	float	m_fAngleYSave2;
	bool	m_bHighChange;
	eVi		eVir;
	bool	m_bCameraStop;

	ENGINE::CTerrainInfo* m_pTerrainInfo;

	// member function
public:
	static CStaticCamera* Create(eObjectType _eObjectType, ENGINE::CTerrainInfo* _pTerrainInfo);
	virtual int Update(void);
private:
	virtual HRESULT Initialize(void);
	void KeyCheck(void);
	void MouseScroll(void);
	void KeyScroll(void);
	HRESULT AddComponent(void);
	virtual void Release(void);

	// getter & setter
public:
	void SetTargetToPlayer(void);
	void SetTargetInfo(const ENGINE::CTransform* _pTargetInfo);

	// constructor & destructor
private:
	explicit CStaticCamera(eObjectType _eObjectType, ENGINE::CTerrainInfo* _pTerrainInfo);
public:
	virtual ~CStaticCamera(void);
	MAKE_UNCOPYABLE(CStaticCamera)
};

#endif // StaticCamera_h__