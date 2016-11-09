#pragma once
typedef struct tagInfo {
	WORD posX;
	WORD posY;
	BYTE state;
}INFO;

typedef struct KEY {
	int clientNum;
	bool key[5];
}KEYDATA;
