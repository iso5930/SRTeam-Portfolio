#include "OBBCollision.h"

#include "Export_Function.h"

#include "Pipeline.h"
#include "Transform.h"
#include "MathManager.h"

ENGINE::COBBCollision::COBBCollision(ENGINE::CGameObject* _pOwner)
:CCollision(_pOwner)
,m_pBoundingBox(NULL)
,m_pOwnersInfo(NULL)
,m_pOwnersMovement(NULL)
,m_pColFunctor(NULL)
,m_bPlayer(false)
,m_bWall(false)
{
}

ENGINE::COBBCollision::~COBBCollision(void)
{
	Release();
}

ENGINE::COBBCollision* ENGINE::COBBCollision::Create(ENGINE::CGameObject* _pOwner,
													 ENGINE::CTransform* _pOwnersInfo,
													 ENGINE::CMovement* _pOwnersMovement, 
													 float _fScaleX /*= 1.f*/,
													 float _fScaleY /*= 1.f*/,
													 float _fScaleZ /*= 1.f*/,
													 CCollisionFunctor* _pColFunctor /*= NULL*/,
													 bool _bPlayer /*= false*/,
													 bool _bWall /*= false*/)
{
	COBBCollision* pInstance = new COBBCollision(_pOwner);
	HRESULT hr = pInstance->Initialize(_pOwnersInfo, _pOwnersMovement, _fScaleX, _fScaleY, _fScaleZ, _pColFunctor, _bPlayer, _bWall);
	if FAILED(hr)
		SAFE_DELETE(pInstance);

	return pInstance;
}

int ENGINE::COBBCollision::Update(void)
{
	// set obb info
	m_tOBBInfo.vPos = m_pOwnersInfo->m_vPos;
	if (!m_bWall)
		m_tOBBInfo.vPos.y -= (1.f - m_tOBBInfo.fRadius[ANGLE_TYPE_Y]);

	//D3DXVECTOR3 vDir = m_pOwnersInfo->m_vDir;
	D3DXVECTOR3 vDir = D3DXVECTOR3(0.f, 0.f, 1.f);
	vDir.y = 0.f;
	D3DXVec3Normalize(&vDir, &vDir);
	float fCos = D3DXVec3Dot(&vDir, &D3DXVECTOR3(0.f, 0.f, 1.f));
	m_tOBBInfo.pAngle[ANGLE_TYPE_Y] = acosf(fCos);
	if (vDir.x < 0)
		m_tOBBInfo.pAngle[ANGLE_TYPE_Y] = D3DX_PI * 2.f - m_tOBBInfo.pAngle[ANGLE_TYPE_Y];
	D3DXMatrixRotationY(&m_tOBBInfo.matRotationY, m_tOBBInfo.pAngle[ANGLE_TYPE_Y]);

	// 반경은 init때 했음..

	if (m_bWall)
		return 0;

	ENGINE::GetManagement()->PrepareFind();
	while (1)
	{
		CComponent* pComponent = ENGINE::GetManagement()->GetComponent(L"OBBCollision");
		//! 현재, getcomponent가 자기자신을 리턴할 때의 예외처리가 되어있지 않다..
		if (pComponent == this)
			continue;
		if (pComponent == NULL)
			break;

		const COBBCollision::OBB_INFO* pOtherOBB = static_cast<const COBBCollision*>(pComponent)->GetOBBInfo();
		if (pOtherOBB->pColOwnersFunctor == NULL)
			continue;

		// 필드에서 뛰어다니는 플레이어끼리는 충돌처리 하지 않음
		if (m_bPlayer && static_cast<const COBBCollision*>(pComponent)->IsPlayers())
			continue;

		D3DXVECTOR3 vNormal(0.f, 0.f, 0.f);
		if (CollisionCheck(pOtherOBB, &vNormal))
		{
			//! 하하 막장이다 막장!!!
			(*pOtherOBB->pColOwnersFunctor)(const_cast<ENGINE::CGameObject*>(this->GetOwner()),
				const_cast<ENGINE::CGameObject*>(pComponent->GetOwner()),
				&vNormal);
			
			// reset obb info
			m_tOBBInfo.vPos = m_pOwnersInfo->m_vPos;
			if (!m_bWall)
				m_tOBBInfo.vPos.y -= (1.f - m_tOBBInfo.fRadius[ANGLE_TYPE_Y]);
		}
	}

	return 0;
}

void ENGINE::COBBCollision::Render(void)
{
	if (!ENGINE::GetInputManager()->IsDrawBoundingBox())
		return;

	ENGINE::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// create world matrix
	//! update 시점에선 collision이 transform보다 나중에 update된다고 장담할 수가 없어서 굳이 여기에..
	ENGINE::CPipeline::MakeWorldMatrix(&m_matWorld,
									   &D3DXVECTOR3(m_tOBBInfo.fRadius[ANGLE_TYPE_X],
													m_tOBBInfo.fRadius[ANGLE_TYPE_Y],
													m_tOBBInfo.fRadius[ANGLE_TYPE_Z]),
									   m_tOBBInfo.pAngle,
									   &m_tOBBInfo.vPos);
	ENGINE::GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);

	ENGINE::GetDevice()->SetTexture(0, NULL);
	m_pBoundingBox->Render();

	ENGINE::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT ENGINE::COBBCollision::Initialize(ENGINE::CTransform* _pOwnersInfo,
										  ENGINE::CMovement* _pOwnersMovement, 
								  float _fScaleX /*= 1.f*/,
								  float _fScaleY /*= 1.f*/,
								  float _fScaleZ /*= 1.f*/,
								  CCollisionFunctor* _pColFunctor /*= NULL*/,
								  bool _bPlayer /*= false*/,
								  bool _bWall /*= false*/)
{
	CComponent* pComponent = ENGINE::GetResourceManager()->CloneResource(m_pOwner, RESOURCE_TYPE_STATIC, L"Buffer_Cube_Color");
	m_pBoundingBox = static_cast<ENGINE::CVIBuffer*>(pComponent);

	m_pColFunctor = _pColFunctor;

	// obb의 각 축별 반경
	// cube-color의 축별 반경이 전부 1이기 때문에 가능.
	m_tOBBInfo.fRadius[ANGLE_TYPE_X] = _fScaleX;
	m_tOBBInfo.fRadius[ANGLE_TYPE_Y] = _fScaleY;
	m_tOBBInfo.fRadius[ANGLE_TYPE_Z] = _fScaleZ;
	// 나랑 충돌했을때, 상대에게 제공할 펑터를 연결..
	m_tOBBInfo.pColOwnersFunctor = m_pColFunctor;

	m_pOwnersInfo = _pOwnersInfo;
	m_pOwnersMovement = _pOwnersMovement;

	m_bPlayer = _bPlayer;
	m_bWall = _bWall;

	return S_OK;
}

bool ENGINE::COBBCollision::CollisionCheck(const OBB_INFO* _pOtherOBB, D3DXVECTOR3* _pNormal)
{
	D3DXMATRIX matMyInverse;
	D3DXMatrixInverse(&matMyInverse, NULL, &m_tOBBInfo.matRotationY);
	D3DXMATRIX matRotation = matMyInverse * _pOtherOBB->matRotationY;

	// 두 OBB 중점 사이의 벡터 준비
	D3DXVECTOR3 vDist = _pOtherOBB->vPos - m_tOBBInfo.vPos;

	// 상대의 법선 벡터를 구하기 위하여..
	float fOverlapped = FLT_MAX;
	D3DXVECTOR3 vNormal(0.f, 0.f, 0.f);

	// case 1, my AxisX
	if (abs(vDist.x) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_X] +
		_pOtherOBB->fRadius[ANGLE_TYPE_X] * abs(matRotation._11) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Y] * abs(matRotation._12) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Z] * abs(matRotation._13))
	{
		//cout << endl;
		return false;
	}
	//cout << "1 ";

	// case 2, my AxisY
	if (abs(vDist.y) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_Y] +
		_pOtherOBB->fRadius[ANGLE_TYPE_X] * abs(matRotation._21) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Y] * abs(matRotation._22) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Z] * abs(matRotation._23))
	{
		//cout << endl;
		return false;
	}
	//cout << "2 ";

	// case 3, my AxisZ
	if (abs(vDist.z) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_Z] +
		_pOtherOBB->fRadius[ANGLE_TYPE_X] * abs(matRotation._31) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Y] * abs(matRotation._32) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Z] * abs(matRotation._33))
	{
		//cout << endl;
		return false;
	}
	//cout << "3 ";

	// case 4, other's AxisX
	if (abs(vDist.x) * abs(matRotation._11) +
		abs(vDist.y) * abs(matRotation._21) +
		abs(vDist.z) * abs(matRotation._31) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._11) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._21) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._31) +
		_pOtherOBB->fRadius[ANGLE_TYPE_X])
	{
		//cout << endl;
		return false;
	}
	// 그렇다면, 이 물체는 상대의 x+면이나, x-면에 들이받은게 된다..
	else
	{
		// 얼마를 겹쳤는지, 조사한다..
		float _fOverlapped = (m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._11) +
			m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._21) +
			m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._31) +
			_pOtherOBB->fRadius[ANGLE_TYPE_X]) -
			(abs(vDist.x) * abs(matRotation._11) +
			abs(vDist.y) * abs(matRotation._21) +
			abs(vDist.z) * abs(matRotation._31));
		//cout << "overlap x : " << _fOverlapped << " ";
		if (_fOverlapped < fOverlapped)
		{
			fOverlapped = _fOverlapped;

			if (m_tOBBInfo.vPos.x < _pOtherOBB->vPos.x)
			{
				// 이 물체는 상대를 x-면에 들이받았다..
				// 내 vPos를 직접 수정할 것이므로 상대의 월드에서의 회전값을 곱해준다..
				D3DXVec3TransformNormal(&vNormal, &D3DXVECTOR3(-1.f, 0.f, 0.f), &_pOtherOBB->matRotationY);
			}
			else
			{
				// 이 물체는 상대를 x+면에 들이받았다..
				D3DXVec3TransformNormal(&vNormal, &D3DXVECTOR3(1.f, 0.f, 0.f), &_pOtherOBB->matRotationY);
			}
		}
	}
	//cout << "4 ";

	// case 5, other's AxisY
	if (abs(vDist.x) * abs(matRotation._12) +
		abs(vDist.y) * abs(matRotation._22) +
		abs(vDist.z) * abs(matRotation._32) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._12) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._22) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._32) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Y])
	{
		//cout << endl;
		return false;
	}
	// 그렇다면, 이 물체는 상대의 y+면이나, y-면에 들이받은게 된다..
	else
	{
		// 얼마를 겹쳤는지, 조사한다..
		float _fOverlapped = (m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._12) +
			m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._22) +
			m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._32) +
			_pOtherOBB->fRadius[ANGLE_TYPE_Y]) -
			(abs(vDist.x) * abs(matRotation._12) +
			abs(vDist.y) * abs(matRotation._22) +
			abs(vDist.z) * abs(matRotation._32));
		//cout << "overlap y : " << _fOverlapped << " ";
		if (_fOverlapped < fOverlapped)
		{
			fOverlapped = _fOverlapped;

			if (m_tOBBInfo.vPos.y < _pOtherOBB->vPos.y)
			{
				// 이 물체는 상대를 y-면에 들이받았다..
				D3DXVec3TransformNormal(&vNormal, &D3DXVECTOR3(0.f, -1.f, 0.f), &_pOtherOBB->matRotationY);
			}
			else
			{
				// 이 물체는 상대를 y+면에 들이받았다..
				D3DXVec3TransformNormal(&vNormal, &D3DXVECTOR3(0.f, 1.f, 0.f), &_pOtherOBB->matRotationY);
			}
		}
	}
	//cout << "5 ";

	// case 6, other's AxisZ
	if (abs(vDist.x) * abs(matRotation._13) +
		abs(vDist.y) * abs(matRotation._23) +
		abs(vDist.z) * abs(matRotation._33) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._13) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._23) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._33) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Z])
	{
		//cout << endl;
		return false;
	}
	// 그렇다면, 이 물체는 상대의 z+면이나, z-면에 들이받은게 된다..
	else
	{
		// 얼마를 겹쳤는지, 조사한다..
		float _fOverlapped = (m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._13) +
			m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._23) +
			m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._33) +
			_pOtherOBB->fRadius[ANGLE_TYPE_Z]) -
			(abs(vDist.x) * abs(matRotation._13) +
			abs(vDist.y) * abs(matRotation._23) +
			abs(vDist.z) * abs(matRotation._33));
		//cout << "overlap z : " << _fOverlapped << " ";
		if (_fOverlapped < fOverlapped)
		{
			fOverlapped = _fOverlapped;

			if (m_tOBBInfo.vPos.z < _pOtherOBB->vPos.z)
			{
				// 이 물체는 상대를 z-면에 들이받았다..
				D3DXVec3TransformNormal(&vNormal, &D3DXVECTOR3(0.f, 0.f, -1.f), &_pOtherOBB->matRotationY);
			}
			else
			{
				// 이 물체는 상대를 z+면에 들이받았다..
				D3DXVec3TransformNormal(&vNormal, &D3DXVECTOR3(0.f, 0.f, 1.f), &_pOtherOBB->matRotationY);
			}
		}
	}
	//cout << "6 ";

	// case 7, my AxisX  X  other's AxisX
	if (-1 * abs(vDist.y) * abs(matRotation._31) +
		abs(vDist.z) * abs(matRotation._21) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._31) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._21) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Y] * abs(matRotation._13) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Z] * abs(matRotation._12))
	{
		//cout << endl;
		return false;
	}
	//cout << "7 ";

	// case 8, my AxisX  X  other's AxisY
	if (-1 * abs(vDist.y) * abs(matRotation._32) +
		abs(vDist.z) * abs(matRotation._22) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._32) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._22) +
		_pOtherOBB->fRadius[ANGLE_TYPE_X] * abs(matRotation._13) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Z] * abs(matRotation._11))
	{
		//cout << endl;
		return false;
	}
	//cout << "8 ";

	// case 9, my AxisX  X  other's AxisZ
	if (-1 * abs(vDist.y) * abs(matRotation._33) +
		abs(vDist.z) * abs(matRotation._23) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._33) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._23) +
		_pOtherOBB->fRadius[ANGLE_TYPE_X] * abs(matRotation._12) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Y] * abs(matRotation._11))
	{
		//cout << endl;
		return false;
	}
	//cout << "9 ";

	// case 10, my AxisY  X  other's AxisX
	if (abs(vDist.x) * abs(matRotation._31) +
		-1 * abs(vDist.z) * abs(matRotation._11) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._31) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._11) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Y] * abs(matRotation._23) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Z] * abs(matRotation._22))
	{
		//cout << endl;
		return false;
	}
	//cout << "A ";

	// case 11, my AxisY  X  other's AxisY
	if (abs(vDist.x) * abs(matRotation._32) +
		-1 * abs(vDist.z) * abs(matRotation._12) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._32) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._12) +
		_pOtherOBB->fRadius[ANGLE_TYPE_X] * abs(matRotation._23) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Z] * abs(matRotation._21))
	{
		//cout << endl;
		return false;
	}
	//cout << "B ";

	// case 12, my AxisY  X  other's AxisZ
	if (abs(vDist.x) * abs(matRotation._33) +
		-1 * abs(vDist.z) * abs(matRotation._13) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._33) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Z] * abs(matRotation._13) +
		_pOtherOBB->fRadius[ANGLE_TYPE_X] * abs(matRotation._22) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Y] * abs(matRotation._21))
	{
		//cout << endl;
		return false;
	}
	//cout << "C ";

	// case 13, my AxisZ  X  other's AxisX
	if (-1 * abs(vDist.x) * abs(matRotation._21) +
		abs(vDist.y) * abs(matRotation._11) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._21) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._11) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Y] * abs(matRotation._33) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Z] * abs(matRotation._32))
	{
		//cout << endl;
		return false;
	}
	//cout << "D ";

	// case 14, my AxisZ  X  other's AxisY
	if (-1 * abs(vDist.x) * abs(matRotation._22) +
		abs(vDist.y) * abs(matRotation._12) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._22) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._12) +
		_pOtherOBB->fRadius[ANGLE_TYPE_X] * abs(matRotation._33) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Z] * abs(matRotation._31))
	{
		//cout << endl;
		return false;
	}
	//cout << "E ";

	// case 15, my AxisZ  X  other's AxisZ
	if (-1 * abs(vDist.x) * abs(matRotation._23) +
		abs(vDist.y) * abs(matRotation._13) >
		m_tOBBInfo.fRadius[ANGLE_TYPE_X] * abs(matRotation._23) +
		m_tOBBInfo.fRadius[ANGLE_TYPE_Y] * abs(matRotation._13) +
		_pOtherOBB->fRadius[ANGLE_TYPE_X] * abs(matRotation._32) +
		_pOtherOBB->fRadius[ANGLE_TYPE_Y] * abs(matRotation._31))
	{
		//cout << endl;
		return false;
	}
	//cout << "F " << endl;

	// 여기까지 내려왔다는 건, 충돌이 실제로 일어났다는 것.
	// 여기서 구한 법선벡터를 밖으로 던져줘야 한다..
	*_pNormal = vNormal;
	//cout << endl;
	//cout << "overlap : " << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;

	return true;
}

void ENGINE::COBBCollision::Release(void)
{
	SAFE_DELETE(m_pBoundingBox);

	SAFE_DELETE(m_pColFunctor);
}

const ENGINE::COBBCollision::OBB_INFO* ENGINE::COBBCollision::GetOBBInfo(void) const
{
	return &m_tOBBInfo;
}

bool ENGINE::COBBCollision::IsPlayers(void) const
{
	return m_bPlayer;
}
