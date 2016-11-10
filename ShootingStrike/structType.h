#pragma once
#include "stdafx.h"

// 오브젝트 공통 구조체
typedef struct {
	WORD posX;
	WORD posY;
	BYTE state;
}INFO;

//SendThread의 인자로 전달할 구조체
typedef struct SENDPACKET {
	SOCKET sock;
	bool key[5];

	SENDPACKET(SOCKET s, bool k[5]) { sock = s; memcpy(key, k, sizeof(k)); };
}SENDPACKET;

typedef struct RECVPACKET {
	SOCKET sock;
	INFO iPos;

	RECVPACKET(SOCKET s, INFO &p) { sock = s;  iPos = p; };

}RECVPACKET;