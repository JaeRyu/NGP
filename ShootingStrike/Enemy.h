#pragma once

#include"userInclude.h"


class CEnemy : CGameObject
{
	/*��� : 1~9, ���� : 11~ */
	int type;
public:
	void Draw(HDC hdc, HBITMAP hBitmap, HBITMAP oldbit);
	int GetType() { return type; }
public:
	CEnemy(OBJECTINFO info);
	CEnemy();
	~CEnemy();
};

