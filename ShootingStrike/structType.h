#pragma once
#include "stdafx.h"

// ������Ʈ ���� ����ü
typedef struct {
	WORD posX;
	WORD posY;
	BYTE state;
}INFO;

//SendThread�� ���ڷ� ������ ����ü
typedef struct {
	SOCKET sock;
	bool key[5];
}SENDPACKET;