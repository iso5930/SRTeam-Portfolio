/*!
 * \file OBBCollision.h
 * \date 2016/06/11 3:11
 *
 * \author ������
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef OBBCollision_h__
#define OBBCollision_h__

#include "Engine_Include.h"
#include "Collision.h"
#include "CollisionFunctors.h"

//! �ٿ�� �ڽ��� �ʿ��ϴٸ�, �� �༮�� ������Ʈ�� ���� �־�� �Ѵ�..
// ������ ������...................
// ��ŷ�ҷ��� �̳༮ �� �־�� ��!
BEGIN_NAMESPACE(ENGINE)
class CVIBuffer;
class CTransform;
class ENGINE_DLL_SPECIFIER COBBCollision : public CCollision
{
public:
	typedef struct tagOBBInfo
	{
		D3DXVECTOR3 vPos;
		float fRadius[ANGLE_TYPE_END];
		float pAngle[ANGLE_TYPE_END];
		D3DXMATRIX matRotationY;
		CCollisionFunctor* pColOwnersFunctor;

		tagOBBInfo(void)
			:vPos(0.f, 0.f, 0.f)
			,pColOwnersFunctor(NULL)
		{
			ZeroMemory(pAngle, sizeof(pAngle));
			ZeroMemory(fRadius, sizeof(float) * ANGLE_TYPE_END);
		}
	} OBB_INFO;

	// member variable
private:
	CVIBuffer* m_pBoundingBox;
	D3DXMATRIX m_matWorld;

	OBB_INFO m_tOBBInfo;

	CTransform* m_pOwnersInfo;
	CMovement* m_pOwnersMovement;


	CCollisionFunctor* m_pColFunctor;

	bool m_bPlayer;
	bool m_bWall;

	// member function
public:
	// scale���� 0���� ū ���� �־�� ��..
	static COBBCollision* Create(ENGINE::CGameObject* _pOwner, CTransform* _pOwnersInfo, CMovement* _pOwnersMovement, float _fScaleX = 1.f, float _fScaleY = 1.f, float _fScaleZ = 1.f, CCollisionFunctor* _ColFunctor = NULL, bool _bPlayer = false, bool _bWall = false);
	virtual int Update(void);
	void Render(void);
private:
	HRESULT Initialize(CTransform* _pOwnersInfo, CMovement* _pOwnersMovement, float _fScaleX = 1.f, float _fScaleY = 1.f, float _fScaleZ = 1.f, CCollisionFunctor* _ColFunctor = NULL, bool _bPlayer = false, bool _bWall = false);
	bool CollisionCheck(const COBBCollision::OBB_INFO* _pOtherOBB, D3DXVECTOR3* _pNormal);
	void Release(void);

	// getter & setter
public:
	const OBB_INFO* GetOBBInfo(void) const;
	bool IsPlayers(void) const;
	bool IsWall(void) const
	{
		return m_bWall;
	}

	// constructor & destructor
private:
	explicit COBBCollision(ENGINE::CGameObject* _pOwner);

public:
	virtual ~COBBCollision(void);
};
END_NAMESPACE

#endif // OBBCollision_h__