#include "Page.h"

#include "Export_Function.h"

ENGINE::CPage::CPage(ENGINE::CGameObject* _pOwner, LPD3DXSPRITE pSprite)
:CComponent(_pOwner)
,m_pSprite(pSprite)
{
	
}

ENGINE::CPage::~CPage(void)
{

}

int ENGINE::CPage::Update(void)
{
	return 0;
}

void ENGINE::CPage::Render(void)
{

}

void ENGINE::CPage::SetMousePos(POINT _ptMouse)
{
	m_ptMouse = _ptMouse;
}

void ENGINE::CPage::DrawFont(char* _pName, float _fX, float _fY, float _fIntervalX, float _fIntervalY)
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

		if(iChar == 'p')
		{
			vCenter.y = (pTexInfo->ImgInfo.Height / 2.f) + 3.f;
		}

		D3DXMatrixTranslation(&matTrans, _fX + (i * _fIntervalX), _fY + (i * _fIntervalY), 0.f);

		m_pSprite->SetTransform(&matTrans);

		m_pSprite->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void ENGINE::CPage::DrawSprite(eResourceType _eResourceType, const TCHAR* _ResourceKey, float _fX, float _fY, const int _iCnt, const RECT* _rcRect)
{
	TEXINFO* pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(_eResourceType, _ResourceKey, _iCnt);

	D3DXVECTOR3 vCenter(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f);

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, _fX, _fY, 0.f);

	m_pSprite->SetTransform(&matTrans);

	m_pSprite->Draw(pTexInfo->pTexture, _rcRect, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void ENGINE::CPage::DrawText(TCHAR* _pText, D3DCOLOR _Color, float _fX, float _fY)
{
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, _fX, _fY, 0.f);

	m_pSprite->SetTransform(&matTrans);

	ENGINE::GetFont()->DrawTextW(m_pSprite, _pText, lstrlen(_pText), NULL, NULL, _Color);
}

void ENGINE::CPage::DrawFont_Int(int _iText, float _fX, float _fY, float _fIntervalX, float _fIntervalY)
{
	char szName[50] = "";

	_itoa_s(_iText, szName, 10);

	TEXINFO* pTexInfo = NULL;

	D3DXVECTOR3 vCenter(0.f, 0.f, 0.f);
	D3DXMATRIX matTrans;

	float fCenterX = 0.f;
	float fCenterY = 0.f;

	int iLength = strlen(szName);

	for(int i = 0; i < iLength; ++i)
	{
		int iChar = szName[i];

		if(iChar == ' ')
		{
			continue;
		}

		if(iChar <= 57)
		{
			iChar -= 48; //0 ~ 9
		}

		pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"Font", iChar);

		fCenterX = (float)pTexInfo->ImgInfo.Width;
		fCenterY = (float)pTexInfo->ImgInfo.Height;

		vCenter.x = 0.f;
		vCenter.y = fCenterY;

		D3DXMatrixTranslation(&matTrans, _fX + (i * _fIntervalX), _fY + (i * _fIntervalY), 0.f);

		m_pSprite->SetTransform(&matTrans);

		m_pSprite->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void ENGINE::CPage::BarTextDraw(int _iPoint, int _iMaxPoint, float _fX, float _fY, float _fIntervalX, float _fIntervalY)
{
	char szFullName[50] = "";
	char szName[50] = "";

	_itoa_s(_iPoint, szName, 10);
	strcat_s(szFullName, szName);

	strcat_s(szFullName, "/");

	_itoa_s(_iMaxPoint, szName, 10);
	strcat_s(szFullName, szName);

	DrawFont(szFullName, _fX, _fY, _fIntervalX, _fIntervalY);
}