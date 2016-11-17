#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "Define.h"
#include "Player.h"


//#include "Player.h"

#define SERVERPORT 9000
#define BUFSIZE    512


INFO tInfo;

KEYDATA keyData;
SOCKET client_sock[2];
CPlayer* pPlayer;
HANDLE hThread;	//키값을 전달 받는 스레드의 이벤트

HANDLE hUpdateHandle; //업데이트 스레드에서 객체들 정보를 받아오자.


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

//커밋엔 푸시푸시

DWORD WINAPI RecvThread(LPVOID clientNum)	//키값 받는 스레드
{
	printf("키값 전달 ㅇㅋ\n");
	int n = (int)clientNum;
	int addrlen;
	int retval;
	bool buf[5];
	SOCKADDR clientaddr;


	addrlen = sizeof(clientaddr);
	getpeername(client_sock[n], (SOCKADDR *)&clientaddr, &addrlen);
	while (1)
	{
		retval = recv(client_sock[n], (char*)buf, sizeof(buf), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		//pPlayer->Update();

		WaitForSingleObject(hUpdateHandle, INFINITE);
		printf("ddd\n");
		keyData.clientNum = 0;

		for (int i = 0; i < 5; ++i)
		{
			keyData.key[i] = buf[i];		//업 0, 다운 1, 레프트 2 , 라이트 3, 스페이스 4
			printf("키[%d] : %d\n", i, keyData.key[i] );
		}

		ResetEvent(hUpdateHandle);
	}
	//WaitForSingleObject(hUpdateHandle, INFINITE);
	
	//closesocket(client_sock[n]);
	return 0;
}

DWORD WINAPI UpdateThread(LPVOID clientNum)
{
	
	int n = (int)clientNum;
	int addrlen;
	int retval;
	char buf;
	SOCKADDR clientaddr;

	addrlen = sizeof(clientaddr);
	ZeroMemory(keyData.key, sizeof(INFO));

	while (1)
	{
		//update()들 돌리는 연산을 해주자.
		//WaitForSingleObject(hUpdateHandle, INFINITE);

		//retval = send(client_sock[n], (char*)buf, sizeof(buf), 0);
		if (keyData.clientNum != -1)
		{
			for (int i = 0; i < 1; ++i)
			{
				buf = tInfo.posX;
				buf = tInfo.posY;
				buf = tInfo.state;
			}
			
			printf("클라이언트 넘버 : %d\n", keyData.clientNum);
			keyData.clientNum = -1;
		}
		SetEvent(hUpdateHandle);
		/*if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;*/

		

		//SetEvent(hUpdateHandle);
	}

	retval = send(client_sock[n], (char*)&tInfo, sizeof(INFO), 0);

	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
	}

	//closesocket(client_sock[n]);

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
	//HANDLE recvnThread;		//업데이트 스레드에서 객체들 정보를 받아오자.

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock[clientSize] = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);

		hUpdateHandle = CreateEvent(NULL, TRUE, TRUE, NULL);
		if (hUpdateHandle == NULL)
			return 1;

		/*hThread = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (hThread == NULL)
			return 1;*/

		hThread = CreateThread(NULL, 0, RecvThread, (LPVOID)clientSize, 0, NULL);
		if (hThread == NULL)
			printf("리시브 스레드 생성 실패");
		CreateThread(NULL, 0, UpdateThread, (LPVOID)clientSize, 0, NULL); //클라의 객체 정보를 받아오자
		if (hThread == NULL)
			printf("업데이트 스레드 생성 실패");
	}

	closesocket(listen_sock);

	WSACleanup();
}