#pragma once

#include"userInclude.h"

class CBullets : public CGameObject
{
	/*�����Ѿ� : 0, ���Ѿ� : 1 */
	int type;
public:
	void setType(int tType) { type = tType; }
	int GetType() { return type; }
	void Draw(HDC hdc, HBITMAP hBitmap, HBITMAP hEnemyBullet, HBITMAP oldbit);


public:
	CBullets(IBULLET iBullet);
	CBullets();
	~CBullets();
};

