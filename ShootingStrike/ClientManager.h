#pragma once

#include"userInclude.h"


class CClientManager
{
	HBITMAP hPlayerBullet;
	HBITMAP hPlane;
	HBITMAP hEnemy;
	
	HBITMAP hBackground;
	HBITMAP oldbit;

public:
	bool DrawObejct(HDC hdc);
	bool DrawBackground(HDC hdc, int& mapY);
	void Init(HINSTANCE hInst);
public:
	std::vector<CPlane> vPlane;
	std::vector<CBullets> vBullet;
	int m_MapY;
public:
	CClientManager();
	~CClientManager();
};

