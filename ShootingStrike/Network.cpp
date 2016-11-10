#pragma once

#include "stdafx.h"
#include "Network.h"
#include "structType.h"



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


void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}



SOCKET InitSocket(int retval)
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");


	return sock;
}

void ConnectToServer(SOCKET sock)
{
	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(9000);
	int retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");
}

void CloseSocket(SOCKET sock)
{
	closesocket(sock);
	WSACleanup();
}


DWORD WINAPI RecvThread(LPVOID parameter)
{
	RECVPACKET sp = (RECVPACKET&)parameter;

	int retval;

	int len;
	while (1) {
		
		// 데이터 받기
		retval = recv(sp.sock, (char *)&sp.iPos, sizeof(sp.iPos), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;
	}
	return 0;
}
DWORD WINAPI SendThread(LPVOID parameter)
{
	SENDPACKET sp = (SENDPACKET&)parameter;

	int retval = send(sp.sock, (char*)&sp.key, sizeof(sp.key), 0);

	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}
	return 0;
}
