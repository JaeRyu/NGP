// ShootingStrike.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//
#include"stdafx.h"
#include"ShootingStrike.h"
#include "userInclude.h"
#define MAX_LOADSTRING 120

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.


INFO pPos;


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;

	// ������ Ŭ���� ���
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "MyWndClass";
	if (!RegisterClass(&wndclass)) return 1;

	// ������ ����
	HWND hWnd = CreateWindow("MyWndClass", "ShootingStrike", WS_OVERLAPPEDWINDOW,
		0, 0, windowSizeW, windowsizeH, NULL, NULL, hInstance, NULL);
	if (hWnd == NULL) return 1;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// �޽��� ����
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int mapY;
	static HBITMAP hBackGround;
	static int px, py;
	static SOCKET sock;
	static bool key[5];
	static HANDLE hEvent;
	static CClientManager *pManager;
	static RECVPACKET *packet;
    switch (message)
    {
	case WM_CREATE:
		pManager = new CClientManager;
		pManager->Init(hInst);
		sock = InitSocket(0);
		ConnectToServer(sock);
		
		hEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
		packet = new RECVPACKET(sock, pManager);
		packet->hEvent = hEvent;
		for (int i = 0; i < 5; ++i)
			key[i] = false;

		mapY = 0;
		hBackGround = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		SetTimer(hWnd, 0, 30, NULL);
		SetTimer(hWnd, 1, 50, NULL);
		CreateThread(NULL, 0, RecvThread, (LPVOID)packet, 0, NULL);
			break;
    
    case WM_PAINT:
        {
		WaitForSingleObject(hEvent, INFINITE);
			RECT rt;
			GetClientRect(hWnd, &rt);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			HDC memdc = CreateCompatibleDC(hdc);
			HBITMAP oldbit, hbit = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
			oldbit = (HBITMAP)SelectObject(memdc, hbit);
            // TODO: ���⿡ memdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.

			// ��� �׸���
			pManager->DrawBackground(memdc, mapY);
		
		
			pManager->DrawObejct(memdc);
				
			pManager->DrawScore(memdc);


			// -- �������
			BitBlt(hdc, 0, 0, rt.right, rt.bottom, memdc, 0, 0, SRCCOPY);
			SelectObject(memdc, oldbit);
			DeleteObject(memdc);
			DeleteObject(hbit);
			DeleteObject(oldbit);
            EndPaint(hWnd, &ps);
			SetEvent(hEvent);
        }
        break;
	case WM_TIMER:
		switch (wParam)
		{
		case 0 :
		{
			SENDPACKET *SPacket = new SENDPACKET(sock, key);
			CreateThread(NULL, 0, SendThread, (LPVOID)SPacket, 0, NULL);
			InvalidateRect(hWnd, NULL, false);
		}			
			break;
		case 1:
			pManager->UpdateDummy();
			InvalidateRect(hWnd, NULL, false);
			break;
		}
		break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
			key[0] = true;
			break;
		case VK_DOWN:
			key[1] = true;
			break;
		case VK_LEFT:
			key[2] = true;
			break;
		case VK_RIGHT:
			key[3] = true;
			break;
		case VK_SPACE:
			key[4] = true;
			break;
			
		}

	}
		break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_UP:
			key[0] = false;
			break;
		case VK_DOWN:
			key[1] = false;
			break;
		case VK_LEFT:
			key[2] = false;
			break;
		case VK_RIGHT:
			key[3] = false;
			break;
		case VK_SPACE:
			key[4] = false;
			break;
		}
	

	}
	break;
    case WM_DESTROY:
		CloseSocket(sock);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}







