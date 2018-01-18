#include "stdafx.h"
#include "cCamera.h"

cCamera::cCamera()
	: m_vEye(0.F, 0.F, 0.F)
	, m_vLookAt(0.F, 0.F, 0.F)
	, m_vUp(0.F, 0.F, 0.F)
	, m_ptPrevMouse()
	, m_fCamRotX(0.F)
	, m_fCamRotY(0.F)
	, m_bIsLButtonDown(false)
	, m_fCamDistance(0.F)
{
}

cCamera::~cCamera()
{
}

void cCamera::Setup()
{
	// ----------------------------------------------------------------------------------------------------
	m_fCamDistance						= 15.5F;
	m_vEye								= D3DXVECTOR3(0.F, m_fCamDistance, -m_fCamDistance);
	m_vUp								= D3DXVECTOR3(0.F, 1.F, 0.F);
	// ----------------------------------------------------------------------------------------------------

	this->CreateMatProj();
}

void cCamera::Release()
{
}

void cCamera::Update()
{
	this->ControlCamDistance();
	this->ControlCamRotation();

	this->CreateMatView();
}

void cCamera::CreateMatView()
{
	D3DXMATRIXA16 matView;

	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	D_DEVICE->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::CreateMatProj()
{
	D3DXMATRIXA16 matProj;

	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 3.F, 
		(FLOAT)D_WINSIZEX / (FLOAT)D_WINSIZEY, 1.F, 1000.F);
	D_DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::ControlCamDistance()
{
	m_fCamDistance -= g_fWheelDelta;

	if (m_fCamDistance < 10.F)
	{
		m_fCamDistance = 10.F;
	}
	else if (m_fCamDistance > 30.F)
	{
		m_fCamDistance = 30.F;
	}

	m_vEye = D3DXVECTOR3(0.F, m_fCamDistance, -m_fCamDistance);
	g_fWheelDelta = 0.F;
}

void cCamera::ControlCamRotation()
{
	if (D_KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		m_bIsLButtonDown = true;
		m_ptPrevMouse.x = g_ptMouse.x;
		m_ptPrevMouse.y = g_ptMouse.y;
	}
	else if (D_KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
	{
		m_bIsLButtonDown = false;
	}

	if (m_bIsLButtonDown)
	{
		float fDeltaX = (float)g_ptMouse.x - (float)m_ptPrevMouse.x;
		float fDeltaY = (float)g_ptMouse.y - (float)m_ptPrevMouse.y;

		m_fCamRotX += fDeltaY / 500.F;
		m_fCamRotY += fDeltaX / 500.F;

		m_ptPrevMouse.x = g_ptMouse.x;
		m_ptPrevMouse.y = g_ptMouse.y;
	}

	D3DXMATRIXA16 matRX, matRY, matR;

	D3DXMatrixRotationX(&matRX, m_fCamRotX);
	D3DXMatrixRotationY(&matRY, m_fCamRotY);

	matR = matRX * matRY;
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);
}
