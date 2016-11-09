#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "Objects.h"

#define SERVERPORT 9000
#define BUFSIZE    512

typedef struct {
	int clientNum;
	bool key[5];
}KEYDATA;

void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

KEYDATA keyData;
SOCKET client_sock[2];


DWORD WINAPI RecvThread(LPVOID clientNum)
{
	printf("Tread Running\n");
	int n = (int)clientNum;
	int addrlen;
	int retval;
	SOCKADDR_IN clientaddr;
	char buf[5];
	INFO position;
	position.posX = 200;
	position.posY = 600;

	addrlen = sizeof(clientaddr);
	getpeername(client_sock[n], (SOCKADDR *)&clientaddr, &addrlen);
	while (1)
	{
		retval = recv(client_sock[n], buf, sizeof(buf), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		keyData.key[0] = buf[0];
		if (buf[0])
			position.posY -= 5;
		if (buf[1])
			position.posY += 5;
		if (buf[2])
			position.posX -= 5;
		if (buf[3])
			position.posX += 5;

		Sleep(50);

		retval = send(client_sock[n], (char*)&position, sizeof(INFO), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}
		
	}
	closesocket(client_sock[n]);
	return 0;
}

int main()
{
	int retval;
	WSADATA wsa;
	int clientSize = 0;
	if(WSAStartup(MAKEWORD(2, 2), &wsa)!=0)
		return 1;
	for (int i = 0; i < 5; ++i)
	{
		keyData.key[i] = false;
	}

	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");


	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");


	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock[clientSize] = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		hThread = CreateThread(NULL, 0, RecvThread,
			(LPVOID)clientSize, 0, NULL);
		
	}


	closesocket(listen_sock);
	WSACleanup();
}