#include "SoundMgr.h"

IMPLEMENT_SINGLETON(CSoundMgr)

CSoundMgr::CSoundMgr()
{
	m_pSystem = NULL;
	m_iVersion = 0;

	Initialize();
}


CSoundMgr::~CSoundMgr()
{
}

void CSoundMgr::Initialize(void)
{
	m_Result = FMOD_System_Create(&m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_GetVersion(m_pSystem, &m_iVersion);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(m_Result);
}

void CSoundMgr::LoadSoundFile(void)
{
	_finddata_t fd;

	long handle;
	int iResult = 1;

	handle = _findfirst("..\\SoundFile\\*.*", &fd);		//해당경로 모두 읽어라.

	if (handle == -1)
	{
		return;
	}

	while (iResult != -1)
	{
		char szName[256];

		ZeroMemory(szName, sizeof(szName));	//메크로 함수.

		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,
			fd.name, lstrlen(fd.name), (LPWSTR)szName, 256);
		

		char* pName = new char[256];
		ZeroMemory(pName, sizeof(char) * 256);
		lstrcpy(pName, szName);

		char szFullName[256];

		strcpy_s(szFullName, "..\\SoundFile\\");
		strcat_s(szFullName, fd.name);


		FMOD_SOUND* pSound;

		m_Result = FMOD_System_CreateSound(m_pSystem, szFullName, FMOD_HARDWARE, 0, &pSound);

		if (m_Result == FMOD_OK)
		{
			m_mapSound.insert(make_pair(pName, pSound));
		}
		else
		{
			delete[] pName;
		}

		iResult = _findnext(handle, &fd);		//모든탐색을 한다.

	}

	_findclose(handle);

	m_Result = FMOD_System_Update(m_pSystem);

	ErrorCheck(m_Result);
}

void CSoundMgr::ShootBullet(char * pSoundKey)
{
	map<char*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if (iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect);

	ErrorCheck(m_Result);
}

void CSoundMgr::ErrorCheck(FMOD_RESULT _result)
{
	if (_result != FMOD_OK)
	{
		cout << "오류" << endl;
		return;
	}
}

