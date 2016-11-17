#include"stdafx.h"
#include"Plane.h"

CPlane::CPlane()
{
}

CPlane::~CPlane()
{
}

void CPlane::Draw(HDC hdc, HBITMAP hPlane, HBITMAP oldbit)
{
	HDC memdc2 = CreateCompatibleDC(hdc);

	//여긴 비행기 테스트중 테스트 완료후 이 함수에서 제거 예정
	//HBITMAP plane = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PLANE));
	oldbit = (HBITMAP)SelectObject(memdc2, hPlane);

	//TransparentBlt()
	TransparentBlt(hdc, m_info.posX, m_info.posY, 50, 50, memdc2, 100, 0, 24, 33, RGB(255, 255, 255));
	SelectObject(memdc2, oldbit);

	DeleteObject(memdc2);
	DeleteObject(oldbit);
}