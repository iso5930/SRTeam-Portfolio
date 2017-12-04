#include "stdafx.h"
#include "Navi.h"
#include "ResourceManager.h"
#include "GraphicDevice.h"
#include "Export_Function.h"
#include "Transform.h"
#include "GroupObserver.h"
#include "CharacterGroup.h"
#include "Character.h"
#include "Export_Utility.h"
#include "Page.h"
#include "MainMenu.h"

CNavi::CNavi(eObjectType _eObjectType)
:CGameObject(_eObjectType)
,m_fAngle(0.f), m_pNaviDir(NULL), m_pNavi(NULL), m_pGroupObserver(NULL)
, m_bHighAngle(false)
, iGoalNow(GOAL_START)
, m_bArr(false)
, m_bKeyInput(false)
{
	m_vGoal1 = D3DXVECTOR3(10.f, 0.f, 20.f);
	m_vGoal2 = D3DXVECTOR3(30.f, 0.f, 5.f);
	m_vGoal3 = D3DXVECTOR3(20.f, 0.f, 25.f);
}

CNavi::~CNavi(void)
{
	Release();
}

CNavi* CNavi::Create(eObjectType _eObjectType)
{
	CNavi* pNavi = new CNavi(_eObjectType);

	if(FAILED(pNavi->Initialize()))
	{
		SAFE_DELETE(pNavi);
	}

	return pNavi;
}

HRESULT CNavi::Initialize(void)
{
	m_fAngle = 0.f;

	m_pNavi = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"Navigation", 0);
	m_pNaviDir = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"Navigation", 1);
	m_pMessage = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"MessagePice", 0);

	m_pGroupObserver = ENGINE::CGroupObserver::Create(this);
	ENGINE::GetInfoSubject()->Subscribe(m_pGroupObserver);

	return S_OK;
}

int CNavi::Update(void)
{
	ENGINE::CGameObject* pMainMenu = ENGINE::GetManagement()->GetGameObject(L"ZZMainMenu");

	if(dynamic_cast<CMainMenu*>(pMainMenu)->GetUISwitch() == false)
	{
		return 0;
	}

	KeyCheak();

	m_vTagPos = m_pGroupObserver->GetCharacterGroup()->GetLeaderCharacter()->GetInfo()->m_vPos;

	return 0;
}

void CNavi::KeyCheak(void)
{
	POINT ptMouse;
	ENGINE::GetInputManager()->GetMousePos(&ptMouse);

	if(iGoalNow == 0)
		m_bArr = false;

	if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_F3))
	{
		++iGoalNow;

		if(iGoalNow >= GOAL_END)
			iGoalNow = GOAL_START;
	}
	else if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_F4))
	{
		--iGoalNow;
		
		if(iGoalNow < GOAL_START)
			iGoalNow = GOAL_END - 1;
	}
	else if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_LBUTTON) && iGoalNow < GOAL_END - 1)
	{
		if(ptMouse.x >= 0.f && ptMouse.x <= 125.f
			&& ptMouse.y >= 130.f && ptMouse.y <= 170.f)
			++iGoalNow;
	}
	else if(ENGINE::GetInputManager()->IsKeyDownNow(KEY_STATE_RBUTTON) && iGoalNow > 0)
	{
		if(ptMouse.x >= 0.f && ptMouse.x <= 125.f
			&& ptMouse.y >= 130.f && ptMouse.y <= 170.f)
			--iGoalNow;
	}
}

void CNavi::TextOut(D3DXMATRIX matWorld)
{
	LPD3DXSPRITE	pTest;
	pTest = ENGINE::GetDeviceManager()->GetSprite();

	RECT		rcTest;
	SetRect(&rcTest, -70, -30, 70, 200);

	TCHAR		szText[FULL_STRING];

	if(iGoalNow == GOAL_START)
		wsprintf(szText, L"이동방향");
	else if(iGoalNow == GOAL_1)
		wsprintf(szText, L"테스트1");
	else if(iGoalNow == GOAL_2)
		wsprintf(szText, L"테스트2");
	else if(iGoalNow == GOAL_3)
		wsprintf(szText, L"테스트3");
	else
		wsprintf(szText, L"알 수 없는 오류");

	pTest->SetTransform(&matWorld);

	ENGINE::CGraphicDevice::GetInstance()->GetFont()->DrawText(
		pTest,
		szText,
		lstrlen(szText),
		&rcTest,
		DT_CENTER | DT_NOCLIP | DT_VCENTER,
		D3DCOLOR_ARGB(255, 0, 0, 0));
}

void CNavi::Render(void)
{
	if(ENGINE::GetBattleManeger()->GetBattleStart())
	{
		return;
	}

	if(ENGINE::GetManagement()->GetGameObject(L"ResultBoard") != NULL)
	{
		return;
	}

	ENGINE::GetDevice()->EndScene();

	ENGINE::GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX matWorld;
	D3DXMATRIX matTrans;
	D3DXMATRIX matRotZ;

	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixTranslation(&matTrans, 65.f, 65.f, 0.f);

	D3DXMatrixIdentity(&matRotZ);

	//ENGINE::GetManagement()->PrepareFind();
	ENGINE::CComponent* pComponent = ENGINE::GetManagement()->GetComponent(L"Camera", L"Transform");
	if (pComponent == NULL)
		return;
	const ENGINE::CTransform* pCameraInfo = static_cast<const ENGINE::CTransform*>(pComponent);

	//=======이하 메세지박스=======================================================================================
	matWorld = matTrans;
	ENGINE::GetSprite()->SetTransform(&matWorld);
	m_pMessage = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"MessagePice", 0);
	ENGINE::GetSprite()->Draw(m_pMessage->pTexture, NULL, &D3DXVECTOR3(65.f, -65.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pMessage = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"MessagePice", 1);
	for(int i = 0; i < 2; ++i)
		ENGINE::GetSprite()->Draw(m_pMessage->pTexture, NULL, &D3DXVECTOR3(33.f - (33 * i), -65.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pMessage = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"MessagePice", 2);
	ENGINE::GetSprite()->Draw(m_pMessage->pTexture, NULL, &D3DXVECTOR3(-33.f, -65.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	m_pMessage = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"MessagePice", 6);
	ENGINE::GetSprite()->Draw(m_pMessage->pTexture, NULL, &D3DXVECTOR3(65.f, -75.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pMessage = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"MessagePice", 7);
	for(int i = 0; i < 2; ++i)
		ENGINE::GetSprite()->Draw(m_pMessage->pTexture, NULL, &D3DXVECTOR3(33.f - (33 * i), -75.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pMessage = ENGINE::GetResourceManager()->GetSpriteTexture(RESOURCE_TYPE_STATIC, L"MessagePice", 8);
	ENGINE::GetSprite()->Draw(m_pMessage->pTexture, NULL, &D3DXVECTOR3(-33.f, -75.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	TextOut(matWorld);
	//=============================================================================================================
	m_fAngle = pCameraInfo->m_pAngle[ANGLE_TYPE_Y];

	D3DXMatrixRotationZ(&matRotZ, -m_fAngle);

	matWorld = matRotZ * matTrans;

	ENGINE::GetSprite()->SetTransform(&matWorld);

	float fX = 64.f;
	float fY = 82.f;

	ENGINE::GetSprite()->Draw(m_pNavi->pTexture, NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	if(iGoalNow == GOAL_START)
	{
		m_fAngle = m_pGroupObserver->GetCharacterGroup()->GetLeaderCharacter()->GetAngle();
		//m_fAngle = m_pGroupObserver->GetCharacterGroup()->GetCharacter(CHARACTER_SIZZ)->GetAngle();
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	}
	else
	{
		m_fAngle = AngleCheak();
		m_fAngle -= pCameraInfo->m_pAngle[ANGLE_TYPE_Y];
		D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	}

	matWorld = matRotZ * matTrans;

	ENGINE::GetSprite()->SetTransform(&matWorld);

	if(m_bArr == false &&  pCameraInfo->m_vPos.x == 0.f)
		ENGINE::GetSprite()->Draw(m_pNaviDir->pTexture, NULL, &D3DXVECTOR3(9.f, 47.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	ENGINE::GetSprite()->End();

	ENGINE::GetDevice()->BeginScene();
}

float CNavi::AngleCheak(void)
{
	float fAngle = 0.f;

	D3DXVECTOR3		m_vDirection, m_vGoal;

	if(iGoalNow == GOAL_1)
		m_vGoal = m_vGoal1;
	if(iGoalNow == GOAL_2)
		m_vGoal = m_vGoal2;
	if(iGoalNow == GOAL_3)
		m_vGoal = m_vGoal3;

	m_vDirection = m_vGoal - m_vTagPos;

	D3DXVec3Normalize(&m_vDirection, &m_vDirection);
	D3DXVECTOR3		vDefaultLook = D3DXVECTOR3(0.f, 0.f, 1.f);

	fAngle = acosf(D3DXVec3Dot(&vDefaultLook, &m_vDirection));

	if(m_vGoal.x < m_vTagPos.x)
		fAngle = 2.0f * D3DX_PI - fAngle;

	if(m_vGoal.x >= m_vTagPos.x - 2.f
		&& m_vGoal.x <= m_vTagPos.x + 2.f
		&& m_vGoal.z >= m_vTagPos.z - 2.f
		&& m_vGoal.z <= m_vTagPos.z + 2.f)
		m_bArr = true;
	else
		m_bArr = false;

	return fAngle;
}

void CNavi::Release(void)
{
	SAFE_DELETE(m_pGroupObserver);
}