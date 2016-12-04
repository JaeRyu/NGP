#include"stdafx.h"
#include"ClientManager.h"


void CClientManager::Init(HINSTANCE hInst)
{
	gameState = 0;
	hBackground = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	hPlane = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PLANE));
	hPlayerBullet = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PBULLET));
	hEnemyBullet = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EBULLET));
	hEnemy[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MOB1));
	hEnemy[10] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MOB11));
	hExplosion = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EXPLOS));
	redBrush = CreateSolidBrush(RGB(255, 0, 0));

	hFontScore = CreateFont(20, 0, 0, 0, FW_EXTRABOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, "굴림");
	SoundManager.PlayWait();
}

void CClientManager::DrawScore(HDC hdc)
{
	//HDC memdc2 = CreateCompatibleDC(hdc);
	oldFont = (HFONT)SelectObject(hdc, hFontScore);
	char a[20];
	wsprintf(a, "내 점수 : %d", score);
	TextOut(hdc, 20, 50, a, strlen(a));

	char a2[20];
	wsprintf(a2, "팀 점수 : %d", pscore);
	TextOut(hdc, 20, 80, a2, strlen(a2));

	SelectObject(hdc, oldFont);
}

void CClientManager::DrawDummy(HDC hdc)
{

	// 폭발 출력
	for (std::list<DESTROYED>::iterator p = vDestroy.begin(); p != vDestroy.end(); ++p)
	{
		p->Draw(hdc, hExplosion, oldbit);
	}

	vDestroy.remove_if([](DESTROYED a)
	{
		return a.animNum > 11;
	}
	);
}

void CClientManager::DrawHP(HDC hdc)
{
	oldBrush = (HBRUSH)SelectObject(hdc, redBrush);
	Rectangle(hdc, 10, 10, iHp * 20, 20);
	SelectObject(hdc, oldBrush);
}

void CClientManager::DrawWaitScene(HDC hdc)
{
	char *ch = "다른 플레이어를 기다리는 중 입니다.";
	TextOut(hdc, 40, 400, ch, strlen(ch));
}

void CClientManager::DrawEndScene(HDC hdc)
{
	DrawBackground(hdc, m_MapY);

	SetTextColor(hdc, RGB(255, 0, 0));
	char a[20];
	wsprintf(a, "내 점수 : %d", score);
	TextOut(hdc, 50, 200, a, strlen(a));

	SetTextColor(hdc, RGB(0, 255, 255));
	char a2[20];
	wsprintf(a2, "상대 점수 : %d", pscore);
	TextOut(hdc, 50, 250, a2, strlen(a2));

	char a3[100];
	if (score > pscore)
	{
		
		wsprintf(a3,"이겼습니다!!");
		TextOut(hdc, 50, 100, a3, strlen(a3));

	}
	else if (score == pscore)
	{
		wsprintf(a3, "동점입니다!!");
		TextOut(hdc, 50, 100, a3, strlen(a3));

	}
	else
	{
		wsprintf(a3, "졌습니다!!");
		TextOut(hdc, 50, 100, a3, strlen(a3));

	}

}

void CClientManager::UpdateDummy()
{
	for (std::list<DESTROYED>::iterator p = vDestroy.begin(); p != vDestroy.end(); ++p)
	{
		p->animNum += 1;
	}
}

void CClientManager::ChangeGameState(int number)
{
	gameState = number;
	if (gameState == 1)
	{
		SoundManager.StopWait();
		SoundManager.PlayBackGround();
	}
	else if (gameState == 2)
	{
		SoundManager.StopBackGround();
		SoundManager.PlayLogOut();
	}
}

int CClientManager::GetGameState()
{
	return gameState;
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
		vBullet[p].Draw(hdc, hPlayerBullet, hEnemyBullet, oldbit);
	
	}
	

	//적 출력
	for (int p = 0; p < vEnemy.size(); ++p)
	{
		if (vEnemy[p].GetInfo().state == 0)
		{
			DESTROYED d;
			d.info = vEnemy[p].GetInfo();
			d.animNum = 0;
			vDestroy.push_back(d);
			SoundManager.PlayBomb();
		}
		else
		vEnemy[p].Draw(hdc, hEnemy[vEnemy[p].GetType()-1], oldbit);
	}
		

	//비행기 출력
	for (int p = 0; p < vPlane.size(); ++p)
	{
		vPlane[p].Draw(hdc, hPlane, oldbit);
	}

	DrawDummy(hdc);
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



