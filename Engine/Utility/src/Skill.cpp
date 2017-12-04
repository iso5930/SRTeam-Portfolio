#include "Skill.h"

#include "Export_Function.h"

ENGINE::CSkill::CSkill(eObjectType _eObjectType)
:CAbility(_eObjectType)
{

}

ENGINE::CSkill::~CSkill(void)
{
	Release();
}

ENGINE::CSkill* ENGINE::CSkill::Create(eObjectType _eObjectType, const wstring& _wstrName, eAbilityType _AbiliType1, int _iAbili1, eAbilityType _AbiliType2 /*= ABILITY_END*/, int _iAbili2 /*= 0*/, eAbilityType _AbiliType3 /*= ABILITY_END*/, int _iAbili3 /*= 0*/)
{
	CSkill* pSkill = new CSkill(_eObjectType);

	if(FAILED(pSkill->Initialize(_wstrName, _AbiliType1, _iAbili1, _AbiliType2, _iAbili2, _AbiliType3, _iAbili3)))
	{
		SAFE_DELETE(pSkill);
	}

	return pSkill;
}

HRESULT ENGINE::CSkill::Initialize(void)
{
	return S_OK;
}

HRESULT ENGINE::CSkill::Initialize(const wstring& _wstrName, eAbilityType _AbiliType1, int _iAbili1, eAbilityType _AbiliType2 /*= ABILITY_END*/, int _iAbili2 /*= 0*/, eAbilityType _AbiliType3 /*= ABILITY_END*/, int _iAbili3 /*= 0*/)
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

int ENGINE::CSkill::Update(void)
{
	//업데이트를 돌리면 해당하는 스킬이 발동이 되는 형식?
	//스킬.....
	//아... 이거 어떻하지...

	

	return 0;
}

void ENGINE::CSkill::Render(void)
{
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 251.f, m_fY, 0.f);

	ENGINE::GetSprite()->SetTransform(&matTrans);

	ENGINE::GetFont()->DrawTextW(ENGINE::GetSprite(), m_wstrAbilityName.c_str(), lstrlen(m_wstrAbilityName.c_str()), NULL, NULL, D3DCOLOR_ARGB(255, 93, 87, 71));

	float fX = 149.f; //<- 이름 시작 지점.

	for(size_t i = 0; i < m_vecAbilityType.size(); ++i)
	{
		if(m_vecAbilityType[i] == ABILITY_END)
		{
			break;
		}

		TEXINFO* pTexInfo = NULL;

		pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"AbilityType", m_vecAbilityType[i]);
	
		D3DXMatrixTranslation(&matTrans, 624.f - (i * 70.f), m_fY + 10.f, 0.f);
		ENGINE::GetSprite()->SetTransform(&matTrans);
		ENGINE::GetSprite()->Draw(pTexInfo->pTexture, NULL, &D3DXVECTOR3(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		D3DXMatrixTranslation(&matTrans, 643.f - (i * 70.f), m_fY, 0.f);
		ENGINE::GetSprite()->SetTransform(&matTrans);

		TCHAR szAbility[10] = L"";

		_itow_s(m_vecAbilityValue[i], szAbility, 10);
		
		ENGINE::GetFont()->DrawTextW(ENGINE::GetSprite(), szAbility, lstrlen(szAbility), NULL, NULL, D3DCOLOR_ARGB(255, 93, 87, 71));
	}
}

void ENGINE::CSkill::Release(void)
{

}