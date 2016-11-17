#pragma once
#include"userInclude.h"

//SendThread�� ���ڷ� ������ ����ü
struct SENDPACKET {
	SOCKET sock;
	bool key[5];

	SENDPACKET(SOCKET& s, bool k[5]) { sock = s; for (int i = 0; i < 5; ++i) key[i] = k[i]; }
};

struct RECVPACKET {
	SOCKET sock;
	CClientManager *Manager;

	RECVPACKET(SOCKET& s, CClientManager *p) { sock = s;  Manager = p; }
};



// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg);

// ���� �Լ� ���� ���
void err_display(char *msg);

SOCKET InitSocket(int retval);
void ConnectToServer(SOCKET sock);
void CloseSocket(SOCKET sock);




DWORD WINAPI RecvThread(LPVOID parameter);
DWORD WINAPI SendThread(LPVOID parameter);
