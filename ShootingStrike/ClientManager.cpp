#include"stdafx.h"
#include"ClientManager.h"


void CClientManager::Init(HINSTANCE hInst)
{
	hBackground = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	hPlane = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PLANE));
	hPlayerBullet = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PBULLET));
}

CClientManager::CClientManager()
{
}


CClientManager::~CClientManager()
{
}

bool CClientManager::DrawObejct(HDC hdc)
{
	//비행기 출력
	//printf("PlaneSize = %d\n", vPlane.size());
	for (int p = 0; p < vPlane.size(); ++p)
	{
		vPlane[p].Draw(hdc, hPlane, oldbit);
	}
	
	//적 출력

	//총알 출력
	printf("BulletSize = %d\n", vBullet.size());
	for(int p = 0; p<vBullet.size(); ++p)
	{
		vBullet[p].Draw(hdc, hPlayerBullet, oldbit);
	}

	return true;
}

bool CClientManager::DrawBackground(HDC hdc, int& mapY)
{
	HDC memdc2 = CreateCompatibleDC(hdc);
	oldbit = (HBITMAP)SelectObject(memdc2, hBackground);

	if (m_MapY < 0)
	{
		StretchBlt(hdc, 0, 0, windowSizeW, windowsizeH, memdc2, 0, 8030 + m_MapY, 900, 800, SRCCOPY);
		/*if (mapY < -800)
			mapY = 7230;*/
	}

	StretchBlt(hdc, 0, 0, windowSizeW, windowsizeH, memdc2, 0, m_MapY, 900, 800, SRCCOPY);
	SelectObject(memdc2, oldbit);


	DeleteObject(memdc2);
	DeleteObject(oldbit);
	return false;
}



