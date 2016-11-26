#pragma once
#include"userInclude.h"


// 오브젝트 공통 구조체
typedef struct INFO{
	short posX;
	short posY;
	BYTE state;
}INFO;

typedef struct BULLETINFO {
	WORD type;
	INFO info;
}IBULLET, OBJECTINFO;

struct DESTROYED {
	INFO info;
	int animNum;

	void Draw(HDC hdc, HBITMAP hEx, HBITMAP oldbit)
	{
		HDC memdc2 = CreateCompatibleDC(hdc);

		
		
		oldbit = (HBITMAP)SelectObject(memdc2, hEx);

		switch (animNum)
		{
		case 0:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 0, 0, 32, 32, RGB(0, 248, 0));
			break;
		case 1:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 33, 0, 32, 32, RGB(0, 248, 0));
			break;
		case 2:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 66, 0, 32, 32, RGB(0, 248, 0));
			break;
		case 3:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 99, 0, 32, 32, RGB(0, 248, 0));
			break;
		case 4:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 132, 0, 32, 32, RGB(0, 248, 0));
			break;
		case 5:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 165, 0, 32, 32, RGB(0, 248, 0));
			break;
		case 6:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 198, 0, 32, 32, RGB(0, 248, 0));
			break;
		case 7:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 231, 0, 32, 32, RGB(0, 248, 0));
			break;
		case 8:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 264, 0, 32, 32, RGB(0, 248, 0));
			break;
		case 9:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 297, 0, 32, 32, RGB(0, 248, 0));
			break;
		case 10:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 330, 0, 32, 32, RGB(0, 248, 0));
			break;
		case 11:
			TransparentBlt(hdc, info.posX, info.posY, 50, 50, memdc2, 363, 0, 31, 32, RGB(0, 248, 0));
			break;
		}
		//animNum++;

		SelectObject(memdc2, oldbit);

		DeleteObject(memdc2);
		DeleteObject(oldbit);
	}
};

