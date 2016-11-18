#include"stdafx.h"
#include"Plane.h"

CPlane::CPlane()
{
}

CPlane::~CPlane()
{
}

void CPlane::Draw(HDC hdc, HBITMAP hBitmap, HBITMAP oldbit)
{
	HDC memdc2 = CreateCompatibleDC(hdc);

	oldbit = (HBITMAP)SelectObject(memdc2, hBitmap);

	TransparentBlt(hdc, m_info.posX, m_info.posY, 50, 50, memdc2, 100, 0, 24, 33, RGB(255, 255, 255));
	SelectObject(memdc2, oldbit);

	DeleteObject(memdc2);
	DeleteObject(oldbit);
}