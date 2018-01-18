#include "stdafx.h"
#include "cDeviceManager.h"

cDeviceManager::cDeviceManager()
	: m_pD3D(NULL)
	, m_pD3DDevice(NULL)
{
}

cDeviceManager::~cDeviceManager()
{
}

void cDeviceManager::Setup()
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 sD3DCaps;
	ZeroMemory(&sD3DCaps, sizeof(D3DCAPS9));
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &sD3DCaps);

	int nProcessing = 0;
	if (sD3DCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		nProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		nProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS sD3Dpp;
	ZeroMemory(&sD3Dpp, sizeof(D3DPRESENT_PARAMETERS));
	sD3Dpp.AutoDepthStencilFormat		= D3DFMT_D16;
	sD3Dpp.BackBufferFormat				= D3DFMT_UNKNOWN;
	sD3Dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	sD3Dpp.EnableAutoDepthStencil		= TRUE;
	sD3Dpp.Windowed						= TRUE;

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, 
		nProcessing, &sD3Dpp, &m_pD3DDevice);
}

void cDeviceManager::Release()
{
	D_SAFE_RELEASE(m_pD3D);

	int nRefCount = m_pD3DDevice->Release();

#ifdef _DEBUG 
	assert(nRefCount == 0 && "메모리를 모두 해제하시오!");
#endif
}
