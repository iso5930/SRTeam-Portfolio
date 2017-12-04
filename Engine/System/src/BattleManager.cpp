#include "BattleManager.h"
#include "CharacterGroup.h"
#include "MonsterGroup.h"
#include "BattleUI.h"
#include "Character.h"
#include "Monster.h"
#include "Export_Function.h"
#include "Transform.h"
#include "ResultBoard.h"

IMPLEMENT_SINGLETON(ENGINE::CBattleManager)

ENGINE::CBattleManager::CBattleManager(void)
:m_bBattleStart(false), m_pBattleUI(NULL), m_pCharacterGroup(NULL), m_pMonsterGroup(NULL), m_iGetExp(0)
{
	
}

ENGINE::CBattleManager::~CBattleManager(void)
{
	
}

void ENGINE::CBattleManager::CreateBattle(CCharacterGroup* _pCharacterGroup, CMonsterGroup* _pMonsterGroup)
{
	m_vecCharacterTime.clear();
	m_vecMonsterTime.clear();

	ENGINE::GetSoundManager()->PlayBGM(L"BGMBattle.mp3");

	m_iGetExp = 0;

	m_bBattleStart = true;

	m_pCharacterGroup = _pCharacterGroup;
	m_pMonsterGroup = _pMonsterGroup;

	for(size_t i = 0; i < m_pCharacterGroup->GetCharacterGroup()->size(); ++i)
	{
		m_vecCharacterTime.push_back(0.f); //턴 타임 값.
	}

	for(size_t i = 0; i < m_pMonsterGroup->GetMonsterGroup()->size(); ++i)
	{
		m_vecMonsterTime.push_back(0.f);
	}

	m_pMonsterGroup->BattleInit();

	m_pBattleUI = ENGINE::CBattleUI::Create(OBJECT_TYPE_DYNAMIC);
	m_pBattleUI->SetMonsterGroup(_pMonsterGroup);

	m_bTurn = false;
	m_iTurnIndex = -1;
	m_bBattleEnd = false;

	//배틀 이벤트를 넣어주어야 한다...
}

int ENGINE::CBattleManager::Update(void)
{
	float fTime = 0.f;

	vector<ENGINE::CCharacter*>* vecChar = m_pCharacterGroup->GetCharacterGroup();
	vector<ENGINE::CMonster*>* vecMonster = m_pMonsterGroup->GetMonsterGroup();

	if(vecMonster->size() == 0)
	{
		m_bBattleStart = false;
		((*vecChar)[0])->SetCamera();
		m_bBattleEnd = true;
		EndBattle();
		return 0;
	}

	if(m_bTurn == false)//아직 턴이 진행되지 않았을때만 작동할수 있도록...
	{
		for(size_t i = 0; i < m_vecCharacterTime.size(); ++i)
		{
			if((*vecChar)[i]->GetBattleMessage() != BATTLE_MESSAGE_END)//엔드가 아닐시에 다른 메세지를 처리하고 있는 중이니 턴 타임감소 x
			{
				continue;
			}

			if((*vecChar)[i]->GetCharacterState()->iHitPoint == 0)
			{
				continue;
			}

			int iSpeed = (*vecChar)[i]->GetCharacterState()->iSPD / 2;

			fTime = iSpeed * ENGINE::GetTimeDelta();

			m_vecCharacterTime[i] += fTime;

			if(m_vecCharacterTime[i] > 50.f)
			{
				//여기서 turn이 발생했다고 스위치를 올려준다.
				m_bTurn = true;
				//그와 동시에 몇번째 캐릭터의 턴인지 저장을 해주자.
				m_iTurnIndex = i;

				m_pBattleUI->SetFirstClick(false);

				((*vecChar)[i])->SetCamera();
				break;
			}
		}

		for(size_t i = 0; i < m_vecMonsterTime.size(); ++i)
		{
			if(((*vecMonster)[i])->GetMonsterDeath() == true)
			{
				m_iGetExp += (*vecMonster)[i]->GetMonsterState()->iEXP;
				m_pMonsterGroup->DeleteMonster(i); //죽은 몬스터는 제거 해준다..

				vector<float>::iterator iter = m_vecMonsterTime.begin();

				for(size_t j = 0; j < i; ++j)
				{
					++iter;
				}

				iter = m_vecMonsterTime.erase(iter);
			}//몬스터가 죽었다면 해당하는 턴타임을 제거해준다..
			else if(((*vecMonster)[i])->GetState() == MONSTER_STAND)//몬스터가 스탠드 상태일때
			{
				int iSpeed = (*vecMonster)[i]->GetMonsterState()->iSPD / 2;

				fTime = iSpeed * ENGINE::GetTimeDelta();

				m_vecMonsterTime[i] += fTime;

				if(m_vecMonsterTime[i] > 50.f)
				{
					m_vecMonsterTime[i] = 0.f;

					float	fLenght = 99999.f;
					int		iTargetIndex = 0;

					D3DXVECTOR3 vMonsterPos = (*vecMonster)[i]->GetInfo()->m_vPos;
					
					for(size_t j = 0; j < vecChar->size(); ++j)
					{
						//플레이어와 몬스터와의 길이를 비교한다음 메세지를 던져주자..

						if(((*vecChar)[j])->GetCharacterState()->iHitPoint == 0)
						{
							continue; //죽은 플레이어는 스킵.
						}
						D3DXVECTOR3 vDist = (*vecChar)[j]->GetInfo()->m_vPos - vMonsterPos;

						float fSource = D3DXVec3Length(&vDist);

						if(fSource <= fLenght)
						{
							fLenght = fSource;
							iTargetIndex = j;
						}
					}
					(*vecMonster)[i]->SetState(MONSTER_ATT);
					(*vecMonster)[i]->SetTarget(((*vecChar)[iTargetIndex]));
					(*vecMonster)[i]->SetTargetPos(&((*vecChar)[iTargetIndex]->GetInfo()->m_vPos));

					break;
				}
			}
		}
	}
	else //턴이 작동을 했다면...
	{
		//배틀UI MenuMessageBoxUpdate 이런식으로 바꾸기
		if(m_pBattleUI->MessageBoxUpdate() == 1)//메세지 박스를 띄우도록....
		{
			//리턴 값이 1일 경우 메세지를 선택했다는 뜻...
			m_bTurn = false; //그러므로 해당하는 캐릭터의 턴이 끝났다고 알려준다...
			eBattleMessage eMessage = m_pBattleUI->GetBattleMessage(); //메세지하고 //pos 값을 받아와야 한다.
			m_pBattleUI->SetBattleMessage(BATTLE_MESSAGE_END);

			if(eMessage == BATTLE_MESSAGE_ESCAPE)
			{
				wstring wstrTemp = ENGINE::GetManagement()->GetBgmKey();
				ENGINE::GetManagement()->SetBgm(wstrTemp.c_str());
				m_bBattleStart = false;
				((*vecChar)[0])->SetCamera();
				EndBattle();
				return 0;
			}

			(*vecChar)[m_iTurnIndex]->SetBattleMessage(eMessage);

			switch(eMessage)
			{
			case BATTLE_MESSAGE_ATTACK:
				(*vecChar)[m_iTurnIndex]->SetMonsterTarget(m_pBattleUI->GetMonsterTarget());
				(*vecChar)[m_iTurnIndex]->SetDestPos(m_pBattleUI->GetTargetPos());
				break;

			case BATTLE_MESSAGE_MOVE:
				(*vecChar)[m_iTurnIndex]->SetDestPos(m_pBattleUI->GetMovePos());
				break;

			case BATTLE_MESSAGE_ABILITY:
				(*vecChar)[m_iTurnIndex]->SetMonsterTarget(m_pBattleUI->GetMonsterTarget());
				(*vecChar)[m_iTurnIndex]->SetAbilityCur(m_pBattleUI->GetAbilityIndex());
				(*vecChar)[m_iTurnIndex]->SetDestPos(m_pBattleUI->GetTargetPos());
				break;
			}

			if(eMessage == BATTLE_MESSAGE_DEFENSE)
			{
				m_vecCharacterTime[m_iTurnIndex] = 25.f;
			}
			else
				m_vecCharacterTime[m_iTurnIndex] = 0.f;

		}
	}

	m_pBattleUI->Update(); //기본적인 업데이트 턴타임관리...

	//그리고 평상시에도 캐릭터의 스프라이트는 움직여야 하므로..

	m_pCharacterGroup->BattleUpdate();
	m_pMonsterGroup->Update(); //이런식으로 평상시에 움직일수 있도록...
	
	return 0;
}

void ENGINE::CBattleManager::Render(void)
{
	//배틀 UI 는 처음부터 있어야 하고 
	//턴이 되었을때만 보이는녀석이 따로 있어야 한다...
	if(m_pBattleUI == NULL)
	{
		return;
	}

	m_pBattleUI->Render(); //턴 타임이나 캐릭터 스테이터스..

	m_pBattleUI->RageGaugeRender(m_iTurnIndex);

	TurnSpeedRender();

	if(m_bTurn)
	{
		//그냥 렌더가 아니라 메세지 박스 렌더같은녀석...
		m_pBattleUI->MessageRender();
	}

	vector<ENGINE::CMonster*>* vecMonster = m_pMonsterGroup->GetMonsterGroup();
	//vector<ENGINE::CCharacter*>* vecChar = m_pCharacterGroup->GetCharacterGroup();

	//system("cls");

	//for(size_t i = 0; i < vecChae->size(); ++i)
	//{
	//	//cout << i << "번째 타임 : " << m_vecMonsterTime[i] << endl;
	//	cout << i << "번째 HP : " << (*vecChae)[i]->GetCharacterState()->iHitPoint << endl;
	//}

	/*for(size_t i = 0; i < m_vecMonsterTime.size(); ++i)
	{
		cout << i << "번째 타임 : " << m_vecMonsterTime[i] << endl;
		cout << i << "번째 HP : " << (*vecMonster)[i]->GetMonsterState()->iHitPoint << endl;
	}*/
}

void ENGINE::CBattleManager::EndBattle(void)
{
	vector<ENGINE::CCharacter*>* vecChar = m_pCharacterGroup->GetCharacterGroup();

	for(size_t i = 0; i < vecChar->size(); ++i)
	{
		(*vecChar)[i]->SetBattleMessage(BATTLE_MESSAGE_END);

		if(((*vecChar)[i])->GetCharacterState()->iHitPoint == 0)
		{	
			((*vecChar)[i])->GetCharacterState()->iHitPoint = (((*vecChar)[i])->GetCharacterState()->iMaxHitPoint / 2);
		}
	}

	SAFE_DELETE(m_pBattleUI);
	m_bBattleStart = false;
	m_pCharacterGroup->GroupSort();
	//m_pCharacterGroup->Update();
	m_vecCharacterTime.clear();
	m_vecMonsterTime.clear();
	m_pMonsterGroup->SetMonsterDeath();

	if(m_bBattleEnd)
	{
		//ResultBoard 생성
		ENGINE::CGameObject* pObj = ENGINE::CResultBoard::Create(OBJECT_TYPE_DYNAMIC, m_iGetExp, m_pCharacterGroup);
		ENGINE::GetManagement()->AddGameObject(L"ResultBoard", 2, pObj);
	}
	m_pCharacterGroup = NULL;
}

void ENGINE::CBattleManager::Release(void)
{
	
}

bool ENGINE::CBattleManager::GetBattleStart(void)
{
	return m_bBattleStart;
}

bool ENGINE::CBattleManager::GetTurn(void)
{
	return m_bTurn;
}

void ENGINE::CBattleManager::TurnSpeedRender(void)
{
	ENGINE::GetDevice()->EndScene();
	ENGINE::GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	vector<ENGINE::CCharacter*>* vecChar = m_pCharacterGroup->GetCharacterGroup();

	for(size_t i = 0; i < m_vecCharacterTime.size(); ++i)
	{
		if((*vecChar)[i]->GetCharacterState()->iHitPoint < 1)
			continue;

		eCharacterID eCharID	=	(*vecChar)[i]->GetCharacterID();
		int iTime = int(m_vecCharacterTime[i] * 2.08);
		if(iTime < 104)
		{
			DrawSprite(RESOURCE_TYPE_STATIC, L"PlayerTurnFace", 244 + (float)iTime, 42, eCharID, NULL);
			DrawSprite(RESOURCE_TYPE_STATIC, L"BattleCharName", 244 + (float)iTime, 64, eCharID, NULL);
		}
			
		if(iTime > 103)
		{
			DrawSprite(RESOURCE_TYPE_STATIC, L"PlayerTurnFace", 400, 42, eCharID, NULL);
			DrawSprite(RESOURCE_TYPE_STATIC, L"BattleCharName", 400, 64, eCharID, NULL);
		}
	}

	vector<ENGINE::CMonster*>* vecMonster = m_pMonsterGroup->GetMonsterGroup();
	
	for(size_t i = 0; i < m_vecMonsterTime.size(); ++i)
	{
		eMonsterID eMonID = (*vecMonster)[i]->GetMonsterID();
		int iTime = int(m_vecMonsterTime[i] * 1.5);

		DrawSprite(RESOURCE_TYPE_STATIC, L"MonsterTurnIcon", 540 - float(iTime) + (i * 4), 36, eMonID, NULL);
		
		switch(i)
		{
		case 0 :
			DrawFont("Enemy A", 512 - float(iTime) + (i * 4), 64, 8, 0);
			break;

		case 1 :
			DrawFont("Enemy B", 512 - float(iTime) + (i * 4), 64, 8, 0);
			break;

		case 2 :
			DrawFont("Enemy C", 512 - float(iTime) + (i * 4), 64, 8, 0);
			break;

		case 3 :
			DrawFont("Enemy D", 520 - float(iTime) + (i * 4), 64, 8, 0);
			break;

		case 4 :
			DrawFont("Enemy E", 520 - float(iTime) + (i * 4), 64, 8, 0);
			break;
			
		case 5 :
			DrawFont("Enemy F", 520 - float(iTime) + (i * 4), 64, 8, 0);
			break;
		}
	}
	//DrawSprite(RESOURCE_TYPE_STATIC, L"PlayerTurnFace", 244, 42, 0, NULL);

	ENGINE::GetSprite()->End();
	ENGINE::GetDevice()->BeginScene();
}

void ENGINE::CBattleManager::DrawSprite(eResourceType _eResourceType, const TCHAR* _ResourceKey, float _fX, float _fY, const int _iCnt, const RECT* _rcRect)
{
	TEXINFO* pTexInfo = ENGINE::GetResourceManager()->GetSpriteTexture(_eResourceType, _ResourceKey, _iCnt);

	D3DXVECTOR3 vCenter(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f);

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, _fX, _fY, 0.f);

	ENGINE::GetSprite()->SetTransform(&matTrans);

	ENGINE::GetSprite()->Draw(pTexInfo->pTexture, _rcRect, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

int ENGINE::CBattleManager::GetTurnIndex(void)
{	
	return m_iTurnIndex;
}

ENGINE::CMonsterGroup* ENGINE::CBattleManager::GetMonsterGroup(void)
{
	return m_pMonsterGroup;
}

void ENGINE::CBattleManager::DrawFont(char* _pName, float _fX, float _fY, float _fIntervalX, float _fIntervalY)
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