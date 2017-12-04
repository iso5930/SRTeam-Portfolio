#include "stdafx.h"

#include "StaticCamera.h"
#include "Transform.h"

#include "Export_Function.h"
#include "OBBCollision.h"
#include "CharacterGroup.h"
#include "Character.h"

#include "TerrainInfo.h"

#include "MainMenu.h"


CStaticCamera::CStaticCamera(eObjectType _eObjectType, ENGINE::CTerrainInfo* _pTerrainInfo)
:CCamera(_eObjectType)
,m_pTargetInfo(NULL)
,m_pInfo(NULL)
,m_fTargetDistance(0.f)
,m_fAngle(0.f)
,m_bLeftTurnCheak(false)
,m_bRightTurnCheak(false)
,fX(0.f)
,m_fInertiaCamera(0.f)
,m_f25(0.f)
,m_bHighAngle(false)
,m_fAngleYSave(0.f)
,m_fAngleYSave2(0.f)
,m_bHighChange(false)
,m_bHighAngleFinal(false)
,eVir(VI_0)
,m_fTargetDistanceSave(0.f)
,m_bCameraStop(false)
,m_pTerrainInfo(_pTerrainInfo)
{

}

CStaticCamera::~CStaticCamera(void)
{
	Release();
}

CStaticCamera* CStaticCamera::Create(eObjectType _eObjectType, ENGINE::CTerrainInfo* _pTerrainInfo)
{
	CStaticCamera* pInstance = new CStaticCamera(_eObjectType, _pTerrainInfo);
	HRESULT hr = pInstance->Initialize();
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int CStaticCamera::Update(void)
{
	KeyCheck();

	MouseScroll();

	if(m_pInfo->m_pAngle[ANGLE_TYPE_Y] >= 6.283f)
		m_pInfo->m_pAngle[ANGLE_TYPE_Y] = 0.f;
	if(m_pInfo->m_pAngle[ANGLE_TYPE_Y] <= -0.785375f)
		m_pInfo->m_pAngle[ANGLE_TYPE_Y] = 5.497625f;

	m_vEye = m_pInfo->m_vDir * -1;
	D3DXVec3Normalize(&m_vEye, &m_vEye);
	m_vEye *= m_fTargetDistance;

	D3DXVECTOR3 vRight;
	memcpy(&vRight, m_pInfo->m_matWorld.m[0], sizeof(float) * 3);

	D3DXMATRIX matRotAxis;
	D3DXMatrixRotationAxis(&matRotAxis, &vRight, m_fAngle);
	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRotAxis);

	m_vEye += m_pTargetInfo->m_vPos;
	m_vAt	= m_pTargetInfo->m_vPos;

	CCamera::SetViewSpaceMatrix(&m_vEye, &m_vAt, &D3DXVECTOR3(0.f, 1.f, 0.f));
	CCamera::SetProjectionMatrix(D3DXToRadian(45.f), float(WINCX) / WINCY, 1.f, 1000.f);

	ENGINE::GetInfoSubject()->Notify(MESSAGE_CAMERA_VIEW);
	ENGINE::GetInfoSubject()->Notify(MESSAGE_CAMERA_PROJECTION);
	ENGINE::GetInfoSubject()->Notify(MESSAGE_CAMERA_INFO);

	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &D3DXVECTOR3(0.f, 0.f, 1.f), &m_pInfo->m_matWorld);
	D3DXVec3Normalize(&m_pInfo->m_vDir, &m_pInfo->m_vDir);

	if(m_bHighAngleFinal == false)
	{
		m_fAngleYSave = m_pInfo->m_pAngle[ANGLE_TYPE_Y];
		m_fAngleYSave2 = m_fAngleYSave;
		m_pInfo->m_vPos.x = 0.f;
	}
	else
		m_pInfo->m_vPos.x = 1.f;
		// 카메라 포지션은 몇이던 어차피 캐릭터 중심으로 보여주니까 위에서 보기를 하고있는지 안 하고 있는지를 포지션 값으로 설정

	if(m_bHighAngleFinal == true && m_bHighAngle == false && m_pInfo->m_pAngle[ANGLE_TYPE_X] == 0.f)
	{
		float fTimeDelta = ENGINE::GetTimeDelta();

		if(m_fAngleYSave <= 3.1415f && m_fAngleYSave > 0.f && eVir != VI_2 && eVir != VI_3)
		{
			eVir = VI_1;
			m_fAngleYSave -= D3DXToRadian(10.f) * fTimeDelta * m_fSpeed * 10.f;
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] += D3DXToRadian(10.f) * fTimeDelta * m_fSpeed * 10.f;
		}
		else if(m_fAngleYSave >= 3.1415f && m_fAngleYSave < 6.283f && eVir != VI_1 && eVir != VI_3)
		{
			eVir = VI_2;
			m_fAngleYSave += D3DXToRadian(10.f) * fTimeDelta * m_fSpeed * 10.f;
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] -= D3DXToRadian(10.f) * fTimeDelta * m_fSpeed * 10.f;
		}
		else if(m_fAngleYSave < 0.f && m_fAngleYSave > -0.785375f && eVir != VI_2 && eVir != VI_1)
		{
			eVir = VI_3;
			m_fAngleYSave += D3DXToRadian(10.f) * fTimeDelta * m_fSpeed * 10.f;
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] -= D3DXToRadian(10.f) * fTimeDelta * m_fSpeed * 10.f;
		}
		if(eVir == VI_0 && m_fAngleYSave == 0.f)
		{
			m_bCameraStop = true;
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] = m_fAngleYSave2;
		}
		if(eVir == VI_1 && m_fAngleYSave <= 0.f)
		{
			m_bCameraStop = true;
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] = m_fAngleYSave2;
		}
		else if(eVir == VI_2 && m_fAngleYSave >= 6.283f)
		{
			m_bCameraStop = true;
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] = m_fAngleYSave2;
		}
		else if(eVir == VI_3 && m_fAngleYSave >= 6.283f)
		{
			m_bCameraStop = true;
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] = m_fAngleYSave2;
		}
	}

	ENGINE::CGameObject::Update();

	//! 이벤트 생기거나 한다면, 얘땜에 문제가 생기겠지, 카메라를 항상 플레이어에 고정시켜 놓으니..
	if(ENGINE::GetBattleManeger()->GetBattleStart() == false)
	{
		SetTargetToPlayer();
	}
	
	return 0;
}

HRESULT CStaticCamera::Initialize(void)
{
	//! 타겟 디스턴스 관련된 상수들..
	// 80000.f 빼고는 관련된 상수들 모두 1/3로 스케일링해놨다..
	m_fTargetDistance = 5.f;
	m_fTargetDistanceSave = m_fTargetDistance;
	m_fAngle = D3DXToRadian(45.f);

	m_fSpeed = 10.f;
	ENGINE::GetInfoSubject()->AddData(MESSAGE_CAMERA_VIEW, &m_matView);
	ENGINE::GetInfoSubject()->AddData(MESSAGE_CAMERA_PROJECTION, &m_matProj);

	ENGINE::GetInputManager()->GetMousePos(&m_ptMouseScroll);
	
	HRESULT hr = AddComponent();
	if FAILED(hr)
		return hr;

	ENGINE::GetInfoSubject()->AddData(MESSAGE_CAMERA_INFO, m_pInfo);

	return S_OK;
}

void CStaticCamera::KeyCheck(void)
{
	ENGINE::CGameObject* pMainMenu = ENGINE::GetManagement()->GetGameObject(L"ZZMainMenu");

	if(dynamic_cast<CMainMenu*>(pMainMenu)->GetUISwitch() == false)
	{
		return;
	}

	float fTimeDelta = ENGINE::GetTimeDelta();

	POINT ptMouse;
	ENGINE::GetInputManager()->GetMousePos(&ptMouse);

	if(m_bHighAngle == false)
	{
		if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_A))
		{
			if(m_fTargetDistance < m_fTargetDistanceSave + 0.33f)
				m_fTargetDistance += 6.66f * fTimeDelta;
		}
		else if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_Z))
		{
			if(m_fTargetDistance > m_fTargetDistanceSave - 0.33f)
				m_fTargetDistance -= 6.66f * fTimeDelta;
		}
		else
		{
			if(m_fTargetDistance > m_fTargetDistanceSave)
				m_fTargetDistance -= 13.33f * fTimeDelta;
			if(m_fTargetDistance < m_fTargetDistanceSave)
				m_fTargetDistance += 13.33f * fTimeDelta;
			if(int(m_fTargetDistance) == int(m_fTargetDistanceSave))
				m_fTargetDistance = m_fTargetDistanceSave;
		}

		if(m_pInfo->m_pAngle[ANGLE_TYPE_X] > 0.f)
			m_pInfo->m_pAngle[ANGLE_TYPE_X] -= 5.f * fTimeDelta;

		else if(m_pInfo->m_pAngle[ANGLE_TYPE_X] <= 0.f)
		{
			m_pInfo->m_pAngle[ANGLE_TYPE_X] = 0.f;

			if(m_fTargetDistance == m_fTargetDistanceSave)
			{
				if(m_bCameraStop == true)
				{
					m_bHighAngleFinal = false;
					m_bCameraStop = false;
				}
				eVir = VI_0;
			}
		}
	}
	else
	{
		if(m_fTargetDistance < 10.f)
			m_fTargetDistance += 10.f * fTimeDelta;

		if(m_bHighChange == false)
		{
			if(m_pInfo->m_pAngle[ANGLE_TYPE_Y] > 0.f)
				m_pInfo->m_pAngle[ANGLE_TYPE_Y] -= D3DXToRadian(10.f) * fTimeDelta * m_fSpeed * 10.f;
			if(m_pInfo->m_pAngle[ANGLE_TYPE_Y] <= 0.f)
				m_pInfo->m_pAngle[ANGLE_TYPE_Y] = 0.f;
		}

		if(m_bHighChange == true)
		{

			if(m_pInfo->m_pAngle[ANGLE_TYPE_Y] < 6.283f)
				m_pInfo->m_pAngle[ANGLE_TYPE_Y] += D3DXToRadian(10.f) * fTimeDelta * m_fSpeed * 10.f;
			if(m_pInfo->m_pAngle[ANGLE_TYPE_Y] > 0.f && m_pInfo->m_pAngle[ANGLE_TYPE_Y] < 1.f)
				m_pInfo->m_pAngle[ANGLE_TYPE_Y] = 0.f;
		}

		if(m_pInfo->m_pAngle[ANGLE_TYPE_Y] == 0)
		{
			if(m_pInfo->m_pAngle[ANGLE_TYPE_X] < 0.785375f)
				m_pInfo->m_pAngle[ANGLE_TYPE_X] += 5.f * fTimeDelta;
			if(m_pInfo->m_pAngle[ANGLE_TYPE_X] > 0.785375f)
				m_pInfo->m_pAngle[ANGLE_TYPE_X] = 0.785375f;
		}

		m_fInertiaCamera = 0.f;
		m_f25 = 0.25f;
	}

	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
	{
		float		fRoot = 0.f;
		fRoot = float(((WINCX / 2) - ptMouse.x) * ((WINCX / 2) - ptMouse.x)) + ((WINCY / 2) - ptMouse.y) * ((WINCY / 2) - ptMouse.y);
		
		m_fTargetDistanceSave = 5.f + (fRoot / 200000.f);
	}

	if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_Q) && m_bKeyInput == false)
	{
		m_pInfo->m_pAngle[ANGLE_TYPE_Y] -= D3DXToRadian(10.f) * m_fSpeed * fTimeDelta;
		m_bLeftTurnCheak = true;
		m_bRightTurnCheak = false;
		m_f25 = 1.038f;
		m_bKeyInput = true;
		m_bHighAngle = false;
	}
	else if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_W) && m_bKeyInput == false)
	{
		m_pInfo->m_pAngle[ANGLE_TYPE_Y] += D3DXToRadian(10.f) * m_fSpeed * fTimeDelta;
		m_bRightTurnCheak = true;
		m_bLeftTurnCheak = false;
		m_f25 = 1.038f;
		m_bKeyInput = true;
		m_bHighAngle = false;
	}

	if(ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_F5));
	else if (ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_RBUTTON))
	{
		m_bHighAngle = false;
		if(ptMouse.x < m_ptMouseScroll.x)
		{
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] -= D3DXToRadian(10.f) * m_fSpeed /* fTimeDelta*/ * (m_ptMouseScroll.x - ptMouse.x) * 0.004481f;//fTimeDelta과 상수중 택1
			m_bLeftTurnCheak = true;
			m_bRightTurnCheak = false;
			m_fInertiaCamera = float(m_ptMouseScroll.x - ptMouse.x);

			m_fInertiaCamera /= 2.f;

			if(m_fInertiaCamera > 6.f)
				m_fInertiaCamera = 6.f;
			if(m_fInertiaCamera < 2.f)
				m_fInertiaCamera = 0.f;
		}
		else if(ptMouse.x > m_ptMouseScroll.x)
		{
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] += D3DXToRadian(10.f) * m_fSpeed /* fTimeDelta*/ * (ptMouse.x - m_ptMouseScroll.x) * 0.004481f;
			m_bRightTurnCheak = true;
			m_bLeftTurnCheak = false;
			m_fInertiaCamera = float(ptMouse.x - m_ptMouseScroll.x);
			
			m_fInertiaCamera /= 2.f;

			if(m_fInertiaCamera > 6.f)
				m_fInertiaCamera = 6.f;
			if(m_fInertiaCamera < 2.f)
				m_fInertiaCamera = 0.f;
		}
	}
	else if (ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_LBUTTON))
	{
		
		if(m_bHighAngle == false && ptMouse.x >= 10.f && ptMouse.x <= 115.f
			&& ptMouse.y >= 10.f && ptMouse.y <= 115.f);
		else
			m_bHighAngle = false;
	}

	if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_F5) && m_bHighAngle == false)
	{
		m_bHighAngle = true;
		m_bHighAngleFinal = true;
		m_bHighAngleFinal = true;
		if(m_pInfo->m_pAngle[ANGLE_TYPE_Y] > 3.1415f || m_pInfo->m_pAngle[ANGLE_TYPE_Y] <= -0.785375f)
			m_bHighChange = true;
		else
			m_bHighChange = false;
	}
	else if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_LBUTTON) && m_bHighAngle == false)
	{
		if(ptMouse.x >= 10.f && ptMouse.x <= 115.f
			&& ptMouse.y >= 10.f && ptMouse.y <= 115.f)
		{
			m_bHighAngle = true;
			m_bHighAngleFinal = true;
			m_bHighAngleFinal = true;
			if(m_pInfo->m_pAngle[ANGLE_TYPE_Y] > 3.1415f || m_pInfo->m_pAngle[ANGLE_TYPE_Y] <= -0.785375f)
				m_bHighChange = true;
			else
				m_bHighChange = false;
		}
	}
	else if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_F5) && m_bHighAngle == true)
		m_bHighAngle = false;

	m_ptMouseScroll = ptMouse;
}

void CStaticCamera::MouseScroll()
{
	float fTimeDelta = ENGINE::GetTimeDelta();

	if(m_bLeftTurnCheak == true)
	{
		if(m_fInertiaCamera > 0.f)
		{
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] -= D3DXToRadian(10.f) * m_fInertiaCamera * fTimeDelta * 5.f;
			m_fInertiaCamera -= 0.025f;
		}

		if(m_f25 > 0.f)
		{
			m_f25 -= D3DXToRadian(10.f) * fTimeDelta * 10.f * m_f25;
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] -= D3DXToRadian(10.f) * fTimeDelta * 10.f * m_f25;
		}
	}
	else if(m_bRightTurnCheak == true)
	{
		if(m_fInertiaCamera > 0)
		{
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] += D3DXToRadian(10.f) * m_fInertiaCamera * fTimeDelta * 5.f;
			m_fInertiaCamera -= 0.025f;
		}

		if(m_f25 > 0.f)
		{
			m_f25 -= D3DXToRadian(10.f) * fTimeDelta * 10.f * m_f25;
			m_pInfo->m_pAngle[ANGLE_TYPE_Y] += D3DXToRadian(10.f) * fTimeDelta * 10.f * m_f25;
		}
	}

	if(m_fInertiaCamera <= 0.f && m_f25 <= 0.25f)
	{
		m_bLeftTurnCheak = false;
		m_bRightTurnCheak = false;
		m_bKeyInput = false;
		m_f25 = 0.f;
	}
}

HRESULT CStaticCamera::AddComponent(void)
{
	ENGINE::CComponent* pComponent = NULL;

	m_pInfo = ENGINE::CTransform::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"Transform", m_pInfo));

	return S_OK;
}

void CStaticCamera::Release(void)
{
}

void CStaticCamera::SetTargetToPlayer(void)
{
	ENGINE::CGameObject* pObject = ENGINE::GetManagement()->GetGameObject(L"CharacterGroup");
	if (pObject == NULL)
		return;

	ENGINE::CGameObject* pLeader = static_cast<ENGINE::CCharacterGroup*>(pObject)->GetLeaderCharacter();
	pLeader->PrepareFind();
	ENGINE::CComponent* pTransform = pLeader->GetComponent(L"Transform");

	m_pTargetInfo = static_cast<const ENGINE::CTransform*>(pTransform);
}

void CStaticCamera::SetTargetInfo(const ENGINE::CTransform* _pTargetInfo)
{
	m_pTargetInfo = _pTargetInfo;
}
