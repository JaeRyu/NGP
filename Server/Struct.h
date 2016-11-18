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

// 클라이언트에 총알을 전송할 구좇
typedef struct BULLETINFO {
	BYTE type;
	INFO info;
}IBULLET;