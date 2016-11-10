// ShootingStrike.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "ShootingStrike.h"
#include "Network.h"
#include "structType.h"

#define MAX_LOADSTRING 120

void DrawBackGround(HDC& memdc, HBITMAP& hBackGround, int& mapY);
void DrawPlane(HDC memdc, int x, int y);

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

const int windowSizeW = 450;
const int windowsizeH = 800;

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
		0, 0, 450, 800, NULL, NULL, hInstance, NULL);
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
	//static bool key[4];
    switch (message)
    {
	case WM_CREATE:
		sock = InitSocket(0);
		ConnectToServer(sock);
		
		mapY = 0;
		hBackGround = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		SetTimer(hWnd, 0, 10, NULL);
		CreateThread(NULL, 0, RecvThread, (LPVOID)&RECVPACKET(sock, pPos) , 0, NULL);
		

		px = 200;
		py = 600;
			break;
    
    case WM_PAINT:
        {
			RECT rt;
			GetClientRect(hWnd, &rt);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			HDC memdc = CreateCompatibleDC(hdc);
			HBITMAP oldbit, hbit = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
			oldbit = (HBITMAP)SelectObject(memdc, hbit);
            // TODO: ���⿡ memdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.

			// ��� �׸���
			DrawBackGround(memdc, hBackGround, mapY);

			DrawPlane(memdc, px, py);
			//����

			// -- �������
			BitBlt(hdc, 0, 0, rt.right, rt.bottom, memdc, 0, 0, SRCCOPY);
			SelectObject(memdc, oldbit);
			DeleteObject(memdc);
			DeleteObject(hbit);
			DeleteObject(oldbit);
            EndPaint(hWnd, &ps);
			//DeleteObject(hdc);
        }
        break;
	case WM_TIMER:
		switch (wParam)
		{
		case 0 :
			mapY -= 5;

			/*if (key[0])
				py -= 2;
			if (key[1])
				py += 2;
			if (key[2])
				px -= 2;
			if (key[3])
				px += 2;*/

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
		}
		CreateThread(NULL, 0, SendThread, (LPVOID)&SENDPACKET(sock, key), 0, NULL);

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
		}
		CreateThread(NULL, 0, SendThread, (LPVOID)&SENDPACKET(sock, key), 0, NULL);


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




void DrawBackGround(HDC& memdc, HBITMAP& hBackGround, int& mapY)
{
	HDC memdc2 = CreateCompatibleDC(memdc);
	HBITMAP oldbit2 = (HBITMAP)SelectObject(memdc2, hBackGround);

	if (mapY < 0)
	{
		StretchBlt(memdc, 0, 0, windowSizeW, windowsizeH , memdc2, 0, 8030+ mapY, 900, 800, SRCCOPY);
		if (mapY < -800)
			mapY = 7230;
	}

	StretchBlt(memdc, 0, 0, windowSizeW, windowsizeH, memdc2, 0, mapY, 900, 800, SRCCOPY);
	SelectObject(memdc2, oldbit2);
	
	
	

	DeleteObject(memdc2);
	DeleteObject(oldbit2);
}

void DrawPlane(HDC memdc, int x, int y)
{
	HDC memdc2 = CreateCompatibleDC(memdc);
	
	//���� ����� �׽�Ʈ�� �׽�Ʈ �Ϸ��� �� �Լ����� ���� ����
	HBITMAP plane = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PLANE));
	HBITMAP oldbit2 = (HBITMAP)SelectObject(memdc2, plane);

	//TransparentBlt()
	TransparentBlt(memdc, pPos.posX, pPos.posY, 50, 50, memdc2, 100, 0, 24, 33, RGB(255, 255, 255));
	SelectObject(memdc2, oldbit2);
	
	DeleteObject(memdc2);
	DeleteObject(oldbit2);
	DeleteObject(plane);

}






