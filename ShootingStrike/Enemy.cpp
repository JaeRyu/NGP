#include "stdafx.h"
#include "Enemy.h"


void CEnemy::Draw(HDC hdc, HBITMAP hBitmap, HBITMAP oldbit)
{
	HDC memdc2 = CreateCompatibleDC(hdc);

	oldbit = (HBITMAP)SelectObject(memdc2, hBitmap);

	if (type < 10)
	{
		TransparentBlt(hdc, m_info.posX, m_info.posY, 50, 50, memdc2, 0, 0, 32, 32, RGB(255, 255, 255));
	}
	else
	{
		TransparentBlt(hdc, m_info.posX, m_info.posY, 100, 100, memdc2, 0, 0, 64, 64, RGB(255, 255, 255));
	}
	SelectObject(memdc2, oldbit);

	DeleteObject(memdc2);
	DeleteObject(oldbit);
}

CEnemy::CEnemy(OBJECTINFO info)
{
	SetInfo(info.info);
	type = info.type;
}

CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}
