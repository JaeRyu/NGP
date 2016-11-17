#pragma once
#include"userInclude.h"

//SendThread의 인자로 전달할 구조체
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



// 소켓 함수 오류 출력 후 종료
void err_quit(char *msg);

// 소켓 함수 오류 출력
void err_display(char *msg);

SOCKET InitSocket(int retval);
void ConnectToServer(SOCKET sock);
void CloseSocket(SOCKET sock);




DWORD WINAPI RecvThread(LPVOID parameter);
DWORD WINAPI SendThread(LPVOID parameter);
