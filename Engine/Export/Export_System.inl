
CGraphicDevice* GetDeviceManager(void)
{
	return ENGINE::CGraphicDevice::GetInstance();
}

const LPDIRECT3DDEVICE9 GetDevice(void)
{
	return ENGINE::CGraphicDevice::GetInstance()->GetDevice();
}

const LPD3DXSPRITE GetSprite(void)
{
	return ENGINE::CGraphicDevice::GetInstance()->GetSprite();
}

const LPD3DXFONT GetFont(void)
{
	return ENGINE::CGraphicDevice::GetInstance()->GetFont();
}

CTimeManager* GetTimeManager(void)
{
	return ENGINE::CTimeManager::GetInstance();
}

const float GetTimeDelta(void)
{
	return ENGINE::CTimeManager::GetInstance()->GetTimeDelta();
}

const CCustomTimer* GetTimer(const wstring& _strTimerKey)
{
	return ENGINE::CTimeManager::GetInstance()->GetTimer(_strTimerKey);
}

CInputManager* GetInputManager(void)
{
	return ENGINE::CInputManager::GetInstance();
}
CBattleManager* GetBattleManeger(void)
{
	return ENGINE::CBattleManager::GetInstance();
}

CSoundManager* GetSoundManager(void)
{
	return ENGINE::CSoundManager::GetInstance();
}

