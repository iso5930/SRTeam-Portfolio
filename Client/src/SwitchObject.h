/*!
 * \file SwitchObject.h
 * \date 2016/06/17 0:27
 *
 * \author 박정민
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 //! 한장짜리 이미지만 렌더됨 일단,
 //! 다이나믹 텍스쳐만 받을 수 있음
 //! 각종 컴포넌트들이 추가되기 시작하면?? 상속내려 쓸까..
 //! 렌더 스테이트 설정..
*/

#ifndef SwitchObject_h__
#define SwitchObject_h__

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

	class CCollisionFunctor;
}
class CSwitchObject : public ENGINE::CGameObject
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

	ENGINE::CCollisionFunctor* m_pFunctor;

	// member function
public:
	static CSwitchObject* Create(eObjectType _eObjectType, const wstring& _strTextureKey, ENGINE::CCollisionFunctor* _pFunctor);
	virtual int Update(void);
	virtual void Render(void);
private:
	virtual HRESULT Initialize(void);
	HRESULT AddComponent(void);
	virtual void Release(void);

	// getter & setter
public:
	void SetTextureKey(const wstring& _strTextureKey);
	void SetPos(float _fX, float _fZ); //! 임시로..

	// constructor & destructor
private:
	explicit CSwitchObject(eObjectType _eObjectType, ENGINE::CCollisionFunctor* _pFunctor);
public:
	~CSwitchObject(void);
	MAKE_UNCOPYABLE(CSwitchObject)
};

#endif // SwitchObject_h__