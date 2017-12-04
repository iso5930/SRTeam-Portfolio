/*!
 * \file SoundManager.h
 * \date 2016/06/23 22:42
 *
 * \author 박정민
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef SoundManager_h__
#define SoundManager_h__

#include "Engine_Include.h"

class CStringCmp
{
private:
	const TCHAR*		m_pName;

public:
	explicit CStringCmp(const TCHAR* pKey)
		:m_pName(pKey){}

public:
	template<typename T>
	bool operator () (T data)
	{
		return (!lstrcmp(data.first, m_pName));
	}
};

enum
{
	FULL_LENGTH = 256
};

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CSoundManager
{
	DECLARE_SINGLETON(CSoundManager)

	//Fmod 인터페이스
private:
	FMOD_SYSTEM*	m_pSystem;			//fmod 시스템 포인터
	FMOD_CHANNEL*	m_pEffect;
	FMOD_CHANNEL*	m_pWeapon;
	FMOD_CHANNEL*	m_pSizz;
	FMOD_CHANNEL*	m_pMaria;
	FMOD_CHANNEL*	m_pElluard;
	FMOD_CHANNEL*	m_pTenzi;
	FMOD_CHANNEL*	m_pWildBoar;
	FMOD_CHANNEL*	m_pHedgehog;
	FMOD_CHANNEL*	m_pChimera;
	FMOD_CHANNEL*	m_pSpider;
	FMOD_CHANNEL*	m_pJelly;
	FMOD_CHANNEL*	m_pSkeleton;
	FMOD_CHANNEL*	m_pAkhenaton;
	FMOD_CHANNEL*	m_pBGM;
	TCHAR* m_pCurrentBGM;

	FMOD_CHANNEL*	m_pEnemySound[10];


	FMOD_RESULT		m_Result;		//실행잘되는지 확인하는 변수.

	//unsigned int m_iVersion;

public:
	map<TCHAR*, FMOD_SOUND*>		m_mapSound;		//사운드 관리(map)

public:
	void Initialize(void);
	void LoadSoundFile(void);
	void PlaySound(TCHAR* pSoundKey);
	void PlayBGM(TCHAR* pSoundKey);
	void PlaySizzSound(TCHAR* pSoundKey);
	void PlayMariaSound(TCHAR* pSoundKey);
	void PlayElluardSound(TCHAR* pSoundKey);
	void PlayTenziSound(TCHAR* pSoundKey);
	void PlayWildBoarSound(TCHAR* pSoundKey);
	void PlayHedgehogSound(TCHAR* pSoundKey);
	void PlayChimeraSound(TCHAR* pSoundKey);
	void PlaySpiderSound(TCHAR* pSoundKey);
	void PlayPoisonJellySound(TCHAR* pSoundKey);
	void PlaySkeletonSound(TCHAR* pSoundKey);
	void PlayAkhenatonSound(TCHAR* pSoundKey);
	void PlayWeaponSound(TCHAR*	pSoundKey);




	void StopBGM(void); // 아예 끔
	void StopSoundAll(void); // 모두 끔

	void PauseBGM(void);

	void Release(void);

public:
	map<TCHAR*, FMOD_SOUND*>* GetSoundMap(void)
	{
		return &m_mapSound;
	}

private:
	void ErrorCheck(FMOD_RESULT _result);


private:
	explicit CSoundManager(void);
	virtual ~CSoundManager(void);
};
END_NAMESPACE

#endif // SoundManager_h__