#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "Define.h"
#include "Player.h"
#include "ServerManager.h"

//#include "Player.h"

#define SERVERPORT 9000
#define BUFSIZE    512


INFO tInfo;
bool sendEvent;
KEYDATA keyData;
SOCKET client_sock[2];
CPlayer m_Player[2];
HANDLE hThread;	//Ű���� ���� �޴� �������� �̺�Ʈ

HANDLE hUpdateHandle; //������Ʈ �����忡�� ��ü�� ������ �޾ƿ���.
CServerManager m_Manager;

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

DWORD WINAPI SendThread(LPVOID parameter)
{
	CServerManager sManager = m_Manager;
	int retval;
	sendEvent = true;

	//���� ���� ����
	int GameState = 1;

	retval = send(client_sock[0], (char *)&GameState, sizeof(int), 0);
	retval = send(client_sock[1], (char *)&GameState, sizeof(int), 0);

	// �÷��̾� ���� �κ�
	std::vector<CPlayer> vPlayer = sManager.GetPlayers();
	int playerSize = vPlayer.size();

	//�÷��̾� ���� ����
	retval = send(client_sock[0], (char *)&playerSize, sizeof(int), 0);
	retval = send(client_sock[1], (char *)&playerSize, sizeof(int), 0);

	//�÷��̾� ��ǥ ����
	for (int i = 0; i < vPlayer.size(); ++i)
	{
		tInfo = vPlayer[i].GetInfo();
		retval = send(client_sock[0], (char*)&tInfo, sizeof(INFO), 0);
		retval = send(client_sock[1], (char*)&tInfo, sizeof(INFO), 0);
	}


	//�� ���ۺκ�
	std::list<CEnemy> LEnemy = sManager.GetMonster();
	int MonsterSize = LEnemy.size();
	//printf("MonsterSize = %d \d", MonsterSize);
	retval = send(client_sock[0], (char *)&MonsterSize, sizeof(int), 0);
	retval = send(client_sock[1], (char *)&MonsterSize, sizeof(int), 0);

	//printf("MonsterSize : %d", MonsterSize);
	//�� ��ǥ ���ۺκ�
	std::list<CEnemy>::iterator iter;
	for (iter = LEnemy.begin(); iter != LEnemy.end(); iter++)
	{
		retval = send(client_sock[0], (char *)&iter->GetPos(), sizeof(EnemyInfo), 0);
		retval = send(client_sock[1], (char *)&iter->GetPos(), sizeof(EnemyInfo), 0);
	}
	m_Manager.EnemyZeroTo(2);


	//�Ѿ����� ���� �κ�
	std::list<CBullet> vBullet = sManager.GetBulletsLIst();
	int bulletSize = vBullet.size();
	//printf("bulletSize = %d\n", bulletSize);


	//�Ѿ� ���� ����
	retval = send(client_sock[0], (char *)&bulletSize, sizeof(int), 0);
	retval = send(client_sock[1], (char *)&bulletSize, sizeof(int), 0);

	//�Ѿ� ��ǥ ����
	std::list<CBullet>::iterator itor;
	for (itor = vBullet.begin(); itor != vBullet.end(); itor++)
	{
		retval = send(client_sock[0], (char *)&itor->GetBulletInfo(), sizeof(IBULLET), 0);
		retval = send(client_sock[1], (char *)&itor->GetBulletInfo(), sizeof(IBULLET), 0);
	}

	//��������
	int tScore = sManager.GetClientScore(0);
	retval = send(client_sock[0], (char *)&tScore, sizeof(int), 0);
	tScore = sManager.GetClientScore(1);;
	retval = send(client_sock[1], (char *)&tScore, sizeof(int), 0);


	//����ǥ ����
	int mapY = *(int *)parameter;

	retval = send(client_sock[0], (char *)&mapY, sizeof(int), 0);
	retval = send(client_sock[1], (char *)&mapY, sizeof(int), 0);
	sendEvent = false;
	return 0;
}

DWORD WINAPI RecvThread(LPVOID clientNum)	//Ű�� �޴� ������
{
	//printf("Ű�� ���� ����\n");
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


		WaitForSingleObject(hUpdateHandle, INFINITE);

		keyData.clientNum = n;

		for (int i = 0; i < 5; ++i)
		{
			keyData.key[i] = buf[i];		//�� 0, �ٿ� 1, ����Ʈ 2 , ����Ʈ 3, �����̽� 4
		}

	}
	return 0;
}

DWORD WINAPI UpdateThread(LPVOID clientNum)
{

	int n = (int)clientNum;
	int addrlen;
	int retval;
	char buf;
	int mapY = 0;
	SOCKADDR clientaddr;

	addrlen = sizeof(clientaddr);
	ZeroMemory(keyData.key, sizeof(INFO));

	DWORD stime = GetTickCount();
	
	DWORD updateSTime = GetTickCount();
	m_Manager.SetPlayTime();
	while (1)
	{
		//�÷��̾� ������Ʈ
		if (keyData.clientNum != -1)
		{
			m_Manager.SetKeyData(keyData);
			//m_Manager.UpdatePlayer(keyData);
			for(int i = 0; i<5; ++i)
				keyData.key[i] = false;
			keyData.clientNum = -1;
			SetEvent(hUpdateHandle);
		}
		
		//������Ʈ ������Ʈ
		if (GetTickCount() - updateSTime > 10)
		{
			m_Manager.Update();
			mapY -= 1;
			if (mapY < -800)
				mapY = 7230;
			updateSTime = GetTickCount();
		}

		//Send ȣ��
		if (GetTickCount() - stime > 40 && sendEvent==false)
		{
			CreateThread(NULL, 0, SendThread, (LPVOID)&mapY, 0, NULL);
		
			stime = GetTickCount();
		}
	}

	return 0;
}

DWORD WINAPI AcceptThread(LPVOID parameter)
{
	int retval;
	int addrlen;
	int clientSize = 0;
	SOCKADDR_IN clientaddr;
	SOCKET sock = (SOCKET)parameter;

	bool start = true;


	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		
		client_sock[clientSize] = accept(sock, (SOCKADDR *)&clientaddr, &addrlen);
		
		int anp = 1;
		setsockopt(client_sock[clientSize], IPPROTO_TCP, TCP_NODELAY, (char*)&anp, sizeof(int));
		
		printf("%s ����\n", inet_ntoa(clientaddr.sin_addr));
		
		hThread = CreateThread(NULL, 0, RecvThread, (LPVOID)clientSize, 0, NULL);
		if (hThread == NULL)
			printf("���ú� ������ ���� ����");

		m_Manager.AddPlayer();
		clientSize++;

		if (clientSize > 1 && start)
		{
			printf("Update Thread Start\n");
			hThread = CreateThread(NULL, 0, UpdateThread, (LPVOID)clientSize, 0, NULL);
			if (hThread == NULL)
				printf("������Ʈ ������ ���� ����");
			start = false;
		}

	}


	return 0;
}

int main()
{
	//CObjects::CObjects();
	int retval;
	WSADATA wsa;
	int clientSize = 0;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	keyData.clientNum = -1;
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


	// ������Ʈ ������ ����


	//�̺�Ʈ ����
	hUpdateHandle = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (hUpdateHandle == NULL)
		return 1;
	
	bool start;
	HANDLE HuThread = CreateThread(NULL, 0, AcceptThread, (LPVOID)listen_sock, 0, NULL);
	WaitForSingleObject(HuThread, INFINITE);

	//while (1) {
	//	// accept()
	//	addrlen = sizeof(clientaddr);
	//	client_sock[clientSize] = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
	//	int anp = 1;
	//	setsockopt(client_sock[clientSize], IPPROTO_TCP, TCP_NODELAY, (char*)&anp, sizeof(int));
	//	printf("%s ����\n", inet_ntoa(clientaddr.sin_addr));
	//	hThread = CreateThread(NULL, 0, RecvThread, (LPVOID)clientSize, 0, NULL);
	//	if (hThread == NULL)
	//		printf("���ú� ������ ���� ����");
	//	
	//	m_Manager.AddPlayer();
	//	clientSize++;


	//	if (clientSize > 1 && start)
	//	{
	//		printf("Update Thread Start\n");
	//		hThread = CreateThread(NULL, 0, UpdateThread, (LPVOID)clientSize, 0, NULL);
	//		if (hThread == NULL)
	//			printf("������Ʈ ������ ���� ����");
	//		start = false;
	//	}

	//}

	closesocket(listen_sock);

	WSACleanup();
}