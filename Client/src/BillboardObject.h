/*!
 * \file BillboardObject.h
 * \date 2016/06/17 0:27
 *
 * \author ������
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 //! ����¥�� �̹����� ������ �ϴ�,
 //! ���̳��� �ؽ��ĸ� ���� �� ����
 //! ���� ������Ʈ���� �߰��Ǳ� �����ϸ�?? ��ӳ��� ����..
 //! ���� ������Ʈ ����..
*/

#ifndef BillboardObject_h__
#define BillboardObject_h__

#include "Client_Include.h"
#include "GameObject.h"

namespace ENGINE
{
	class CTransform;
	class CVIBuffer;
	class CTexture;
	class CTerrainCollision;
	class CMouseCollision;
	class COBBCollision;
}
class CBillboardObject : public ENGINE::CGameObject
{
	// member variable
private:
	ENGINE::CVIBuffer* m_pBuffer;
	ENGINE::CTexture* m_pTexture;

	ENGINE::CTransform* m_pInfo;

	ENGINE::CTerrainCollision* m_pTerrainCollision;
	ENGINE::CMouseCollision* m_pMouseCollision;
	ENGINE::COBBCollision* m_pOBBCollision;

	wstring m_strTextureKey;
	// member function
public:
	static CBillboardObject* Create(eObjectType _eObjectType, const wstring& _strTextureKey);
	virtual int Update(void);
	virtual void Render(void);
private:
	virtual HRESULT Initialize(void);
	HRESULT AddComponent(void);
	virtual void Release(void);

	// getter & setter
public:
	void SetTextureKey(const wstring& _strTextureKey);
	void SetPos(float _fX, float _fZ); //! �ӽ÷�..
	int		SetAngle(void);
	// constructor & destructor
private:
	explicit CBillboardObject(eObjectType _eObjectType);
public:
	~CBillboardObject(void);
	MAKE_UNCOPYABLE(CBillboardObject)
};

#endif // BillboardObject_h__