#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "Define.h"
#include "Player.h"


//#include "Player.h"

#define SERVERPORT 9000
#define BUFSIZE    512


INFO position;
//CObjects* pObj;
//CPlayer* pPlayer;
KEYDATA keyData;
SOCKET client_sock[2];

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

// ¼ÒÄÏ ÇÔ¼ö ¿À·ù Ãâ·Â
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

//Ä¿¹Ô¿£ Çª½ÃÇª½Ã

DWORD WINAPI RecvThread(LPVOID clientNum)
{
	printf("Tread Running\n");
	int n = (int)clientNum;
	int addrlen;
	int retval;
	char buf[5];
	SOCKADDR_IN clientaddr;
	CPlayer* pPlayer = new CPlayer;

	pPlayer->SetKeyData(keyData);
	pPlayer->SetInfo(position);


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
		

		if (buf[0])for (int i = 0; i < 5; ++i)
		{
			//pObj->GetKeyData().key[i];
			keyData.key[i] = buf[i];
		}
		pPlayer->Update();

		/*if (buf[0])			position.posY -= 5;
		if (buf[1])
			position.posY += 5;
		if (buf[2])
			position.posX -= 5;
		if (buf[3])
			position.posX += 5;*/
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
	//CObjects::CObjects();
	int retval;
	WSADATA wsa;
	int clientSize = 0;
	if(WSAStartup(MAKEWORD(2, 2), &wsa)!=0)
		return 1;
	for (int i = 0; i < 5; ++i)
	{
		//pObj->GetKeyData().key[i] = false;
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