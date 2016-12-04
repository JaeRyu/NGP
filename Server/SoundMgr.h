#pragma once

#include "define.h"

class CSoundMgr
{
public:
	DECLARE_SINGLETON(CSoundMgr)
	
	//�������� �����°͸� ä�� �ϳ� ������.


private:
	FMOD_SYSTEM*	m_pSystem;			//fmod �ý��� ������
	FMOD_CHANNEL*	m_pEffect;
	FMOD_RESULT		m_Result;		//�����ߵǴ��� Ȯ���ϴ� ����.

	unsigned int m_iVersion;

	std::map<char*, FMOD_SOUND*>		m_mapSound;		//���� ����(map)

public:
	void Initialize(void);
	void LoadSoundFile(void);
	void ShootBullet(char* pSoundKey);
	void ErrorCheck(FMOD_RESULT _result);


public:
	CSoundMgr();
	~CSoundMgr();
};

