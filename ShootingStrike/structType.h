#pragma once
#include"userInclude.h"


// ������Ʈ ���� ����ü
typedef struct INFO{
	short posX;
	short posY;
	BYTE state;
}INFO;

typedef struct BULLETINFO {
	BYTE type;
	INFO info;
}IBULLET;