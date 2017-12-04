#include "Magic.h"

#include "Export_Function.h"

ENGINE::CMagic::CMagic(eObjectType _eObjectType)
:CAbility(_eObjectType)
{

}

ENGINE::CMagic::~CMagic(void)
{
	Release();
}

ENGINE::CMagic* ENGINE::CMagic::Create(eObjectType _eObjectType, const wstring& _wstrName, eAbilityType _AbiliType1, int _iAbili1, eAbilityType _AbiliType2 /*= ABILITY_END*/, int _iAbili2 /*= 0*/, eAbilityType _AbiliType3 /*= ABILITY_END*/, int _iAbili3 /*= 0*/)
{	
	CMagic* pMagic = new CMagic(_eObjectType);

	if(FAILED(pMagic->Initialize(_wstrName, _AbiliType1, _iAbili1, _AbiliType2, _iAbili2, _AbiliType3, _iAbili3)))
	{
		SAFE_DELETE(pMagic);
	}

	return pMagic;
}

HRESULT ENGINE::CMagic::Initialize(const wstring& _wstrName, eAbilityType _AbiliType1, int _iAbili1, eAbilityType _AbiliType2 /*= ABILITY_END*/, int _iAbili2 /*= 0*/, eAbilityType _AbiliType3 /*= ABILITY_END*/, int _iAbili3 /*= 0*/)
{
	m_vecAbilityType.push_back(_AbiliType1);
	m_vecAbilityValue.push_back(_iAbili1);

	if(_AbiliType2 != ABILITY_END)
	{
		m_vecAbilityType.push_back(_AbiliType2);
		m_vecAbilityValue.push_back(_iAbili2);

		if(_AbiliType3 != ABILITY_END)
		{
			m_vecAbilityType.push_back(_AbiliType3);
			m_vecAbilityValue.push_back(_iAbili3);
		}
	}

	m_wstrAbilityName = _wstrName;

	return S_OK;
}

HRESULT ENGINE::CMagic::Initialize(void)
{
	return S_OK;
}

int ENGINE::CMagic::Update(void)
{	
	return 0;
}

void ENGINE::CMagic::Render(void)
{
	/*if(m_dwTime + 200 < GetTickCount())
	{
		m_dwTime = GetTickCount();

		if(++m_tAbiliIconFrame.iCurFrame > m_tAbiliIconFrame.iEndFrame)
		{
			m_tAbiliIconFrame.iCurFrame = m_tAbiliIconFrame.iStartFrame;
		}
	}*/

	m_tAbiliIconFrame.fCurFrame += m_tAbiliIconFrame.fFrameTime * ENGINE::GetTimeDelta();

	if(m_tAbiliIconFrame.fCurFrame > m_tAbiliIconFrame.fEndFrame)
	{
		m_tAbiliIconFrame.fCurFrame = m_tAbiliIconFrame.fStartFrame;
	}

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 251.f, m_fY, 0.f);

	ENGINE::GetSprite()->SetTransform(&matTrans);

	if(m_bField)
	{
		ENGINE::GetFont()->DrawTextW(ENGINE::GetSprite(), m_wstrAbilityName.c_str(), lstrlen(m_wstrAbilityName.c_str()), NULL, NULL, D3DCOLOR_ARGB(255, 0, 0, 0));
	}
	else
	{
		ENGINE::GetFont()->DrawTextW(ENGINE::GetSprite(), m_wstrAbilityName.c_str(), lstrlen(m_wstrAbilityName.c_str()), NULL, NULL, D3DCOLOR_ARGB(255, 93, 87, 71));
	}

	float fX = 149.f; //<- 이름 시작 지점.
	
	for(size_t i = 0; i < m_vecAbilityType.size(); ++i)
	{
		if(m_vecAbilityType[i] == ABILITY_END)
		{
			break;
		}

		TEXINFO* pTexInfo = NULL;

		switch(m_vecAbilityType[i])
		{
		case ABILITY_FIRE:
			pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"FireMagicIcon", (DWORD)m_tAbiliIconFrame.fCurFrame);
			break;

		case ABILITY_WATER:
			pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"IceMagicIcon", (DWORD)m_tAbiliIconFrame.fCurFrame);
			break;

		case ABILITY_WIND:
			pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"WindMagicIcon", (DWORD)m_tAbiliIconFrame.fCurFrame);
			break;

		case ABILITY_EARTH:
			pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"돌MagicIcon", (DWORD)m_tAbiliIconFrame.fCurFrame);
			break;
		}

		D3DXMatrixTranslation(&matTrans, 624.f - (i * 51.f), m_fY + 10.f, 0.f);
		ENGINE::GetSprite()->SetTransform(&matTrans);
		ENGINE::GetSprite()->Draw(pTexInfo->pTexture, NULL, &D3DXVECTOR3(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		

		D3DXMatrixTranslation(&matTrans, 643.f - (i * 53.f), m_fY, 0.f);
		ENGINE::GetSprite()->SetTransform(&matTrans);

		TCHAR szAbility[10] = L"";

		_itow_s(m_vecAbilityValue[i], szAbility, 10);
		if(m_bField)
		{
			ENGINE::GetFont()->DrawTextW(ENGINE::GetSprite(), szAbility, lstrlen(szAbility), NULL, NULL, D3DCOLOR_ARGB(255, 0, 0, 0));
		}
		else
		{
			ENGINE::GetFont()->DrawTextW(ENGINE::GetSprite(), szAbility, lstrlen(szAbility), NULL, NULL, D3DCOLOR_ARGB(255, 93, 87, 71));
		}
	}
}

void ENGINE::CMagic::Release(void)
{

}