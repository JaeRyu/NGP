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

KEYDATA keyData;
SOCKET client_sock[2];
CPlayer m_Player[2];
HANDLE hThread;	//키값을 전달 받는 스레드의 이벤트

HANDLE hUpdateHandle; //업데이트 스레드에서 객체들 정보를 받아오자.
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

DWORD WINAPI SendThread(LPVOID parameter)
{
	int retval;
	


	return 0;
}

DWORD WINAPI RecvThread(LPVOID clientNum)	//키값 받는 스레드
{
	//printf("키값 전달 ㅇㅋ\n");
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
			keyData.key[i] = buf[i];		//업 0, 다운 1, 레프트 2 , 라이트 3, 스페이스 4
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

	while (1)
	{
		//update()들 돌리는 연산을 해주자.
		if (keyData.clientNum != -1)
		{
			m_Manager.update(keyData);
			for(int i = 0; i<5; ++i)
				keyData.key[i] = false;
			keyData.clientNum = -1;

			SetEvent(hUpdateHandle);
		}
		
		
		
		if (GetTickCount() - updateSTime > 20)
		{
			if (keyData.clientNum == -1)
			{
				KEYDATA tempKey;
				tempKey.clientNum = -1;
				for (int i = 0; i < 5; ++i)
					tempKey.key[i] = false;


				m_Manager.update(tempKey);
			}
			updateSTime = GetTickCount();
		}


		if (GetTickCount() - stime > 30)
		{
			
			// 플레이어 전송 부분
			std::vector<CPlayer> vPlayer = m_Manager.GetPlayers();
			int playerSize = vPlayer.size();

			//플레이어 숫자 전송
			retval = send(client_sock[0], (char *)&playerSize, sizeof(int), 0);
			retval = send(client_sock[1], (char *)&playerSize, sizeof(int), 0);

			//플레이어 좌표 전송
			for (int i = 0; i < vPlayer.size(); ++i)
			{
				tInfo = vPlayer[i].GetInfo();
				retval = send(client_sock[0], (char*)&tInfo, sizeof(INFO), 0);
				retval = send(client_sock[1], (char*)&tInfo, sizeof(INFO), 0);
			}


			//적 전송부분
			std::list<CEnemy> LEnemy = m_Manager.GetMonster();
			int MonsterSize = LEnemy.size();
			retval = send(client_sock[0], (char *)&MonsterSize, sizeof(int), 0);
			retval = send(client_sock[1], (char *)&MonsterSize, sizeof(int), 0);

			//printf("MonsterSize : %d", MonsterSize);
			//적 좌표 전송부분
			std::list<CEnemy>::iterator iter;
			for (iter = LEnemy.begin(); iter != LEnemy.end(); iter++)
			{
				retval = send(client_sock[0], (char *)&iter->GetPos(), sizeof(EnemyInfo), 0);
				retval = send(client_sock[1], (char *)&iter->GetPos(), sizeof(EnemyInfo), 0);
			}

			
			//총알정보 전송 부분
			std::list<CBullet> vBullet = m_Manager.GetBulletsLIst();
			int bulletSize = vBullet.size();
			//printf("bulletSize = %d\n", bulletSize);


			//총알 숫자 전송
			retval = send(client_sock[0], (char *)&bulletSize, sizeof(int), 0);
			retval = send(client_sock[1], (char *)&bulletSize, sizeof(int), 0);

			//총알 좌표 전송
			std::list<CBullet>::iterator itor;
			for (itor = vBullet.begin(); itor != vBullet.end(); itor++)
			{
				retval = send(client_sock[0], (char *)&itor->GetBulletInfo(), sizeof(IBULLET), 0);
				retval = send(client_sock[1], (char *)&itor->GetBulletInfo(), sizeof(IBULLET), 0);

			}

			//점수전송
			int tScore = m_Manager.GetClientScore(0);
			retval = send(client_sock[0], (char *)&tScore, sizeof(int), 0);
			tScore = m_Manager.GetClientScore(1);;
			retval = send(client_sock[1], (char *)&tScore, sizeof(int), 0);


			//맵좌표 전송

			mapY -= 5;
			if (mapY < -800)
				mapY = 7230;

			retval = send(client_sock[0], (char *)&mapY, sizeof(int), 0);
			retval = send(client_sock[1], (char *)&mapY, sizeof(int), 0);

			stime = GetTickCount();


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


	// 업데이트 스레드 생성


	//이벤트 생성
	hUpdateHandle = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (hUpdateHandle == NULL)
		return 1;

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock[clientSize] = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);


		hThread = CreateThread(NULL, 0, RecvThread, (LPVOID)clientSize, 0, NULL);
		if (hThread == NULL)
			printf("리시브 스레드 생성 실패");
		
		m_Manager.AddPlayer();
		clientSize++;

		bool start = true;
		if (clientSize > 1 && start)
		{
			hThread = CreateThread(NULL, 0, UpdateThread, (LPVOID)clientSize, 0, NULL);
			if (hThread == NULL)
				printf("업데이트 스레드 생성 실패");
			start = false;
		}

	}

	closesocket(listen_sock);

	WSACleanup();
}