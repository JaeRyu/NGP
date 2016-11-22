#include"stdafx.h"
#include"ClientManager.h"


void CClientManager::Init(HINSTANCE hInst)
{
	hBackground = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	hPlane = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PLANE));
	hPlayerBullet = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PBULLET));
	hEnemy[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MOB1));
	hEnemy[10] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MOB11));

}

void CClientManager::DrawScore(HDC hdc)
{
	//HDC memdc2 = CreateCompatibleDC(hdc);
	char a[20];
	wsprintf(a, "%d", score);
	TextOut(hdc, 20, 400, a, strlen(a));
}

CClientManager::CClientManager()
{
}


CClientManager::~CClientManager()
{
}

bool CClientManager::DrawObejct(HDC hdc)
{
	
	//총알 출력
	
	for (int p = 0; p<vBullet.size(); ++p)
	{
		vBullet[p].Draw(hdc, hPlayerBullet, oldbit);
	}
	

	//적 출력
	for (int p = 0; p < vEnemy.size(); ++p)
	{
		vEnemy[p].Draw(hdc, hEnemy[vEnemy[p].GetType()-1], oldbit);
	}
		

	//비행기 출력
	for (int p = 0; p < vPlane.size(); ++p)
	{
		vPlane[p].Draw(hdc, hPlane, oldbit);
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



