#pragma once

#include"userInclude.h"

class CBullets : public CGameObject
{
	/*À¯ÀúÃÑ¾Ë : 0, ÀûÃÑ¾Ë : 1 */
	int type;
public:
	void setType(int tType) { type = tType; }
	void Draw(HDC hdc, HBITMAP hBitmap, HBITMAP oldbit);


public:
	CBullets(IBULLET iBullet);
	CBullets();
	~CBullets();
};

