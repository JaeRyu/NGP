#include "stdafx.h"
#include "Sound.h"

void CSoundMgr::PlayBackGround()
{
	if (!bgm)
	{
		pSystem->playSound(FMOD_CHANNEL_FREE, pSound[0], false, &pChannel[0]);
		bgm = true;
	}
}

void CSoundMgr::StopBackGround()
{
	pChannel[0]->stop();
	bgm = false;
}

CSoundMgr::CSoundMgr()
{
	FMOD::System_Create(&pSystem);
	pSystem->init(1, FMOD_HARDWARE, 0);
	pSystem->createSound("Sound/BGM.mp3",FMOD_LOOP_NORMAL,NULL, &pSound[0]);
	bgm = false;
}

CSoundMgr::~CSoundMgr()
{
	pSystem->release();
	pSystem->close();
}
