#include "stdafx.h"
#include "Bullet.h"


void CBullets::Draw(HDC hdc, HBITMAP hBitmap, HBITMAP oldbit)
{
	HDC memdc2 = CreateCompatibleDC(hdc);

	oldbit = (HBITMAP)SelectObject(memdc2, hBitmap);

	TransparentBlt(hdc, m_info.posX, m_info.posY, 50, 50, memdc2, 0, 0, 32, 32, RGB(255, 255, 255));
	SelectObject(memdc2, oldbit);

	DeleteObject(memdc2);
	DeleteObject(oldbit);
}


CBullets::CBullets(IBULLET iBullet)
{
	SetInfo(iBullet.info);
	type = iBullet.type;
}

CBullets::CBullets()
{
}


CBullets::~CBullets()
{
}
