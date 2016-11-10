#pragma once
#include "stdafx.h"

// 소켓 함수 오류 출력 후 종료
void err_quit(char *msg);

// 소켓 함수 오류 출력
void err_display(char *msg);

SOCKET InitSocket(int retval);
void ConnectToServer(SOCKET sock);
void CloseSocket(SOCKET sock);


DWORD WINAPI RecvThread(LPVOID parameter);
DWORD WINAPI SendThread(LPVOID parameter);
