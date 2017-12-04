/*!
 * \file StaticCamera.h
 * \date 2016/06/04 16:43
 *
 * \author 박정민
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 //! 카메라의 움직임..
 플레이어의 이동속도에 따라서 조금씩 확대, 축소가 이뤄진다.
 마우스 우클릭 후 드래그 & 드랍에 의해 카메라 y축 회전(실제 회전축은 플레이어 위치)이 이뤄진다.
 마우스 좌클릭에 의한 플레이어 이동시 플레이어를 따라간다. 
 정 중앙보다 살짝 위에 플레이어를 위치하도록 만들고 있다..
 화면 끄트머리같은 곳을 만날 시 플레이어가 중앙에서 이탈한다 -> 카메라가 갈 수 있는 곳에 한계가 있는 듯 보인다.
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
	POINT	m_ptMouseScroll; // 마우스 위치를 기록하는 변수
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