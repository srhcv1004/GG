#include "stdafx.h"
#include "D3DMain.h"
#include "cMainGame.h"

HINSTANCE													g_hInstance;
HWND														g_hWnd;
POINT														g_ptMouse;
FLOAT														g_fWheelDelta;

cMainGame*													g_pMainGame;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void SetWindowsSize(int nStartX, int nStartY, int nWidth, int nHeight);

int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPWSTR    lpCmdLine,
                      int       nCmdShow)
{
	g_hInstance = hInstance;

    MSG msg;
	WNDCLASS wc;

	wc.cbClsExtra						= 0;
	wc.cbWndExtra						= 0;
	wc.hbrBackground					= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpfnWndProc						= (WNDPROC)WndProc;
	wc.hInstance						= g_hInstance;
	wc.hIcon							= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor							= LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName						= NULL;
	wc.lpszClassName					= D_WINNAME;
	wc.style							= CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	g_hWnd = CreateWindow(D_WINNAME, D_WINNAME, WS_OVERLAPPEDWINDOW,
		D_WINSTARTX, D_WINSTARTY, D_WINSIZEX, D_WINSIZEY, 
		NULL, (HMENU)NULL, g_hInstance, NULL);

	SetWindowsSize(D_WINSTARTX, D_WINSTARTY, D_WINSIZEX, D_WINSIZEY);
	ShowWindow(g_hWnd, nCmdShow);

	g_pMainGame = new cMainGame();
	g_pMainGame->Setup();
	D_TIMEMANAGER->Setup();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			D_TIMEMANAGER->Update(60.F);

			g_pMainGame->Update();
			g_pMainGame->Render();
		}
	}

	D_SAFE_RELEASE(g_pMainGame);
	D_SAFE_DELETE(g_pMainGame);
    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return g_pMainGame->MainProc(hWnd, message, wParam, lParam);
}

void SetWindowsSize(int nStartX, int nStartY, int nWidth, int nHeight)
{
	RECT sRc = { 0, 0, nWidth, nHeight };
	AdjustWindowRect(&sRc, D_WINSTYLE, FALSE);
	SetWindowPos(g_hWnd, NULL, nStartX, nStartY, 
		sRc.right - sRc.left, sRc.bottom - sRc.top, SWP_NOZORDER | SWP_NOMOVE);
}
