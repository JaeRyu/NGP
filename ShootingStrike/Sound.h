#pragma once
#include"userInclude.h"

#define MAX_SOUND 4

class CSoundMgr {
private:
	FMOD::System  *pSystem;
	FMOD::Sound *pSound[MAX_SOUND];
	FMOD::Channel *BGMChannel;
	FMOD::Channel *waitChannel;
	FMOD::Channel *bombChannel;
	FMOD::Channel *outChannel;
	bool bgm;
	bool wait;
	bool logout;

public:
	void PlayBackGround();
	void StopBackGround();
	void PlayWait();
	void StopWait();

	void PlayLogOut();
	void PlayBomb();
	CSoundMgr();
	~CSoundMgr();
};