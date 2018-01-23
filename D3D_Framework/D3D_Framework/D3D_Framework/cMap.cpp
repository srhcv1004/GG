#include "stdafx.h"
#include "cMap.h"
#include "cCamera.h"
#include "cXPlayer.h"

cMap::cMap()
	: m_pCamera(NULL)
	, m_pPlayer(NULL)
{
}

cMap::~cMap()
{
}

void cMap::Setup()
{
	this->SetLight();
}

void cMap::Release()
{
	D_SAFE_DELETE(m_pCamera);

	D_SAFE_RELEASE(m_pPlayer);
	D_SAFE_DELETE(m_pPlayer);
}

void cMap::Update()
{
}

void cMap::Render()
{
	D_DEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void cMap::SetLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type						= D3DLIGHT_POINT;
	stLight.Ambient						= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse						= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular					= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	stLight.Position					= D3DXVECTOR3(0.F, 2.F, 0.F);
	stLight.Range						= 50.F;

	D_DEVICE->SetLight(0, &stLight);
	D_DEVICE->LightEnable(0, TRUE);
}
