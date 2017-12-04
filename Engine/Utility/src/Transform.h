/*!
 * \file Transform.h
 * \date 2016/05/29 3:51
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Transform_h__
#define Transform_h__

#include "Engine_Include.h"
#include "Component.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CTransform : public CComponent
{
	// member variable
public:
	float m_pAngle[ANGLE_TYPE_END];
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vDir;
	D3DXMATRIX m_matWorld;
	D3DXVECTOR3 m_vScale; //! �߰��� ������, �̰� �������� �� OBB�� �ùٸ��� �۵����� ���� �Ŷ�� ������ ��..

	// member function
public:
	static CTransform* Create(ENGINE::CGameObject* _pOwner);
	virtual int Update(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CTransform(ENGINE::CGameObject* _pOwner);
public:
	virtual ~CTransform(void);
MAKE_UNCOPYABLE(CTransform)
};
END_NAMESPACE

#endif // Transform_h__