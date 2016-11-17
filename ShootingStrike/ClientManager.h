#pragma once

#include"userInclude.h"


class CClientManager
{
	HBITMAP hBullet;
	HBITMAP hPlane;
	HBITMAP hEnemy;
	HBITMAP hBackground;
	HBITMAP oldbit;

public:
	bool DrawObejct(HDC hdc);
	bool DrawBackground(HDC hdc, int& mapY);
	void Init(HINSTANCE hInst);
	std::vector<CPlane> vPlane;

	CClientManager();
	~CClientManager();
};

