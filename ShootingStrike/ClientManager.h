#pragma once

#include"userInclude.h"


class CClientManager
{
	HBITMAP hPlayerBullet;
	HBITMAP hPlane;
	HBITMAP hEnemy[11];
	
	HBITMAP hBackground;
	HBITMAP oldbit;
	int score;
public:
	bool DrawObejct(HDC hdc);
	bool DrawBackground(HDC hdc, int& mapY);
	void Init(HINSTANCE hInst);
	void DrawScore(HDC hdc);
	void SetScore(int s) { score = s; }
public:
	std::vector<CPlane> vPlane;
	std::vector<CBullets> vBullet;
	std::vector<CEnemy> vEnemy;
	int m_MapY;
public:
	CClientManager();
	~CClientManager();
};

