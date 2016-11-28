#include "Enemy.h"

int CEnemy::Update(void)
{
	Move(m_dx, m_dy);	//�ϴ� ������������.

	if (iHp <= 0)
		ChangeState(0);

	if (m_dx > 0)
	{
		if (m_tInfo.posX > 550)
			ChangeState(0);
	}
	else if(m_dx < 0)
	{
		if (m_tInfo.posX < -100)
			ChangeState(0);
	}

	if (iType > 10)
	{
		if (m_dy > 0)
		{
			if (m_tInfo.posY > 350)
				m_dy *= -1;
		}

		if (m_dy < 0)
		{
			if (m_tInfo.posY < 100)
				m_dy *= -1;
		}
	}
	

	return 0;
}
int CEnemy::SetVector(int dx, int dy)
{
	m_dx = dx;
	m_dy = dy;
	return 0;
}
EnemyInfo CEnemy::GetPos(void)
{
	EnemyInfo tInfo;
	tInfo.info = m_tInfo;
	tInfo.type = iType;
	return tInfo;
}

RECT CEnemy::GetRect(void)
{
	{
		RECT rc;
		if (iType < 10)
		{
			rc.left = m_tInfo.posX + 10;
			rc.right = m_tInfo.posX + 40;
			rc.bottom = m_tInfo.posY + 40;
			rc.top = m_tInfo.posY + 10;
		}
		else
		{
			rc.left = m_tInfo.posX + 20;
			rc.right = m_tInfo.posX + 80;
			rc.bottom = m_tInfo.posY + 80;
			rc.top = m_tInfo.posY + 20;
		}

		return rc;
	}
}

DWORD CEnemy::GetTime()
{
	return GetTickCount() - dTime;
}

void CEnemy::SetTimeZero()
{
	dTime = GetTickCount();
}

void CEnemy::SetShootRate(int p)
{
	shootRate = p;
}

int CEnemy::GetShootRate()
{
	return shootRate;
}

void CEnemy::HitDamage(int damage)
{
	iHp -= damage;
}

CEnemy::CEnemy(short posX, short posY, int Type)
{
	shootRate = 1000;
	iType = Type;
	if (iType < 10)
		iHp = 5;
	else
		iHp = 100;
	m_tInfo.state = 1;
	m_tInfo.posX = posX;
	m_tInfo.posY = posY;
	dTime = GetTickCount();
}


CEnemy::~CEnemy()
{
}
