#pragma once
#include"userInclude.h"

#define MAX_SOUND 1

class CSoundMgr {
private:
	FMOD::System  *pSystem;
	FMOD::Sound *pSound[MAX_SOUND];
	FMOD::Channel *pChannel[MAX_SOUND];
	bool bgm;
public:
	void PlayBackGround();
	void StopBackGround();
	CSoundMgr();
	~CSoundMgr();
};