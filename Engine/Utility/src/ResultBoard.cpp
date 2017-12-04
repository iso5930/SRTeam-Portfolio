#include "ResultBoard.h"
#include "CharacterGroup.h"
#include "Export_Function.h"
#include "Character.h"

ENGINE::CResultBoard::CResultBoard(eObjectType _eObjectType)
:CGameObject(_eObjectType), m_bCreate(false), m_bLevelUp(false), m_bBattleEnd(false)
{

} 

ENGINE::CResultBoard::~CResultBoard(void)
{
	wstring wstrTemp = ENGINE::GetManagement()->GetBgmKey();
	ENGINE::GetManagement()->SetBgm(wstrTemp.c_str());
}

ENGINE::CResultBoard* ENGINE::CResultBoard::Create(eObjectType _eObjectType, int _iExp, CCharacterGroup* _pCharGroup)
{

	CResultBoard* pResultBoard = new CResultBoard(_eObjectType);

	if(FAILED(pResultBoard->Initialize()))
	{
		SAFE_DELETE(pResultBoard);
	}
	else
	{
		pResultBoard->SetCharacterAndExp(_pCharGroup, _iExp);
	}

	return pResultBoard;
}

HRESULT ENGINE::CResultBoard::Initialize(void)
{
	m_bLevelUp = false;
	m_bBattleEnd = false;
	m_bCreate = true;
	ENGINE::GetSoundManager()->PlayBGM(L"BGMBattleEnd.mp3");

	return S_OK;
}

int ENGINE::CResultBoard::Update(void)
{		
	vector<CCharacter*>::iterator iter =  m_pCharGroup->GetCharacterGroup()->begin();
	vector<CCharacter*>::iterator iter_end = m_pCharGroup->GetCharacterGroup()->end();
	if(m_bCreate)
	{
		if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_LBUTTON))
		{
			m_bExit = true; //이게 켜지면 룰렛을 돌릴수 있도록..
			m_bCreate = false;
		}
	}

	int iDevideExp = m_iExp / 4;

	if(m_bBattleEnd == false)
	{
		for(iter; iter != iter_end; ++iter)
		{
			if((*iter)->BattleResult(iDevideExp) == true)
				m_bLevelUp = true;
		}
		m_bBattleEnd = true;
	}
		

	if(m_bExit)
	{
		if(ResultBoard() == 1) //룰렛이 다 돌았다면
		{
			if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_LBUTTON))
			{
				m_bExit = false;

				return 1;
			}
		}
	}

	return 0;
}

void ENGINE::CResultBoard::SetCharacterAndExp(CCharacterGroup* _pGroup, int _iExp)
{
	m_pCharGroup = _pGroup;
	m_iExp = _iExp;
}

void ENGINE::CResultBoard::Render(void)
{
	ENGINE::GetDevice()->EndScene();
	ENGINE::GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleResult", 408, 114, 0, NULL);

	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleEndWindow", 252, 286, 0, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleEndWindow", 557, 286, 0, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleEndWindow", 252, 451, 0, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleEndWindow", 557, 451, 0, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleShadow", 140, 320, 0, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleShadow", 443, 320, 0, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleShadow", 140, 486, 0, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleShadow", 443, 486, 0, NULL);

	vector<CCharacter*>::iterator iter =  m_pCharGroup->GetCharacterGroup()->begin();
	vector<CCharacter*>::iterator iter_end = m_pCharGroup->GetCharacterGroup()->end();

	int iDevideExp = m_iExp / 4;
	
	for(size_t i = 0; i < 2; ++i)
	{
		for(size_t j = 0; j < 2; ++j)
		{
			eCharacterID eCharID = (*iter)->GetCharacterID();
			CHARACTER_STATE* pCharState  = (*iter)->GetCharacterState();
			if(m_bLevelUp)
				DrawSprite(RESOURCE_TYPE_STATIC, L"BattleLevelUp", 198 + float(j * 304),  272 + float(i * 165), 0, NULL);
			DrawSprite(RESOURCE_TYPE_STATIC, L"ExpGet", 198 + float(j * 304), 272 + float(i * 165), 0, NULL);
			DrawFont_Int(iDevideExp, 300 + float(j * 304), 288 + float(i * 165), 24, 0);
			DrawSprite(RESOURCE_TYPE_STATIC, L"TotalExp", 198 + float(j * 304), 303 + float(i * 165), 0, NULL);
			DrawFont_Int((*iter)->GetCharacterState()->iExp, 300 + float(j * 304), 319 + float(i * 165), 24, 0);
			DrawSprite(RESOURCE_TYPE_STATIC, L"NextExp", 198 + float(j * 304), 336 + float(i * 165), 0, NULL);
			DrawFont_Int((*iter)->GetCharacterState()->iNextExp, 300 + float(j * 304), 353 + float(i * 165), 24, 0);
			DrawSprite(RESOURCE_TYPE_STATIC, L"BattleCharacter", 140 + float(j * 304), 260 + float(i * 165), eCharID, NULL);
			++iter;
		}
	}

	//TEXINFO* pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"BattleEndWindow", 0);

	ENGINE::GetSprite()->End();
	ENGINE::GetDevice()->BeginScene();
}

int ENGINE::CResultBoard::ResultBoard(void)
{
	//기타 연산..

	return 1;
}

void ENGINE::CResultBoard::DrawSprite(eResourceType _eResourceType, const TCHAR* _ResourceKey, float _fX, float _fY, const int _iCnt, const RECT* _rcRect)
{
	TEXINFO* pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(_eResourceType, _ResourceKey, _iCnt);

	D3DXVECTOR3 vCenter(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f);

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, _fX, _fY, 0.f);

	ENGINE::GetSprite()->SetTransform(&matTrans);

	ENGINE::GetSprite()->Draw(pTexInfo->pTexture, _rcRect, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void ENGINE::CResultBoard::DrawFont_Int(int _iText, float _fX, float _fY, float _fIntervalX, float _fIntervalY)
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
		
		//if(_bIsMaxFont == false)
		pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"BattleEndFont", iChar);

		/*if(_bIsMaxFont == true)
			pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"MaxFont", iChar);*/

		fCenterX = (float)pTexInfo->ImgInfo.Width;
		fCenterY = (float)pTexInfo->ImgInfo.Height;

		vCenter.x = 0.f;
		vCenter.y = fCenterY;

		D3DXMatrixTranslation(&matTrans, _fX + (i * _fIntervalX), _fY + (i * _fIntervalY), 0.f);

		ENGINE::GetSprite()->SetTransform(&matTrans);

		ENGINE::GetSprite()->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}