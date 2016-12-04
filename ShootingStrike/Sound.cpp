#include "stdafx.h"
#include "Sound.h"

void CSoundMgr::PlayBackGround()
{
	if (!bgm)
	{
		pSystem->playSound(FMOD_CHANNEL_FREE, pSound[0], false, &BGMChannel);
		bgm = true;
	}
	//bool isPlaying;
	//BGMChannel->isPlaying(&isPlaying);

}

void CSoundMgr::StopBackGround()
{
	BGMChannel->stop();
	bgm = false;
}

void CSoundMgr::PlayWait()
{
	if (!wait)
	{
		pSystem->playSound(FMOD_CHANNEL_FREE, pSound[1], false, &waitChannel);
		wait = true;
	}
}

void CSoundMgr::StopWait()
{
	waitChannel->stop();
	wait = false;
}

void CSoundMgr::PlayLogOut()
{
	if (!logout)
	{
		pSystem->playSound(FMOD_CHANNEL_FREE, pSound[2], false, &outChannel);
		logout = true;
	}
}

void CSoundMgr::PlayBomb()
{
	pSystem->playSound(FMOD_CHANNEL_FREE, pSound[3], false, &bombChannel);
}

CSoundMgr::CSoundMgr()
{
	FMOD::System_Create(&pSystem);
	pSystem->init(4, FMOD_INIT_NORMAL, 0);
	pSystem->createSound("Sound/BGM.mp3", FMOD_LOOP_NORMAL, NULL, &pSound[0]);
	pSystem->createSound("Sound/Listen.mp3", FMOD_LOOP_NORMAL, NULL, &pSound[1]);
	pSystem->createSound("Sound/LogOut.mp3", FMOD_DEFAULT, NULL, &pSound[2]);
	pSystem->createSound("Sound/Bomb.wav", FMOD_DEFAULT, NULL, &pSound[3]);

	bgm = false;
	wait = false;
	logout = false;
}

CSoundMgr::~CSoundMgr()
{
	pSystem->release();
	pSystem->close();
}
