#pragma once
#include"userInclude.h"


// ������Ʈ ���� ����ü
typedef struct INFO{
	WORD posX;
	WORD posY;
	BYTE state;
}INFO;

typedef struct BULLETINFO {
	BYTE type;
	INFO info;
}IBULLET;