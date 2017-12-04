#include "Character.h"
#include "Equip.h"
#include "Inventory.h"
#include "AbilityGroup.h"
#include "Movement.h"
#include "Transform.h"
#include "Sprite.h"
#include "Export_System.h"
#include "MouseCollision.h"
#include "TerrainCollision.h"
#include "Export_Utility.h"
#include "Texture.h"
#include "HitBox.h"

ENGINE::CCharacter::CCharacter(eObjectType _eObjectType)
:CGameObject(_eObjectType)
,m_pInfo(NULL),
m_pVIBuffer(NULL),
m_pTexture(NULL),
m_eCharacterID(CHARACTER_END),
m_eAbilityID(ABILITYID_END),
m_eState(Character_End),
m_ePrevState(Character_End),
m_pEquip(NULL), 
m_pInventory(NULL), 
m_pAbilityGroup(NULL),
m_pMouseCollision(NULL),
m_pSpriteFrame(NULL),
m_pOBBCollision(NULL),
m_pTerrainCollision(NULL),
m_vDestPos(0.f, 0.f, 0.f),
m_fAngle(0.f),
m_iPrevIndex(0),
m_vPrevPos(0.f, 0.f, 0.f),
m_bJump(false),
m_fJumpY(0.f),
m_fTime(0.f),
m_eBattleMessage(BATTLE_MESSAGE_END),
m_bAttackMessage(false),
m_fDefTime(0.f),
m_pHitBox(NULL),
m_eUnitType(UNIT_PLAYER),
m_bSkillRun(false),
m_pTargetMonster(NULL)
{
	ZeroMemory(&m_tCharacterState, sizeof(CHARACTER_STATE));
	ZeroMemory(&m_tTempState, sizeof(CHARACTER_STATE));
}

ENGINE::CCharacter::~CCharacter(void)
{
	Release();
}

eCharacterID ENGINE::CCharacter::GetCharacterID(void)
{
	return m_eCharacterID;
}

CHARACTER_STATE* ENGINE::CCharacter::GetCharacterState(void)
{
	return &m_tCharacterState;
}

ENGINE::CEquip* ENGINE::CCharacter::GetEquip(void)
{
	return m_pEquip;
}

ENGINE::CInventory* ENGINE::CCharacter::GetInven(void)
{
	return m_pInventory;
}

ENGINE::CAbilityGroup* ENGINE::CCharacter::GetAbilityGroup(void)
{
	return m_pAbilityGroup;
}

void ENGINE::CCharacter::Release(void)
{
	SAFE_DELETE(m_pEquip);
	SAFE_DELETE(m_pAbilityGroup);
}

vector<eAbilityType>* ENGINE::CCharacter::GetAbilityType(void)
{
	return &m_vecAbilityType;
}

eAbilityID ENGINE::CCharacter::GetAbilityID(void)
{
	return m_eAbilityID;
}

ENGINE::CTransform* ENGINE::CCharacter::GetInfo(void)
{
	return m_pInfo;
}

void ENGINE::CCharacter::SetAngle(void)
{
	CComponent* pComponent = NULL;

	pComponent = ENGINE::GetManagement()->GetComponent(L"Camera", L"Transform");
	float fCameraAngle = ((CTransform*)pComponent)->m_pAngle[ANGLE_TYPE_Y];

	D3DXMATRIX matRot;
	D3DXMatrixRotationY(&matRot, fCameraAngle);

	D3DXVECTOR3 vDist = m_vDestPos - m_pInfo->m_vPos;
	vDist.y = 0;

	D3DXVec3Normalize(&vDist, &vDist);

	D3DXVECTOR3 vLook(1.f, 0.f, 0.f);

	D3DXVec3TransformNormal(&vLook, &vLook, &matRot);

	float fAngle = D3DXVec3Dot(&vDist, &vLook);

	fAngle = acosf(fAngle);

	D3DXVECTOR3 vDestPos = m_vDestPos;
	D3DXVECTOR3 vCharacter = m_pInfo->m_vPos;

	D3DXMatrixRotationY(&matRot, -fCameraAngle);

	D3DXVec3TransformCoord(&vDestPos, &vDestPos, &matRot);
	D3DXVec3TransformCoord(&vCharacter, &vCharacter, &matRot);

	if(vCharacter.z < vDestPos.z)
	{
		fAngle = 2 * D3DX_PI - fAngle;
	}

	float fSource = 0.f;
	int iIndex = 0;

	fAngle = D3DXToDegree(fAngle);

	for(int i = 1; i < 9; ++i)
	{
		fSource = 45.f * i;

		if(fSource >= fAngle)
		{
			iIndex = i;
			break;
		}
	}

	m_fAngle = fAngle + 90.f;

	if(m_eState != m_ePrevState || m_iPrevIndex != iIndex)
	{
		switch(m_eState)
		{
		case Character_Stand:
			m_pSpriteFrame->SetFrame(FRAME(float(iIndex - 1), float(iIndex - 1), 10.f));
			break;

		case Character_Run:
			m_pSpriteFrame->SetFrame(FRAME(float((iIndex - 1) * 8), float((iIndex * 8) - 1), 10.f));
			break;
		}

		m_iPrevIndex = iIndex;
	}
}

void ENGINE::CCharacter::SetDir(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &D3DXVECTOR3(0.f, 0.f, 1.f), &m_pInfo->m_matWorld);
	D3DXVec3Normalize(&m_pInfo->m_vDir, &m_pInfo->m_vDir);
}

void ENGINE::CCharacter::KeyCheck(void)
{	
	float fDeltaTime = ENGINE::GetTimeDelta();

	if(ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_LBUTTON))
	{
		m_pMovement->SetMove(true);
		m_pMouseCollision->PickTerrain(&m_vDestPos);
		m_eState = Character_Run;
	}

	if(ENGINE::GetInputManager()->IsKeyUpNow(KEY_STATE_LBUTTON))
	{
		//! 피킹..
		m_pMouseCollision->PickObject(m_pOBBCollision->GetOBBInfo(), &m_pInfo->m_matWorld, NULL);

		m_pMovement->SetMove(false);
		m_pSpriteFrame->SetFrame(FRAME(float(m_iPrevIndex - 1), float(m_iPrevIndex - 1), 10.f));
		m_eState = Character_Stand;
	}

	if(ENGINE::GetInputManager()->IsKeyDown(KEY_STATE_LCTRL))
	{
		//점프를 만들어 보자...
		m_bJump = true;
		m_fTime = 0.f;
	}
}

float ENGINE::CCharacter::GetAngle(void)
{
	return m_fAngle;
}

void ENGINE::CCharacter::SubCharacterUpdate(deque<MEMENTO>* _dequePrevMemento)
{
	if(_dequePrevMemento->size() == 0)
	{
		SetState();
		this->SetAngle();

		ENGINE::CGameObject::Update();

		D3DXMATRIX matBill;
		ENGINE::GetDevice()->GetTransform(D3DTS_VIEW, &matBill);

		ZeroMemory(matBill.m[3], sizeof(float) * 3);
		D3DXMatrixInverse(&matBill, NULL, &matBill);
		m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;

		return;
	}

	MEMENTO tMemento = _dequePrevMemento->front();

	m_iPrevFrmae = (int)m_pSpriteFrame->GetCurFrame();
	m_vPrevPos = m_pInfo->m_vPos;
	m_vDestPos = tMemento.vDestPos;

	m_pInfo->m_vPos = tMemento.vPos;
	m_eState = tMemento.eState;

	//일단 그렇다면 필요한 값이 갱신된 Frame값..

	if(_dequePrevMemento->size() > 20)
	{
		int iFrame = GetSubCharacterFrame(_dequePrevMemento);

		_dequePrevMemento->pop_front();
		//
		if(iFrame == -1)
		{
			if(m_eState == Character_Stand)
			{
				m_pSpriteFrame->SetFrame(FRAME(float(tMemento.iIndex - 1), float(tMemento.iIndex - 1), 10.f));
			}
			else
			{
				m_pSpriteFrame->SetFrame(FRAME((float)tMemento.iCurFrame, (float)tMemento.iCurFrame, 10.f));
			}
		}
		else
			m_pSpriteFrame->SetFrame(FRAME((float)iFrame, (float)iFrame, 10.f));

		if(m_eState == Character_Stand && m_pSpriteFrame->GetCurFrame() > 8)
		{
			int iA = 0;
		}
	}
	else
	{
		m_eState = Character_Stand;

		int iFrame = GetSubCharacterFrame(_dequePrevMemento);

		if(iFrame == -1)
			m_pSpriteFrame->SetFrame(FRAME(float(tMemento.iIndex - 1), float(tMemento.iIndex - 1), 10.f));
		else
			m_pSpriteFrame->SetFrame(FRAME((float)iFrame, (float)iFrame, 10.f));
	}

	this->SetState();

	ENGINE::CGameObject::Update();

	D3DXMATRIX matBill;
	ENGINE::GetDevice()->GetTransform(D3DTS_VIEW, &matBill);

	ZeroMemory(matBill.m[3], sizeof(float) * 3);
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;

	//여기서도 다음 객체를 위해서 디큐에 저장을 해놓아야 한다..

	if(m_vPrevPos != m_pInfo->m_vPos)
	{
		m_dequeMemento.push_back(MEMENTO(m_ePrevState, m_vPrevPos, m_vDestPos, m_iPrevFrmae, m_iPrevIndex));
	}
}

eCharacterState ENGINE::CCharacter::GetPrevState(void)
{
	return m_ePrevState;
}

int ENGINE::CCharacter::GetPrevFrame(void)
{
	return m_iPrevFrmae;
}

int ENGINE::CCharacter::Update(void)
{
	m_iPrevFrmae = (int)m_pSpriteFrame->GetCurFrame();
	m_vPrevPos = m_pInfo->m_vPos;

	KeyCheck();
	SetAngle();
	this->SetState();
	//SetDir();

	ENGINE::CGameObject::Update();

	if(m_bJump)
	{
		Jump();

		m_pInfo->m_vPos.y += (m_fJumpY * -1) / 150.f;

		//cout << m_pInfo->m_vPos.y << endl;

		m_pInfo->Update();
	}

	D3DXMATRIX matBill;
	ENGINE::GetDevice()->GetTransform(D3DTS_VIEW, &matBill);
	ZeroMemory(matBill.m[3], sizeof(float) * 3);
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;

	if(m_vPrevPos != m_pInfo->m_vPos)
	{
		m_dequeMemento.push_back(MEMENTO(m_ePrevState, m_vPrevPos, m_vDestPos, m_iPrevFrmae, m_iPrevIndex));
	}

	return 0;
}

void ENGINE::CCharacter::SetCntXZ(int _CntX, int _CntZ)
{
	m_iCntX = _CntX;
	m_iCntZ = _CntZ;
}

deque<MEMENTO>* ENGINE::CCharacter::GetMemento(void)
{
	return &m_dequeMemento;
}

int ENGINE::CCharacter::GetSubCharacterFrame(deque<MEMENTO>* _dequePrevMemento)
{
	CComponent* pComponent = ENGINE::GetManagement()->GetComponent(L"Camera", L"Transform");

	float fCameraAngle = ((CTransform*)pComponent)->m_pAngle[ANGLE_TYPE_Y];
	D3DXMATRIX matRotY;
	D3DXMatrixRotationY(&matRotY, fCameraAngle);

	D3DXVECTOR3 vDist = _dequePrevMemento->front().vDestPos - _dequePrevMemento->front().vPos;

	D3DXVec3Normalize(&vDist, &vDist);
	
	D3DXVECTOR3 vLook(1.f, 0.f, 0.f);

	D3DXVec3TransformNormal(&vLook, &vLook, &matRotY);

	float fAngle = D3DXVec3Dot(&vDist, &vLook);

	fAngle = acosf(fAngle);

	D3DXVECTOR3 vDestPos = _dequePrevMemento->front().vDestPos;
	D3DXVECTOR3 vPos = _dequePrevMemento->front().vPos;

	D3DXMatrixRotationY(&matRotY, -fCameraAngle);

	D3DXVec3TransformCoord(&vDestPos, &vDestPos, &matRotY);
	D3DXVec3TransformCoord(&vPos, &vPos, &matRotY);

	if(vPos.z < vDestPos.z)
	{
		fAngle = 2 * D3DX_PI - fAngle;
	}
	
	float	fSoruce = 0.f;
	int		iIndex	= 0;

	fAngle = D3DXToDegree(fAngle);

	for(int i = 1; i < 9; ++i)
	{
		fSoruce = 45.f * i;

		if(fSoruce >= fAngle)
		{
			iIndex = i;

			break;
		}
	}

	int iReturn = -1;

	if(_dequePrevMemento->front().iIndex == iIndex)
	{
		m_iPrevIndex = _dequePrevMemento->front().iIndex;
		return iReturn;
	}

	m_iPrevIndex = iIndex;

	switch(m_eState)
	{
	case Character_Stand:
		iReturn = iIndex - 1;
		break;

	case Character_Run:
		iReturn = _dequePrevMemento->front().iCurFrame % 8;
		iReturn = iReturn + ((iIndex - 1) * 8);
		break;
	}

	return iReturn;
}

void ENGINE::CCharacter::Jump(void)
{
	m_fTime += ENGINE::GetTimeDelta();

	m_fJumpY += 2.f * -1 + ((17.8f *  m_fTime * m_fTime) / 2.f);

	if(m_fJumpY > 0)
	{
		m_bJump = false;
	}
}

int ENGINE::CCharacter::BattleUpdate(void)
{
	this->SetBattleAngle();//<- 4방향 각도를 계산해서 이미지를 뿌리자...
	this->BattleState();

	if(m_eBattleMessage == BATTLE_MESSAGE_HIT)
	{
		if(m_pSpriteFrame->GetFrameEnd() == true)
		{
			m_eBattleMessage = BATTLE_MESSAGE_END;
		}

		m_pInfo->m_vPos += m_vHitDir * 0.5f * ENGINE::GetTimeDelta();
	}

	if(m_eBattleMessage == BATTLE_MESSAGE_MOVE)
	{
		if(m_pMovement->GetMove() == false)
		{
			if(m_bAttackMessage)
			{
				m_eBattleMessage = BATTLE_MESSAGE_ATTACK;
				m_bAttackMessage = false;
			}
			else if(m_bSkillRun)
			{
				switch(m_iAbilityCur)
				{
				case 0:
					m_eBattleMessage = BATTLE_MESSAGE_SKILL1;
					break;

				case 1:
					m_eBattleMessage = BATTLE_MESSAGE_SKILL2;
					break;
				}
				m_bSkillRun = false;
			}
			else
				m_eBattleMessage = BATTLE_MESSAGE_END;
		}
	}
	else if(m_eBattleMessage == BATTLE_MESSAGE_DEFENSE)
	{
		m_fDefTime += 5.f * ENGINE::GetTimeDelta();

		if(m_fDefTime >= 5.f)
		{
			m_fDefTime = 0.f;
			m_eBattleMessage = BATTLE_MESSAGE_END;
		}

	}

	if(m_eCharacterID == CHARACTER_ELLUARD && m_eBattleMessage == BATTLE_MESSAGE_SKILL2)
	{
		m_pInfo->Update();
		m_pVIBuffer->Update();
		m_pTexture->Update();
		m_pSpriteFrame->Update();
		m_pMovement->Update();
		m_pOBBCollision->Update();
	}
	else if(m_eCharacterID == CHARACTER_TENZI && m_eBattleMessage == BATTLE_MESSAGE_SKILL2)
	{
		m_pInfo->Update();
		m_pVIBuffer->Update();
		m_pTexture->Update();
		m_pSpriteFrame->Update();
		m_pMovement->Update();
		m_pOBBCollision->Update();
	}
	else
		ENGINE::CGameObject::Update();

	if(m_eBattleMessage == BATTLE_MESSAGE_ATTACK)
	{
		if(m_pSpriteFrame->GetFrameEnd())
		{
			//마지막 프레임이 돌았다면.....
			//공격모션...
			m_eBattleMessage = BATTLE_MESSAGE_END;

			ENGINE::CGameObject* pHitBox = NULL;

			int iAtk = 0;

			if(m_pTargetMonster != NULL)
			{
				iAtk = m_tCharacterState.iATK - m_pTargetMonster->GetMonsterState()->iDEF;

				if(iAtk < 1)
					iAtk = 0;
			}	

			switch(m_eCharacterID)
			{
			case CHARACTER_SIZZ:
				pHitBox = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster, 0.5f, 0.5f, 0.5f, iAtk, true, true);
				ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pHitBox);
				ENGINE::GetSoundManager()->PlayWeaponSound(L"Dagger.wav");
				break;

			case CHARACTER_MARIA:
				pHitBox = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster,0.5f, 0.5f, 0.5f, iAtk, true, true);
				ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pHitBox);
				ENGINE::GetSoundManager()->PlayWeaponSound(L"Sword.wav");
				break;

			case CHARACTER_ELLUARD:
				pHitBox = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster,0.5f, 0.5f, 0.5f, iAtk, true, true);
				ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pHitBox);
				ENGINE::GetSoundManager()->PlayWeaponSound(L"Whip.wav");
				break;

			case CHARACTER_TENZI:
				pHitBox = ENGINE::CHitBox::Create(OBJECT_TYPE_DYNAMIC, this, m_pTargetMonster,0.5f, 0.5f, 0.5f, iAtk, true, true);
				ENGINE::GetManagement()->AddGameObject(L"HitBox", 1, pHitBox);
				ENGINE::GetSoundManager()->PlayWeaponSound(L"Stick.wav");
				break;
			}
		}
	} //각자의 배틀 업데이트로 내리자...

	SetBillBoard();

	return 0;
}

eBattleMessage ENGINE::CCharacter::GetBattleMessage(void)
{
	return m_eBattleMessage;
}

void ENGINE::CCharacter::SetDestPos(D3DXVECTOR3* _pPos)
{
	if(m_eBattleMessage == BATTLE_MESSAGE_HIT)
	{
		m_vDestPos = (*_pPos);
		return;
	}

	if(m_eBattleMessage == BATTLE_MESSAGE_MOVE)
	{
		//cout << "헬로!" << endl;
		m_pMovement->SetMove(true);
	}
	else if(m_eBattleMessage == BATTLE_MESSAGE_ATTACK)
	{
		//거리가 멀리 있을때...
		D3DXVECTOR3 vSource(m_pInfo->m_vPos.x, 0.f, m_pInfo->m_vPos.z);
		D3DXVECTOR3 vDest(_pPos->x, 0.f, _pPos->z);
		D3DXVECTOR3 vDist = vSource - vDest;
		float fLength = D3DXVec3Length(&vDist);

		if(fLength >= 1.f)
		{
			m_pMovement->SetMove(true);
			m_eBattleMessage = BATTLE_MESSAGE_MOVE;
			m_bAttackMessage = true;
		}
	}
	else if(m_eBattleMessage == BATTLE_MESSAGE_ABILITY)
	{
		m_iSkillCount = 0;

		if(m_eCharacterID == CHARACTER_SIZZ)
		{
			m_eBattleMessage = BATTLE_MESSAGE_MAGIC;

			//이펙트 생성.
			ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, this, EFFECT_REDPARTICLE, m_pInfo->m_vPos.x, m_pInfo->m_vPos.y - 0.5f, m_pInfo->m_vPos.z);
			ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
		}
		else
		{	
			switch(m_iAbilityCur)
			{
			case 0:
				m_eBattleMessage = BATTLE_MESSAGE_SKILL1;
				break;

			case 1:
				m_eBattleMessage = BATTLE_MESSAGE_SKILL2;
				break;
			}
			//만약에 거리가 멀리있을경우 달려가야한다..

			if(m_eCharacterID == CHARACTER_ELLUARD)
			{
				D3DXVECTOR3 vSource(m_pInfo->m_vPos.x, 0.f, m_pInfo->m_vPos.z);
				D3DXVECTOR3 vDest(_pPos->x, 0.f, _pPos->z);
				D3DXVECTOR3 vDist = vSource - vDest;
				float fLength = D3DXVec3Length(&vDist);

				if(fLength >= 0.5f)
				{
					m_eBattleMessage = BATTLE_MESSAGE_MOVE;

					m_pMovement->SetMove(true);
					m_bSkillRun = true;
				}
			}
			
			if(m_eCharacterID == CHARACTER_MARIA)
			{
				D3DXVECTOR3 vSource(m_pInfo->m_vPos.x, 0.f, m_pInfo->m_vPos.z);
				D3DXVECTOR3 vDest(_pPos->x, 0.f, _pPos->z);
				D3DXVECTOR3 vDist = vSource - vDest;
				float fLength = D3DXVec3Length(&vDist);

				if(fLength >= 0.5f)
				{
					if(m_eBattleMessage == BATTLE_MESSAGE_SKILL1)
					{
						m_eBattleMessage = BATTLE_MESSAGE_SKILL1_RUN;
					}
					else if(m_eBattleMessage == BATTLE_MESSAGE_SKILL2)
					{
						m_eBattleMessage = BATTLE_MESSAGE_SKILL2_RUN;
					}

					m_pMovement->SetMove(true);
					m_bSkillRun = true;
				}
			}
		}
	}
	//! 문제 일으킬까?
	else if (ENGINE::GetInputManager()->GetOnEvent())
	{
		//거리가 멀리 있을때...
		D3DXVECTOR3 vSource(m_pInfo->m_vPos.x, 0.f, m_pInfo->m_vPos.z);
		D3DXVECTOR3 vDest(_pPos->x, 0.f, _pPos->z);
		D3DXVECTOR3 vDist = vSource - vDest;
		float fLength = D3DXVec3Length(&vDist);

		if(fLength >= 1.f)
		{
			m_pMovement->SetMove(true);
			m_eBattleMessage = BATTLE_MESSAGE_MOVE;
			m_bAttackMessage = true;
		}
	}

	m_vDestPos = *_pPos;
}

void ENGINE::CCharacter::SetBattleMessage(eBattleMessage _Message)
{
	m_eBattleMessage = _Message;
}

void ENGINE::CCharacter::SetCamera(void)
{
	
}

void ENGINE::CCharacter::SetBillBoard(void)
{	
	this->SetBattleAngle();
	m_pInfo->Update();
	
	D3DXMATRIX matBill;
	ENGINE::GetDevice()->GetTransform(D3DTS_VIEW, &matBill);
	ZeroMemory(matBill.m[3], sizeof(float) * 3);
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;
}

void ENGINE::CCharacter::Render(void)
{
	LPDIRECT3DDEVICE9 pDevice = ENGINE::GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pTexture->Render((int)m_pSpriteFrame->GetCurFrame());
	m_pVIBuffer->Render();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pOBBCollision->Render();

	/*if(m_eBattleMessage == BATTLE_MESSAGE_HIT)
	{
		cout << m_pSpriteFrame->GetCurFrame() << endl;
	}*/
}

void ENGINE::CCharacter::SetOwner(CCharacterGroup* _pOwner)
{
	m_pOwner = _pOwner;
}

ENGINE::CCharacterGroup* ENGINE::CCharacter::GetOwner(void)
{
	return m_pOwner;
}	

void ENGINE::CCharacter::SetCharacterState(eCharacterState _State)
{
	m_eState = _State;
}

void ENGINE::CCharacter::ResetCharacter(void)
{
	//초기위치로 돌려주는 코드...
	m_ePrevState = Character_End;
	m_eState = Character_Stand;
	m_pSpriteFrame->SetFrame(FRAME(2.f, 2.f, 10.f));
}

eUnitType ENGINE::CCharacter::GetUnitType(void)
{
	return m_eUnitType;
}	

float ENGINE::CCharacter::GetLengthToDest(void)
{
	D3DXVECTOR3 vPos = m_pInfo->m_vPos;
	vPos.y = 0.f;
	D3DXVECTOR3 vDist = m_vDestPos - vPos;
	return D3DXVec3Length(&vDist);
}

void ENGINE::CCharacter::CharacterHit(int _iAtk, D3DXVECTOR3 _vDir, D3DXVECTOR3 _vDest)
{
	if(m_eBattleMessage == BATTLE_MESSAGE_DEFENSE)
	{
		ENGINE::CGameObject* pObj = ENGINE::CEffect::Create(OBJECT_TYPE_DYNAMIC, this, EFFECT_GUARD, m_pInfo->m_vPos.x, m_pInfo->m_vPos.y + 0.5f, m_pInfo->m_vPos.z);
		ENGINE::GetManagement()->AddGameObject(L"Effect", 1, pObj);
		ENGINE::GetSoundManager()->PlaySound(L"GuardSound.wav");

		return;
	}

	m_eBattleMessage = BATTLE_MESSAGE_HIT;

	if(m_tCharacterState.iBarrierPoint > 0)
	{
		m_tCharacterState.iBarrierPoint -= _iAtk;

		if(m_tCharacterState.iBarrierPoint < 0)
		{
			m_tCharacterState.iBarrierPoint = 0;
		}
	}
	else
	{
		m_tCharacterState.iHitPoint -= _iAtk;

		if(m_tCharacterState.iHitPoint < 0)
		{
			m_tCharacterState.iHitPoint = 0;
		}
	}

	m_vDestPos = _vDest;

	m_bAttackMessage = false;

	m_vHitDir = _vDir;
}

void ENGINE::CCharacter::SetAbilityCur(int _iCur)
{
	m_iAbilityCur = _iCur;
}

void ENGINE::CCharacter::SetMonsterTarget(CMonster* _pMonsterTarget)
{
	m_pTargetMonster = _pMonsterTarget;
}

void ENGINE::CCharacter::SetPos(float _fX, float _fZ)
{
	m_pInfo->m_vPos.x = _fX;
	m_pInfo->m_vPos.z = _fZ;
}

void ENGINE::CCharacter::SetSpeed(float _fSpeed)
{
	m_pMovement->SetSpeed(_fSpeed);
}

void ENGINE::CCharacter::SetSkillCharge(bool _bCharge)
{
	m_bSkillCharge = _bCharge;
}

bool ENGINE::CCharacter::BattleResult(int _iExp)
{
	m_tCharacterState.iExp += _iExp;

	if(m_tCharacterState.iExp >= m_tCharacterState.iNextExp)
	{
		++m_tCharacterState.iLevel;

		//int iResult = m_tCharacterState.iExp - m_tCharacterState.iNextExp;

		m_tCharacterState.iExp = 0;

		m_tCharacterState.iATK += 3;
		m_tCharacterState.iDEF += 3;
		m_tCharacterState.iMaxHitPoint += 5;
		m_tCharacterState.iMaxBarrierPoint += 5;
		m_tCharacterState.iHitPoint = m_tCharacterState.iMaxHitPoint;
		m_tCharacterState.iBarrierPoint = m_tCharacterState.iMaxBarrierPoint;
		m_tCharacterState.iSPD += 2;
		m_tCharacterState.iNextExp += 10;

		m_tTempState = m_tCharacterState;

		return true;
	}

	return false;
}


D3DXVECTOR3 ENGINE::CCharacter::GetDestPos(void)
{
	return m_vDestPos;

}

void ENGINE::CCharacter::SetCharacterStatus(CHARACTER_STATE _Status)
{
	m_tCharacterState = _Status;
}

D3DXVECTOR3 ENGINE::CCharacter::GetPos(void)
{
	return m_pInfo->m_vPos;
}

CHARACTER_STATE ENGINE::CCharacter::GetOriginStatus(void)
{
	return m_tTempState;
}

void ENGINE::CCharacter::SetState(int _iBp, int _iAtk, int _iDef, int _iSpd, int _iMag, int _iCri)
{
	m_tCharacterState.iBarrierPoint = m_tTempState.iBarrierPoint + _iBp;
	m_tCharacterState.iMaxBarrierPoint = m_tTempState.iMaxBarrierPoint + _iBp;
	m_tCharacterState.iATK = m_tTempState.iATK + _iAtk;
	m_tCharacterState.iDEF = m_tTempState.iDEF + _iDef;
	m_tCharacterState.iSPD = m_tTempState.iSPD + _iSpd;
	m_tCharacterState.iMAG = m_tTempState.iMAG + _iMag;
	m_tCharacterState.iCRI = m_tTempState.iCRI + _iCri;
}
