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

// Ŭ���̾�Ʈ�� �Ѿ��� ������ ����
typedef struct ObjectInfo {
	WORD type;
	INFO info;
}IBULLET, EnemyInfo;
//typedef struct ENEMYINFO {
//	BYTE type;
//	INFO info;
//};