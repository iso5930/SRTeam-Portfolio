/*!
 * \file Tile.h
 * \date 2016/06/04 17:59
 *
 * \author ¼­ÇÏ´Ã
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#pragma once

namespace ENGINE
{
	class CTransform;
	class CVIBuffer;
	class CTexture;
}

#include "GameObject.h"

class CTile : public ENGINE::CGameObject
{
private:
	ENGINE::CTransform* m_pInfo;
	ENGINE::CVIBuffer* m_pVIBuffer;
	ENGINE::CTexture* m_pTexture;

public:
	virtual int Update(void);
	virtual void Render(void);
	virtual HRESULT Initialize(void);
	virtual void Release(void);	

public:
	CTile(void);
	~CTile(void);


};
