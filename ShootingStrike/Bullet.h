#pragma once

#include"userInclude.h"

class CBullets : public CGameObject
{
	/*�����Ѿ� : 0, ���Ѿ� : 1 */
	int type;
public:
	void setType(int tType) { type = tType; }
	void Draw(HDC hdc, HBITMAP hBitmap, HBITMAP oldbit);


public:
	CBullets(IBULLET iBullet);
	CBullets();
	~CBullets();
};

