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
	Move(0, -5);
	if (m_tInfo.posY < 0 || m_tInfo.posY > 850)
			ChangeState(0);

	
	return 0;
}

void CBullet::SetType(int tType)
{
	type = tType;
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