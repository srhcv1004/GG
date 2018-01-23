#include "stdafx.h"
#include "cGameNode.h"

cGameNode::cGameNode()
{
}

cGameNode::~cGameNode()
{
}

void cGameNode::Setup()
{
	// ----------------------------------------------------------------------------------------------------
	D_DEVICEMANAGER->Setup();
	// ----------------------------------------------------------------------------------------------------



	// ----------------------------------------------------------------------------------------------------
	D_KEYMANAGER->Setup();

	D_RNDMANAGER->Setup();

	D_SCENEMANAGER->Setup();

	D_TIMEMANAGER->Setup();

	D_SOUNDMANAGER->Setup();

	D_SPRITEMANAGER->Setup();

	D_FONTMANAGER->Setup();

	D_ASELOADMANAGER->Setup();

	D_TEXMTLMANAGER->Setup();

	//D_ITEMMANAGER->Setup();
	// ----------------------------------------------------------------------------------------------------
}

void cGameNode::Release()
{	
	// ----------------------------------------------------------------------------------------------------
	D_KEYMANAGER->Release();
	D_KEYMANAGER->ReleaseSingleton();

	D_RNDMANAGER->Release();
	D_RNDMANAGER->ReleaseSingleton();

	D_SCENEMANAGER->Release();
	D_SCENEMANAGER->ReleaseSingleton();

	D_SCENEMANAGER->Release();
	D_SCENEMANAGER->ReleaseSingleton();

	D_SPRITEMANAGER->Release();
	D_SPRITEMANAGER->ReleaseSingleton();

	D_FONTMANAGER->Release();
	D_FONTMANAGER->ReleaseSingleton();

	D_ASELOADMANAGER->Release();
	D_ASELOADMANAGER->ReleaseSingleton();

	D_TEXMTLMANAGER->Release();
	D_TEXMTLMANAGER->ReleaseSingleton();

	D_ITEMMANAGER->Release();
	D_ITEMMANAGER->ReleaseSingleton();
	// ----------------------------------------------------------------------------------------------------



	// ----------------------------------------------------------------------------------------------------
	D_DEVICEMANAGER->Release();
	D_DEVICEMANAGER->ReleaseSingleton();
	// ----------------------------------------------------------------------------------------------------
}

void cGameNode::Update()
{
	InvalidateRect(g_hWnd, NULL, FALSE);
}

void cGameNode::Render()
{	// ----------------------------------------------------------------------------------------------------
	D_DEVICE->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 125, 0), 1.F, 0);
	// ----------------------------------------------------------------------------------------------------
}

LRESULT cGameNode::MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;

		case WM_MOUSEWHEEL:
		{
			g_fWheelDelta = GET_WHEEL_DELTA_WPARAM(wParam) / 40.F;
		}
		break;

		case WM_MOUSEMOVE:
		{	
			g_ptMouse.x = static_cast<float>LOWORD(lParam);
			g_ptMouse.y = static_cast<float>HIWORD(lParam);
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	return 0;
}
