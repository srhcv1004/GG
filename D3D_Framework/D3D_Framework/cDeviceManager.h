#pragma once
#include "cSingletonBase.h"

class cDeviceManager : public cSingletonBase<cDeviceManager>
{
private:
	IDirect3D9*												m_pD3D;
	IDirect3DDevice9*										m_pD3DDevice;

public:
	cDeviceManager();
	virtual ~cDeviceManager();

	void Setup();
	void Release();

	IDirect3DDevice9* GetDevice() { return m_pD3DDevice; }
};

