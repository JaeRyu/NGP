#include"stdafx.h"
#include"ClientManager.h"

bool CClientManager::DrawObejct(HDC hdc)
{
	//비행기 출력
	for each (auto p in vPlane)
	{
		p.Draw(hdc, hPlane, oldbit);
	}

	//총알 출력


	//적 출력



	return true;
}

bool CClientManager::DrawBackground(HDC hdc, int& mapY)
{
	HDC memdc2 = CreateCompatibleDC(hdc);
	oldbit = (HBITMAP)SelectObject(memdc2, hBackground);

	if (mapY < 0)
	{
		StretchBlt(hdc, 0, 0, windowSizeW, windowsizeH, memdc2, 0, 8030 + mapY, 900, 800, SRCCOPY);
		if (mapY < -800)
			mapY = 7230;
	}

	StretchBlt(hdc, 0, 0, windowSizeW, windowsizeH, memdc2, 0, mapY, 900, 800, SRCCOPY);
	SelectObject(memdc2, oldbit);


	DeleteObject(memdc2);
	DeleteObject(oldbit);
	return false;
}


void CClientManager::Init(HINSTANCE hInst)
{
	hBackground = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	hPlane = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PLANE));

	CPlane cp;
	INFO m;
	m.posX = 200;
	m.posY = 600;
	m.state = 0;

	cp.SetInfo(m);

	vPlane.push_back(cp);

	m.posX = 300;

	cp.SetInfo(m);

}

CClientManager::CClientManager()
{
}


CClientManager::~CClientManager()
{
}
