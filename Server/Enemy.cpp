#include "Enemy.h"

int CEnemy::Update(void)
{
	Move(0, 0);	//일단 움직이지말자.

	return 0;
}
EnemyInfo CEnemy::GetPos(void)
{
	EnemyInfo tInfo;
	tInfo.info = m_tInfo;
	tInfo.type = iType;
	return tInfo;
}

CEnemy::CEnemy(short posX, short posY, int Type)
{
	iType = Type;
	iHp = 5;
	m_tInfo.state = 1;
	m_tInfo.posX = posX;
	m_tInfo.posY = posY;
}


CEnemy::~CEnemy()
{
}
