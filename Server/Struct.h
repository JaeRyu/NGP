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

// Ŭ���̾�Ʈ�� �Ѿ��� ������ ����
typedef struct BULLETINFO {
	BYTE type;
	INFO info;
}IBULLET;