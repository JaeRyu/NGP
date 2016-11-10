#pragma once
#include "stdafx.h"

// ������Ʈ ���� ����ü
typedef struct {
	WORD posX;
	WORD posY;
	BYTE state;
}INFO;

//SendThread�� ���ڷ� ������ ����ü
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