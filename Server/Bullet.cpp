#include<stdio.h>
#include "Bullet.h"

CBullet::CBullet()
{
	m_tInfo.state = 1;
}


CBullet::~CBullet()
{
}
int CBullet::Update(void)
{
	Move(m_dx, m_dy);
	if (m_tInfo.posY < 0 || m_tInfo.posY > 850)
			ChangeState(0);

	return 0;
}

void CBullet::SetType(int tType)
{
	type = tType;
}

void CBullet::SetClient(int c)
{
	client = c;
}

int CBullet::GetClient()
{
	return client;
}

void CBullet::SetVector(int dx, int dy)
{
	m_dx = dx;
	m_dy = dy;
}


int CBullet::GetType(void)
{
	return type;
}

IBULLET CBullet::GetBulletInfo(void)
{
	IBULLET tinfo;
	tinfo.info = m_tInfo;
	tinfo.type = type;

	return tinfo;
}



void CBullet::Initialize(void)
{
}

void CBullet::Release(void)
{
}