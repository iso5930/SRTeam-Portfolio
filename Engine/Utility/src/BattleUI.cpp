#include "BattleUI.h"
#include "Export_Function.h"
#include "GroupObserver.h"
#include "Character.h"
#include "CharacterGroup.h"
#include "MonsterGroup.h"
#include "Monster.h"
#include "MouseCollision.h"
#include "..\Resources\src\RectangleColor.h"
#include "Ability.h"
#include "AbilityGroup.h"

ENGINE::CBattleUI::CBattleUI(eObjectType _eObjectType)
:CGameObject(_eObjectType), m_pCharacterGroupObserver(NULL), m_pCheck(NULL), m_pRcCol(NULL), m_pMonster(NULL), m_iAbilityIndex(-1)
{
	
}

ENGINE::CBattleUI::~CBattleUI(void)
{
	Release();
}

ENGINE::CBattleUI* ENGINE::CBattleUI::Create(eObjectType _eObjectType)
{
	CBattleUI* pBattleUI = new CBattleUI(_eObjectType);

	if(FAILED(pBattleUI->Initialize()))
	{
		SAFE_DELETE(pBattleUI);
	}

	return pBattleUI;
}

HRESULT ENGINE::CBattleUI::Initialize(void)
{
	m_eBattleMessage = BATTLE_MESSAGE_END;

	m_pCharacterGroupObserver = ENGINE::CGroupObserver::Create(this);
	ENGINE::GetInfoSubject()->Subscribe(m_pCharacterGroupObserver);

	//여기서 충돌 박스를 만들어주자..

	for(int i = 0; i < 5; ++i)
	{
		float fY = 244.f + (i * 20);

		RECT rcRect;

		rcRect.left = 300;
		rcRect.right = 400;

		rcRect.top = long(fY - 20.f);
		rcRect.bottom = (long)fY;

		m_vecCollision.push_back(rcRect);
	}

	m_bFirstClick = false;

	m_bMessageEnd = false;

	m_bMessageBoxClose = false;

	m_pMouseCollision = ENGINE::CMouseCollision::Create(this);
	m_ComponentMap.insert(COMPONENT_MAP::value_type(L"MouseCollision", m_pMouseCollision));

	m_pCheck = new bool;

	(*m_pCheck) = false;

	m_pRcCol = ENGINE::CRectangleColor::Create();
		
	return S_OK;
}

int ENGINE::CBattleUI::Update(void)
{	
	//턴타임 & 캐릭터 정보 & 몬스터 정보 실시간 갱신...

	CGameObject::Update();
	
	return 0;
}

void ENGINE::CBattleUI::Render(void)
{
	//그래픽 디바이스 껏다가 다시 키기

	//마우스 오버시 글씨 색깔이 바뀔수 있도록...
	//어빌리티 사용시 옆으로 충돌박스가 더 그려진다..

	//턴타임에 따른 UI 렌더

	ENGINE::GetDevice()->EndScene();
	ENGINE::GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	vector<ENGINE::CCharacter*>::iterator iter = m_pCharacterGroupObserver->GetCharacterGroup()->GetCharacterGroup()->begin();
	vector<ENGINE::CCharacter*>::iterator iter_end = m_pCharacterGroupObserver->GetCharacterGroup()->GetCharacterGroup()->end();

	int iCount = -1;

	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleTurnShape", 400, 70, 0, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleTurnShape", 245, 64, 1, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"BattleTurnShape", 555, 64, 2, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"TurnBar", 400, 60, 0, NULL);

	if(ENGINE::GetBattleManeger()->GetTurn() == true)
		DrawSprite(RESOURCE_TYPE_STATIC, L"Action", 400, 28, 0, NULL);
	
	else
		DrawSprite(RESOURCE_TYPE_STATIC, L"Ready", 400, 60, 0, NULL);

	for(iter; iter != iter_end; ++iter)
	{	
		
		eCharacterID eCharID = (*iter)->GetCharacterID();
		CHARACTER_STATE* pCharState  = (*iter)->GetCharacterState();

		if(pCharState->iHitPoint <= 0)
			continue;
		
		++iCount;
		
		float fBPPercentage = ((float)pCharState->iBarrierPoint / (float)pCharState->iMaxBarrierPoint) * 106;
		float fHPPercentage = ((float)pCharState->iHitPoint / (float)pCharState->iMaxHitPoint) * 106;
		float fAbilPercentage1 = ((float)pCharState->iAbility1 / (float)pCharState->iMaxAbility1) * 28;
		float fAbilPercentage2 = ((float)pCharState->iAbility2 / (float)pCharState->iMaxAbility2) * 28;
		float fAbilPercentage3 = ((float)pCharState->iAbility3 / (float)pCharState->iMaxAbility3) * 28;

		RECT BPrc = {0, 0, (long)fBPPercentage, 2};
		RECT HPrc = {0, 0, (long)fHPPercentage, 2};
		RECT AbilRc1 = {0, 0, (long)fAbilPercentage1, 22};
		RECT AbilRc2 = {0 ,0, (long)fAbilPercentage2, 22};
		RECT AbilRc3 = {0, 0, (long)fAbilPercentage3, 22};

		DrawSprite(RESOURCE_TYPE_STATIC, L"BattleCharacterFace", 139 + float(iCount * 155), 517, eCharID, NULL);
		DrawSprite(RESOURCE_TYPE_STATIC, L"BattleFaceShape", 140 + float(iCount * 155), 518, 0, NULL);
		DrawSprite(RESOURCE_TYPE_STATIC, L"BP", 166 + float(iCount * 155), 552, 0, NULL);
		DrawSprite(RESOURCE_TYPE_STATIC, L"Bar", 166 + float(iCount * 155), 551, 0, NULL);
		DrawSprite(RESOURCE_TYPE_STATIC, L"Bar", 166 + float(iCount * 155), 551, 1, &BPrc);
		DrawSprite(RESOURCE_TYPE_STATIC, L"HP", 166 + float(iCount * 155), 577, 0, NULL);
		DrawSprite(RESOURCE_TYPE_STATIC, L"Bar", 166 + float(iCount * 155), 576, 0, NULL);
		DrawSprite(RESOURCE_TYPE_STATIC, L"Bar", 166 + float(iCount * 155), 576, 2, &HPrc);
		DrawSprite(RESOURCE_TYPE_STATIC, L"SPShape", 210 + float(iCount * 155), 500, 0, NULL);
		DrawSprite(RESOURCE_TYPE_STATIC, L"SPShape", 210 + float(iCount * 155), 517, 0, NULL);
		DrawSprite(RESOURCE_TYPE_STATIC, L"SPShape", 210 + float(iCount * 155), 534, 0, NULL);
		DrawSprite(RESOURCE_TYPE_STATIC, L"SPGauge", 209 + float(iCount * 155), 499, 0, &AbilRc1);
		DrawSprite(RESOURCE_TYPE_STATIC, L"SPGauge", 209 + float(iCount * 155), 516, 1, &AbilRc2);
		DrawSprite(RESOURCE_TYPE_STATIC, L"SPGauge", 209 + float(iCount * 155), 533, 2, &AbilRc3);
		DrawFont_Int(pCharState->iBarrierPoint, 150 + float(iCount * 155), 574, 12, 0, L"NormalFont");
		DrawFont_Int(pCharState->iMaxBarrierPoint, 190 + float(iCount * 155), 574, 12, 0, L"MaxFont");
		DrawFont_Int(pCharState->iHitPoint, 150 + float(iCount * 155), 599, 12, 0, L"NormalFont");
		DrawFont_Int(pCharState->iMaxHitPoint, 190 + float(iCount * 155), 599, 12, 0, L"MaxFont");

		if(eCharID == CHARACTER_SIZZ)
		{
			DrawSprite(RESOURCE_TYPE_STATIC, L"MagicName", 190 + float(iCount * 155), 501, 0, NULL);
			DrawSprite(RESOURCE_TYPE_STATIC, L"MagicName", 186 + float(iCount * 155), 518, 1, NULL);
			DrawSprite(RESOURCE_TYPE_STATIC, L"MagicName", 186 + float(iCount * 155), 535, 2, NULL);
		}
		else
		{
			DrawSprite(RESOURCE_TYPE_STATIC, L"SkillName", 188 + float(iCount * 155), 501, 0, NULL);
			DrawSprite(RESOURCE_TYPE_STATIC, L"SkillName", 186 + float(iCount * 155), 518, 1, NULL);
			DrawSprite(RESOURCE_TYPE_STATIC, L"SkillName", 186 + float(iCount * 155), 535, 2, NULL);
		}
		DrawSprite(RESOURCE_TYPE_STATIC, L"TextBP", 124 + float(iCount * 155), 557, 0, NULL);
		DrawSprite(RESOURCE_TYPE_STATIC, L"TextHP", 124 + float(iCount * 155), 582, 0, NULL);
	}

	if(m_pMonster != NULL)
	{
		int iMonsterID = m_pMonster->GetMonsterID();
		int iMonsterType = m_pMonster->GetMonsterState()->eMonType;
		int iMonsterHP = m_pMonster->GetMonsterState()->iHitPoint;
		int iMonsterMaxHP = m_pMonster->GetMonsterState()->iMaxHitPoint;
		int iMonsterBP = m_pMonster->GetMonsterState()->iBarrierPoint;
		int iMonsterMaxBP = m_pMonster->GetMonsterState()->iMaxBarrierPoint;
		int iMonsterLevel = m_pMonster->GetMonsterState()->iLevel;

		DrawSprite(RESOURCE_TYPE_STATIC, L"BattleUIMonster", 645, 60, iMonsterID, NULL);
		DrawFont("Attr", 610, 90, 8, 0);
		DrawSprite(RESOURCE_TYPE_STATIC, L"TypeName", 664, 84, iMonsterType, NULL);
		DrawFont("Level", 610, 105, 8, 0);
		DrawFont_Int(iMonsterLevel, 665, 105, 8, 0, L"Font");
		if(iMonsterBP == 0)
		{
			DrawFont("H.P.", 575, 144, 8, 0);
			DrawFont_Int(iMonsterHP, 620, 144, 12, 0, L"NormalFont");
			DrawFont_Int(iMonsterMaxHP, 668, 144, 12, 0, L"MaxFont");
		}
		else
		{
			DrawFont("B.P.", 575, 144, 8, 0);
			DrawFont("H.P.", 575, 166, 8, 0);
			DrawFont_Int(iMonsterBP, 620, 144, 12, 0, L"NormalFont");
			DrawFont_Int(iMonsterMaxBP, 668, 144, 12, 0, L"MaxFont");
			DrawFont_Int(iMonsterHP, 620, 166, 12, 0, L"NormalFont");
			DrawFont_Int(iMonsterMaxHP, 668, 166, 12, 0, L"MaxFont");
		}

	}

	ENGINE::GetSprite()->End();
	ENGINE::GetDevice()->BeginScene();

	ENGINE::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	ENGINE::GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);

	ENGINE::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	ENGINE::GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	ENGINE::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	ENGINE::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	ENGINE::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	ENGINE::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	ENGINE::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if(m_pRcCol != NULL)
		m_pRcCol->Render();

	ENGINE::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	ENGINE::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void ENGINE::CBattleUI::Release(void)
{
	if(m_pRcCol != NULL)
	{
		m_pRcCol = NULL;
		delete m_pRcCol;
	}
}

eBattleMessage ENGINE::CBattleUI::GetBattleMessage(void)
{
	return m_eBattleMessage;
}

int ENGINE::CBattleUI::MessageBoxUpdate(void)
{
	//메세지 박스 업데이트..
	//여기서 메세지 충돌 검사를 한후 충돌검사가 true일 경우 
	//그 상태에 따라 메세지의 값을 바꾸어 주고 return 1 을 해준다.

	POINT ptMouse;
	ENGINE::GetInputManager()->GetMousePos(&ptMouse); //마우스 값 받아오기..

	//마우스 오버시에 바꾸어 주고..
	//마우스 클릭시에 바꾸어 주고..

	//이게 1번째 클릭인지 

	//2번째 클릭인지..

	//반환 값이 1일때는 완전히 선택이 완료됬을때...

	//그렇다면 1번째 클릭후 돌아 갈수가 있나?

	//if문으로 bool타입 변수를 하나 준다음에 1번째 클릭에서는 메세지의 저장만 다음에는 스위치문으로 분기를 나누자...

	for(size_t i = 0; i < m_vecCollision.size(); ++i)
	{
		if(PtInRect(&m_vecCollision[i], ptMouse))
		{
			//아직 클릭아님..
			//글씨 색깔만 바꾸어 주자면...
			m_iMouseOver = i; //이게 렌더할때 사용될거임...

			if(m_bFirstClick == false)
			{
				if(ENGINE::GetInputManager()->IsKeyUpNow(KEY_STATE_LBUTTON))
				{
					m_eBattleMessage = (eBattleMessage)i;
					m_bFirstClick = true;
					m_bMessageEnd = false;
				}
			}
		}
	}

	if(m_bFirstClick)
	{
		ENGINE::CComponent* pComponent = NULL;

		switch(m_eBattleMessage)
		{
		case BATTLE_MESSAGE_ATTACK:
			MonsterTargeting();
			m_bMessageBoxClose = true;
			break;

		case BATTLE_MESSAGE_DEFENSE:
			m_bMessageEnd = true;
			break;

		case BATTLE_MESSAGE_ABILITY:
			if(m_bMessageBoxClose)
			{
				MonsterTargeting();
			}
			break;

	/*	case BATTLE_MESSAGE_ITEM:
			m_bFirstClick = false;
			break;

		case BATTLE_MESSAGE_EQUIP:
			m_bFirstClick = false;
			break;

		case BATTLE_MESSAGE_AUTO_ATTACK:
			m_bFirstClick = false;
			break;*/

		case BATTLE_MESSAGE_MOVE:
			//타겟 선택
			MoveTargeting();
			m_bMessageBoxClose = true;
			break;

		case BATTLE_MESSAGE_ESCAPE:
			m_bMessageEnd = true;
			break;
		}
	}
	if(m_bMessageEnd)
	{
		m_bMessageEnd = false;
		m_bMessageBoxClose = false;
		return 1;
	}

	return 0;
}

void ENGINE::CBattleUI::MessageRender(void)
{
	ENGINE::GetDevice()->EndScene();
	ENGINE::GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	if(m_bMessageBoxClose == false)
	{
		DrawSprite(RESOURCE_TYPE_STATIC, L"BattleWindow", 360.f, 296.f, 0, NULL);
		//메세지 박스 띄우고

		for(size_t i = 0; i < m_vecCollision.size(); ++i)
		{
			D3DCOLOR D3dColor;

			if(m_iMouseOver == i)
			{	
				D3dColor = D3DCOLOR_ARGB(255, 255, 0, 0);
			}
			else
			{
				D3dColor = D3DCOLOR_ARGB(255, 0, 0, 0);
			}	

			float fY = 224.f + (i * 20);

			switch(i)
			{
			case 0:
				DrawText(L"공격(A)", D3dColor, 300, fY);
				break;

			case 1:
				DrawText(L"방어(D)", D3dColor, 300, fY);
				break;

			case 2:
				DrawText(L"스킬(T)", D3dColor, 300, fY);
				//캐릭터의 속성에 따라서 바뀔수 있다...
				break;

			//case 3:
			//	//DrawText(L"아이템(I)", D3dColor, 300, fY); //이것도 빼자,.
			//	break;

			//case 4:
			//	//DrawText(L"장비(E)", D3dColor, 300, fY); //이것도 빼고
			//	break;

			//case 5:
			//	//DrawText(L"자동전투(U)", D3dColor, 300, fY); //이거 빼고
			//	break;

			case 3:
				DrawText(L"이동(M)", D3dColor, 300, fY);
				break;

			case 4:
				DrawText(L"도주(F)", D3dColor, 300, fY);
				break;
			}

			//못쓰는거 빼자....

			if(m_eBattleMessage == BATTLE_MESSAGE_ABILITY)
			{
				POINT ptMouse;
				ENGINE::GetInputManager()->GetMousePos(&ptMouse);
				D3DCOLOR D3dColor;

				//스킬 탭을 사용했다는 뜻..
				DrawSprite(RESOURCE_TYPE_STATIC, L"BattleWindow", 534.f, 340.f, 1, NULL);
				vector<RECT> vecCollision;

				int iCur = ENGINE::GetBattleManeger()->GetTurnIndex();
				//지금 누구의 턴인지..

				vector<ENGINE::CCharacter*>* vecChar = m_pCharacterGroupObserver->GetCharacterGroup()->GetCharacterGroup();

				vector<ENGINE::CAbility*>* vecAbility = ((*vecChar)[iCur])->GetAbilityGroup()->GetAbility();

				for(size_t i = 0; i < vecAbility->size(); ++i)
				{
					float fY = 284.f + (i * 20);

					RECT rcRect;

					rcRect.left = 440;
					rcRect.right = 620;

					rcRect.top = long(fY - 20.f);
					rcRect.bottom = (long)fY;

					vecCollision.push_back(rcRect);
				}

				for(size_t i = 0; i < vecCollision.size(); ++i)
				{
					if(PtInRect(&vecCollision[i], ptMouse))
					{
						if(ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
						{
							//m_bMessageEnd = true;
							m_bMessageBoxClose = true;
						}
						m_iAbilityIndex = i;
					}

					if(m_iAbilityIndex == i)
					{
						D3dColor = D3DCOLOR_ARGB(255, 255, 0, 0);
					}
					else
					{
						D3dColor = D3DCOLOR_ARGB(255, 0, 0, 0);
					}

					wstring wstrName = (*vecAbility)[i]->GetAbilityName();

					TCHAR szName[100] = L"";

					lstrcpy(szName, wstrName.c_str());

					float fY = 263 + ((float)i * 20);

					DrawText(szName, D3dColor, 450.f, fY);
				}

				//for(size_t i = 0; i < vecAbility->size(); ++i)
				//{
				//	wstring wstrName = (*vecAbility)[i]->GetAbilityName();

				//	TCHAR szName[100] = L"";

				//	lstrcpy(szName, wstrName.c_str());

				//	float fY = 263 + ((float)i * 20);

				//	DrawText(szName, D3dColor, 450.f, fY);
				//}
			}
		}

		
	}

	ENGINE::GetSprite()->End();
	ENGINE::GetDevice()->BeginScene();
}

void ENGINE::CBattleUI::DrawSprite(eResourceType _eResourceType, const TCHAR* _ResourceKey, float _fX, float _fY, const int _iCnt, const RECT* _rcRect)
{
	TEXINFO* pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(_eResourceType, _ResourceKey, _iCnt);

	D3DXVECTOR3 vCenter(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f);

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, _fX, _fY, 0.f);

	ENGINE::GetSprite()->SetTransform(&matTrans);

	ENGINE::GetSprite()->Draw(pTexInfo->pTexture, _rcRect, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void ENGINE::CBattleUI::DrawText(TCHAR* _pText, D3DCOLOR _Color, float _fX, float _fY)
{
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, _fX, _fY, 0.f);

	ENGINE::GetSprite()->SetTransform(&matTrans);

	ENGINE::GetFont()->DrawTextW(ENGINE::GetSprite(), _pText, lstrlen(_pText), NULL, NULL, _Color);
}

void ENGINE::CBattleUI::SetFirstClick(bool _Check)
{
	m_bFirstClick = _Check;
}

D3DXVECTOR3* ENGINE::CBattleUI::GetTargetPos(void)
{
	return &m_vTargetPos;
}

D3DXVECTOR3* ENGINE::CBattleUI::GetMovePos(void)
{
	return &m_vMovePos;
}

void ENGINE::CBattleUI::MonsterTargeting(void)
{

	if(m_eBattleMessage == BATTLE_MESSAGE_ABILITY)
	{
		int iCur = ENGINE::GetBattleManeger()->GetTurnIndex();

		vector<CCharacter*>* vecChar = m_pCharacterGroupObserver->GetCharacterGroup()->GetCharacterGroup();

		if(((*vecChar)[iCur])->GetCharacterID() == CHARACTER_SIZZ)
		{
			//스킬의 사용자가 시즈일경우.. 
			//논타겟팅 스킬일경우 바로 나갈수있게 해준다...
			if(m_iAbilityIndex != 0)
			{
				m_bMessageEnd = true;

				return;
			}
			else
			{
				vector<ENGINE::CMonster*>::iterator iter = m_pMonsterGroup->GetMonsterGroup()->begin();
				vector<ENGINE::CMonster*>::iterator iter_end = m_pMonsterGroup->GetMonsterGroup()->end();

				for(iter; iter != iter_end; ++iter)
				{
					if((*iter)->MonsterPickCheck(m_pCheck) == true) 
					{
						m_pMonster = *iter;

						if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_LBUTTON))
						{
							m_bMessageEnd = true;
							m_vTargetPos = (*iter)->GetInfo()->m_vPos;
						}
						break;
					}
					(*m_pCheck) = false;
				}
			}
		}
	}

	vector<ENGINE::CMonster*>::iterator iter = m_pMonsterGroup->GetMonsterGroup()->begin();
	vector<ENGINE::CMonster*>::iterator iter_end = m_pMonsterGroup->GetMonsterGroup()->end();
	
	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->MonsterPickCheck(m_pCheck) == true) 
		{
			m_pMonster = *iter;

			if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_LBUTTON))
			{
				m_bMessageEnd = true;
				m_vTargetPos = (*iter)->GetInfo()->m_vPos;
			}
			break;
		}
		(*m_pCheck) = false;
	}
}

void ENGINE::CBattleUI::MoveTargeting(void)
{
	D3DXVECTOR3 pPos;

	m_pMouseCollision->PickTerrain(&pPos);

	if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_LBUTTON))
	{
		m_vMovePos = pPos;
		m_bMessageEnd = true;
		m_pRcCol = NULL;
	}
	else
	{
		////타일오버레이 렌더? 어떻게 하냐....
		VERTEX_COLOR*	pVertexColor = new VERTEX_COLOR[4];

		pVertexColor = m_pMouseCollision->PickTileIndex();
		
		pVertexColor[0].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);
		pVertexColor[1].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);
		pVertexColor[2].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);
		pVertexColor[3].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

		m_pRcCol = ENGINE::CRectangleColor::Create();

		m_pRcCol->WriteVerticies(pVertexColor);
	}
}

void ENGINE::CBattleUI::SetMonsterGroup(CMonsterGroup* _pMonsterGroup)
{
	m_pMonsterGroup = _pMonsterGroup;
}

void ENGINE::CBattleUI::RageGaugeRender(int iCharCur)
{
	if(iCharCur == -1)
		return;

	ENGINE::GetDevice()->EndScene();
	ENGINE::GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	vector<ENGINE::CCharacter*>* pvecChar = m_pCharacterGroupObserver->GetCharacterGroup()->GetCharacterGroup();
	
	eCharacterID eCharID = ((*pvecChar)[iCharCur])->GetCharacterID();
	int iRageGauge		= ((*pvecChar)[iCharCur])->GetCharacterState()->iRageGauge;
	int iMaxRageGauge	= ((*pvecChar)[iCharCur])->GetCharacterState()->iMaxRageGauge;
	
	float fPercentage = (float(iRageGauge) / float(iMaxRageGauge)) * 63;

	RECT rc = { 0, 0, (long)fPercentage, 5};
	
	DrawSprite(RESOURCE_TYPE_STATIC, L"RageCharacter", 150, 25, eCharID, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"RageGauge", 150, 93, 0, NULL);
	DrawSprite(RESOURCE_TYPE_STATIC, L"RageGaugeBar", 150, 93, 0, &rc);

	if(iRageGauge < 60)
		DrawSprite(RESOURCE_TYPE_STATIC, L"RageText", 116, 92, 0, NULL);
	else
		DrawSprite(RESOURCE_TYPE_STATIC, L"RageText", 116, 92, 1, NULL);

	ENGINE::GetSprite()->End();
	ENGINE::GetDevice()->BeginScene();
	
}

void ENGINE::CBattleUI::DrawFont_Int(int _iText, float _fX, float _fY, float _fIntervalX, float _fIntervalY, wstring _wstrKey)
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
		pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, _wstrKey.c_str(), iChar);

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

void ENGINE::CBattleUI::DrawFont(char* _pName, float _fX, float _fY, float _fIntervalX, float _fIntervalY)
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

		ENGINE::GetSprite()->SetTransform(&matTrans);

		ENGINE::GetSprite()->Draw(pTexInfo->pTexture, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void ENGINE::CBattleUI::SelectAbility(void)
{
	//스킬 선택창...
	

	//시즈인지 아닌지를 판단하고 
	//지금 턴인녀석의 아이디를 알아야한다...
	//일단 콜리전을 그려야 하니깐...
	//m_bMessageEnd = true;
}

int ENGINE::CBattleUI::GetAbilityIndex(void)
{
	return m_iAbilityIndex;
}

void ENGINE::CBattleUI::SetBattleMessage(eBattleMessage _Message)
{
	m_eBattleMessage = _Message;
}

ENGINE::CMonster* ENGINE::CBattleUI::GetMonsterTarget(void)
{
	return m_pMonster;
}