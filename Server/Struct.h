#pragma once
typedef struct tagInfo {
	short posX;
	short posY;
	BYTE state;
}INFO;

typedef struct KEY {
	int clientNum;
	bool key[5];
}KEYDATA;

// 클라이언트에 총알을 전송할 구좇
typedef struct ObjectInfo {
	WORD type;
	INFO info;
}IBULLET, EnemyInfo;
//typedef struct ENEMYINFO {
//	BYTE type;
//	INFO info;
//};