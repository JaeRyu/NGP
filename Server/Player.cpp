#include "Player.h"

CPlayer::CPlayer()
{
	ZeroMemory(&m_PlayerMove, sizeof(KEYDATA));
	m_tInfo.posX = 200;
	m_tInfo.posY = 600;
	shootTime = GetTickCount();
	iHp = 10;
}
int CPlayer::Update(void)
{

	if (m_PlayerMove.key[0] == true)
	{
		Move(0, -5);
	}

	if (m_PlayerMove.key[1] == true)
	{
		Move(0, 5);
	}

	if (m_PlayerMove.key[2] == true)
	{
		Move(-5, 0);
	}

	if (m_PlayerMove.key[3] == true)
	{
		Move(5, 0);
	}



	return 0;
}

void CPlayer::PlayerMove(void)
{
	
}

void CPlayer::Initialize(void)
{
	
}

DWORD CPlayer::GetShootTime(void)
{
	return shootTime;
}

void CPlayer::ResetTime(void)
{
	shootTime = GetTickCount();
}

CPlayer::~CPlayer()
{
}
