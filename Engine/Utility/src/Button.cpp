#include "Button.h"

#include "Export_Function.h"

#include "MainUIObserver.h"
#include "SubPageObserver.h"

ENGINE::CButton::CButton(ENGINE::CGameObject* _pOwner)
:CComponent(_pOwner)
{

}

ENGINE::CButton::~CButton(void)
{
	Release();
}

ENGINE::CButton* ENGINE::CButton::Create(ENGINE::CGameObject* _pOwner, const D3DXVECTOR3& _vPos, const float& _fCX, const float& _fCY, eButtonType _eType/* = BUTTON_END*/)
{
	CButton* pButton = new CButton(_pOwner);

	if(FAILED(pButton->Init(_vPos, _fCX, _fCY, _eType)))
	{
		SAFE_DELETE(pButton);
	}

	return pButton;
}

HRESULT ENGINE::CButton::Init(const D3DXVECTOR3& _vPos, const float& _fCX, const float& _fCY, eButtonType _eType/* = BUTTON_END*/)
{
	m_rcButton.left		= long(_vPos.x - _fCX / 2.f);
	m_rcButton.right	= long(_vPos.x + _fCX / 2.f);
	m_rcButton.top		= long(_vPos.y - _fCY / 2.f);
	m_rcButton.bottom	= long(_vPos.y + _fCY / 2.f);

	m_fX = _vPos.x;
	m_fY = _vPos.y;

	m_eButtonType = _eType;

	m_pObserver = CMainUIObserver::Create(m_pOwner);
	ENGINE::GetInfoSubject()->Subscribe(m_pObserver);

	m_pSubObserver = CSubPageObserver::Create(m_pOwner);
	ENGINE::GetInfoSubject()->Subscribe(m_pSubObserver);

	return S_OK;
}

void ENGINE::CButton::Release(void)
{
	SAFE_DELETE(m_pSubObserver);
	SAFE_DELETE(m_pObserver);
}

int ENGINE::CButton::Update(void)
{
	eCharacterID eCharID = m_pSubObserver->GetCharCur();

	if(eCharID == CHARACTER_MARIA && m_eButtonType == BUTTON_MAGIC)
	{
		return 0;
	}
	else if(eCharID == CHARACTER_SIZZ && m_eButtonType == BUTTON_SKILL)
	{
		return 0;
	}

	if(PtInRect(&m_rcButton, m_ptMouse))
	{
		return 1;
	}

	return 0;
}

void ENGINE::CButton::Render(void)
{
	if(m_eButtonType == BUTTON_END)
	{
		return;
	}

	eCharacterID eCharID = m_pSubObserver->GetCharCur();

	if(eCharID == CHARACTER_MARIA && m_eButtonType == BUTTON_MAGIC)
	{
		return;
	}
	else if(eCharID == CHARACTER_SIZZ && m_eButtonType == BUTTON_SKILL)
	{
		return;
	}
	else if(eCharID == CHARACTER_ELLUARD && m_eButtonType == BUTTON_MAGIC)
	{
		return;
	}
	else if(eCharID == CHARACTER_TENZI && m_eButtonType == BUTTON_MAGIC)
	{
		return;
	}

	if(m_pObserver->GetLeftIndex() == 0)
	{	
		TEXINFO* pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"ButtonIcon", m_eButtonType);

		float fX = pTexInfo->ImgInfo.Width / 2.f;
		float fY = pTexInfo->ImgInfo.Width / 2.f;

		D3DXVECTOR3 vCenter;
		D3DXMATRIX matTrans;

		vCenter.x = fX;
		vCenter.y = fY;
		vCenter.z = 0.f;

		D3DXMatrixTranslation(&matTrans, m_fX, m_fY, 0.f);

		ENGINE::GetSprite()->SetTransform(&matTrans);
		ENGINE::GetSprite()->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		switch(m_eButtonType)
		{
		case BUTTON_STATUS:
			DrawFont("Status", 400 - 152, 300 - 205, 8.f, 0.f);
			break;

		case BUTTON_ITEM:
			DrawFont("Item", 400 - 61, 300 - 205, 8.f, 0.f);
			break;

		case BUTTON_EQUIP:
			DrawFont("Equip", 400 + 9, 300 - 205, 8.f, 0.f);
			break;

		case BUTTON_MAGIC:
			DrawFont("Magic", 400 + 81, 300 - 205, 9.f, 0.f);
			break;

		case BUTTON_SKILL:
			DrawFont("Skill", 400 + 168, 300 - 205, 8.f, 0.f);
			break;
		}
	}
	else if(m_pObserver->GetLeftIndex() == 1)
	{
		int iCur = m_eButtonType + 5;

		if(iCur >= BUTTON_END)
		{
			return;
		}

		TEXINFO* pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"ButtonIcon", iCur);

		float fX = pTexInfo->ImgInfo.Width / 2.f;
		float fY = pTexInfo->ImgInfo.Width / 2.f;

		D3DXVECTOR3 vCenter;
		D3DXMATRIX matTrans;

		vCenter.x = fX;
		vCenter.y = fY;
		vCenter.z = 0.f;

		D3DXMatrixTranslation(&matTrans, m_fX, m_fY, 0.f);

		ENGINE::GetSprite()->SetTransform(&matTrans);
		ENGINE::GetSprite()->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		switch(m_eButtonType)
		{
		case BUTTON_DIARY_ITEM:
			DrawFont("Item", 400 - 152, 300 - 200, 8.f, 0.f);
			break;

		case BUTTON_DIARY_MONSTER:
			DrawFont("Monster", 400 - 61, 300 - 200, 8.f, 0.f);
			break;

		case BUTTON_DIARY_SCRAP:
			DrawFont("Scrap", 400 + 9, 300 - 200, 8.f, 0.f);
			break;
		}
	}
}

RECT* ENGINE::CButton::GetButton(void)
{
	return &m_rcButton;
}

void ENGINE::CButton::SetMousePos(POINT _ptMouse)
{
	m_ptMouse = _ptMouse;
}

void ENGINE::CButton::DrawFont(char* _pName, float _fX, float _fY, float _fIntervalX, float _fIntervalY)
{
	TEXINFO* pTexInfo = NULL;

	D3DXVECTOR3 vCenter(0.f, 0.f, 0.f);
	D3DXMATRIX matTrans;

	float fCenterX = 0.f;
	float fCenterY = 0.f;

	int iLength = strlen(_pName);

	for(int i = 0; i < iLength; ++i)
	{
		int iChar = _pName[i];

		if(iChar == ' ')
		{
			continue;
		}

		if(iChar == '/')
		{
			iChar = 62;
		}
		else if(iChar == '.')
		{
			iChar = 63;
		}
		else if(iChar <= 57)
		{
			iChar -= 48; //0 ~ 9
		}
		else if(iChar <= 90)
		{
			iChar -= 55; // A ~ Z
		}
		else if(iChar <= 122)
		{
			iChar -= 61; //a ~ z
		}

		pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"Font", iChar);

		fCenterX = (float)pTexInfo->ImgInfo.Width;
		fCenterY = (float)pTexInfo->ImgInfo.Height;

		vCenter.x = 0.f;
		vCenter.y = fCenterY;

		iChar = _pName[i];

		if(iChar == 'p' || iChar == 'q' || iChar == 'g')
		{
			vCenter.y = (pTexInfo->ImgInfo.Height / 2.f) + 3.f;
		}
		
		D3DXMatrixTranslation(&matTrans, _fX + (i * _fIntervalX), _fY + (i * _fIntervalY), 0.f);

		ENGINE::GetSprite()->SetTransform(&matTrans);

		ENGINE::GetSprite()->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}