#pragma once

#include"userInclude.h"


class CEnemy : public CGameObject
{
	/*Àâ¸÷ : 1~9, º¸¼ö : 11~ */
	int type;
public:
	void Draw(HDC hdc, HBITMAP hBitmap, HBITMAP oldbit);
	int GetType() { return type; }
public:
	CEnemy(OBJECTINFO info);
	CEnemy();
	~CEnemy();
};

