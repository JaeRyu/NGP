#pragma once
#include"stdafx.h"
#include"Network.h"

DWORD SERVERIP;

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
	DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(SERVERIP);
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
	RECVPACKET sp = *(RECVPACKET *)parameter;
	CClientManager *Manager = sp.Manager;
	HANDLE hEvent = sp.hEvent;
	int retval;
	INFO buf;
	int len;
	while (1) {
		
		WaitForSingleObject(hEvent,INFINITE);
		// 데이터 받기

		//플레이어 수신
		int playersize = 0;

		retval = recv(sp.sock, (char*)&playersize, sizeof(int), 0);
		Manager->vPlane.clear();
		for (int i = 0; i < playersize; ++i)
		{
			retval = recv(sp.sock, (char *)&buf, sizeof(INFO), 0);
			if (retval == SOCKET_ERROR) {
				err_quit("recv()");
				break;
			}
			else if (retval == 0)
				break;

			CPlane cp;
			cp.SetInfo(buf);
			Manager->vPlane.push_back(cp);
		}
		

		//적 수신
		int Enemysize = 0;
		retval = recv(sp.sock, (char*)&Enemysize, sizeof(int), 0);
		Manager->vEnemy.clear();
		OBJECTINFO eBuf;
		for (int i = 0; i < Enemysize; ++i)
		{

			retval = recv(sp.sock, (char *)&eBuf, sizeof(OBJECTINFO), 0);
			Manager->vEnemy.push_back(CEnemy(eBuf));
			if (retval == SOCKET_ERROR) {
				err_quit("recv()");
				break;
			}
			else if (retval == 0)
				break;
		}

		

		//총알 수신
		int bulletsize;
		retval = recv(sp.sock, (char * )&bulletsize, sizeof(int),0);
	
		Manager->vBullet.clear();
		for (int i = 0; i < bulletsize; ++i)
		{
			IBULLET buf;
			retval = recv(sp.sock, (char*)&buf, sizeof(IBULLET), 0);
			Manager->vBullet.push_back(CBullets(buf));
		}

		// 맵좌표 수신
		int mapY;
		retval = recv(sp.sock, (char *)&mapY, sizeof(int), 0);
		Manager->m_MapY = mapY;


		SetEvent(hEvent);

	}
	return 0;
}
DWORD WINAPI SendThread(LPVOID parameter)
{
	SENDPACKET sp = *(SENDPACKET*)parameter;

	int retval = send(sp.sock, (char*)&sp.key, sizeof(sp.key), 0);

	if (retval == SOCKET_ERROR) {
		err_quit("send()");
	}

	delete parameter;
	return 0;
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			SendMessage(GetDlgItem(hDlg, IDC_IPADDRESS1), IPM_GETADDRESS, 0, (LPARAM)&SERVERIP);
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
