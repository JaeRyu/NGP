#pragma once

#include "define.h"

class CSoundMgr
{
public:
	DECLARE_SINGLETON(CSoundMgr)
	
	//서버에서 나가는것만 채널 하나 만들자.


private:
	FMOD_SYSTEM*	m_pSystem;			//fmod 시스템 포인터
	FMOD_CHANNEL*	m_pEffect;
	FMOD_RESULT		m_Result;		//실행잘되는지 확인하는 변수.

	unsigned int m_iVersion;

	std::map<char*, FMOD_SOUND*>		m_mapSound;		//사운드 관리(map)

public:
	void Initialize(void);
	void LoadSoundFile(void);
	void ShootBullet(char* pSoundKey);
	void ErrorCheck(FMOD_RESULT _result);


public:
	CSoundMgr();
	~CSoundMgr();
};

