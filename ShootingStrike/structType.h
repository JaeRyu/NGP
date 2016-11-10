#pragma once
#include "stdafx.h"

// 오브젝트 공통 구조체
typedef struct {
	WORD posX;
	WORD posY;
	BYTE state;
}INFO;

//SendThread의 인자로 전달할 구조체
typedef struct {
	SOCKET sock;
	bool key[5];
}SENDPACKET;