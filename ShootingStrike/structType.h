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

