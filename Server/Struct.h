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
typedef struct BULLETINFO {
	BYTE type;
	INFO info;
}IBULLET;