#include "SoundManager.h"

IMPLEMENT_SINGLETON(ENGINE::CSoundManager)

ENGINE::CSoundManager::CSoundManager(void)
:m_pCurrentBGM(NULL)
{
	m_pSystem = NULL;

	Initialize();
}

ENGINE::CSoundManager::~CSoundManager(void)
{
	Release();
}


void ENGINE::CSoundManager::Initialize(void)
{
	m_Result = FMOD_System_Create(&m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::ErrorCheck(FMOD_RESULT _result)
{
	if(_result != FMOD_OK)
	{
		//cout << "sound error : " << _result << endl;
		return;
	}
}


void ENGINE::CSoundManager::LoadSoundFile(void)
{
	_finddata_t fd;

	long handle;
	int iResult = 1;

	handle = _findfirst("..\\bin\\Resources\\Sounds\\*.*", &fd);		//해당경로 모두 읽어라.
	//handle = -1;

	if (handle == -1)
	{
		return;
	}

	while(iResult != -1)
	{
		TCHAR szName[256];

		ZeroMemory(szName, sizeof(szName));	//메크로 함수.

		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,
			fd.name, strlen(fd.name), szName, 256);
		//멀티바이트를 유니코드로 변경.

		TCHAR* pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);
		lstrcpy(pName, szName);

		char szFullName[256];

		strcpy_s(szFullName, "..\\bin\\Resources\\Sounds\\");
		strcat_s(szFullName, fd.name);


		FMOD_SOUND* pSound;

		m_Result = FMOD_System_CreateSound(m_pSystem, szFullName, FMOD_HARDWARE, 0, &pSound);

		if(m_Result == FMOD_OK)
		{
			m_mapSound.insert( std::make_pair(pName, pSound) );
		}
		else
		{
			delete [] pName;
		}

		iResult = _findnext(handle, &fd);		//모든탐색을 한다.

	}

	_findclose(handle);

	m_Result = FMOD_System_Update(m_pSystem);

	ErrorCheck(m_Result);

}

void ENGINE::CSoundManager::PlaySound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlayBGM(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	// 같은 bgm이면 걍 계속 재생
	if (iter->first ==  m_pCurrentBGM)
		return;

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pBGM);
	ErrorCheck(m_Result);

	m_Result = FMOD_Channel_SetVolume(m_pBGM, 0.1f);
	ErrorCheck(m_Result);

	m_pCurrentBGM = iter->first;
}


void ENGINE::CSoundManager::StopBGM(void)
{
	m_Result  = FMOD_Channel_Stop(m_pBGM);
	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::StopSoundAll(void)
{
	m_Result  = FMOD_Channel_Stop(m_pBGM);
	ErrorCheck(m_Result);
}


void ENGINE::CSoundManager::PauseBGM(void)
{
	m_Result = FMOD_Channel_SetPaused(m_pBGM, true);
	ErrorCheck(m_Result);
}


void ENGINE::CSoundManager::Release(void)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter = m_mapSound.begin();
	map<TCHAR*, FMOD_SOUND*>::iterator iter_end = m_mapSound.end();

	for (; iter != iter_end; ++iter)
	{
		delete (*iter).first;
	}

	m_mapSound.clear();
}

void ENGINE::CSoundManager::PlaySizzSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pSizz);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlayMariaSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pMaria);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlayElluardSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pElluard);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlayTenziSound(TCHAR* pSoundKey)
{	
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
	return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									 iter->second, 0, &m_pEffect);

	m_Result = FMOD_Channel_SetVolume(m_pTenzi, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlayWildBoarSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pWildBoar);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlayHedgehogSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pHedgehog);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlayChimeraSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pChimera);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlaySpiderSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pSpider);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlayPoisonJellySound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pJelly);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlaySkeletonSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pSkeleton);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlayAkhenatonSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pAkhenaton);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}

void ENGINE::CSoundManager::PlayWeaponSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pWeapon);

	m_Result = FMOD_Channel_SetVolume(m_pEffect, 1.f);
	ErrorCheck(m_Result);

	ErrorCheck(m_Result);
}
