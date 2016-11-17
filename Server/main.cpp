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
HANDLE hThread;	//Ű���� ���� �޴� �������� �̺�Ʈ

HANDLE hUpdateHandle; //������Ʈ �����忡�� ��ü�� ������ �޾ƿ���.


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

// ���� �Լ� ���� ���
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

//Ŀ�Կ� Ǫ��Ǫ��

DWORD WINAPI RecvThread(LPVOID clientNum)	//Ű�� �޴� ������
{
	printf("Ű�� ���� ����\n");
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
			keyData.key[i] = buf[i];		//�� 0, �ٿ� 1, ����Ʈ 2 , ����Ʈ 3, �����̽� 4
			printf("Ű[%d] : %d\n", i, keyData.key[i] );
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
		//update()�� ������ ������ ������.
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
			
			printf("Ŭ���̾�Ʈ �ѹ� : %d\n", keyData.clientNum);
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
	//HANDLE recvnThread;		//������Ʈ �����忡�� ��ü�� ������ �޾ƿ���.

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
			printf("���ú� ������ ���� ����");
		CreateThread(NULL, 0, UpdateThread, (LPVOID)clientSize, 0, NULL); //Ŭ���� ��ü ������ �޾ƿ���
		if (hThread == NULL)
			printf("������Ʈ ������ ���� ����");
	}

	closesocket(listen_sock);

	WSACleanup();
}