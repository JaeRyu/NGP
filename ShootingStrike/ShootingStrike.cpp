// ShootingStrike.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "ShootingStrike.h"
#include"mThread.h"

#define MAX_LOADSTRING 120

void DrawBackGround(HDC& memdc, HBITMAP& hBackGround, int& mapY);
void DrawPlane(HDC memdc, int x, int y);

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

const int windowSizeW = 450;
const int windowsizeH = 800;
bool key[5];
INFO pPos;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI RecvThread(LPVOID parameter);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SHOOTINGSTRIKE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SHOOTINGSTRIKE));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHOOTINGSTRIKE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SHOOTINGSTRIKE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, windowSizeW, windowsizeH, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
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
	//static bool key[4];
    switch (message)
    {
	case WM_CREATE:
		mapY = 0;
		hBackGround = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		SetTimer(hWnd, 0, 10, NULL);
		CreateThread(NULL, 0, RecvThread,NULL, 0, NULL);
		px = 200;
		py = 600;
			break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
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
	}
	break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
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






DWORD WINAPI RecvThread(LPVOID parameter)
{
	int retval;
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(9000);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");
	int len;
	while (1) {
		

		// ������ ������
		retval = send(sock, (char*)&key, sizeof(key), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}
		//printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval);

		// ������ �ޱ�
		retval = recv(sock, (char *)&pPos, sizeof(pPos), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;
	}
	closesocket(sock);

	WSACleanup();
	return 0;
}