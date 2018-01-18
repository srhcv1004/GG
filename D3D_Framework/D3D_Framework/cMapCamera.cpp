#include "stdafx.h"
#include "cMapCamera.h"


cMapCamera::cMapCamera()
{
}


cMapCamera::~cMapCamera()
{
}

void cMapCamera::CreateMatView()
{
	cCamera::CreateMatView();
}

void cMapCamera::CreateMatProj()
{
	cCamera::CreateMatProj();
}

void cMapCamera::ControlCamDistance()
{
	cCamera::ControlCamDistance();
}

void cMapCamera::ControlCamRotation()
{
	cCamera::ControlCamRotation();
}

void cMapCamera::Setup()
{
	// ----------------------------------------------------------------------------------------------------
	m_fCamDistance = 15.5F;
	m_vEye = D3DXVECTOR3(0.F, m_fCamDistance, -m_fCamDistance);
	m_vUp = D3DXVECTOR3(0.F, 1.F, 0.F);
	// ----------------------------------------------------------------------------------------------------

	this->CreateMatProj();
}

void cMapCamera::Update()
{
	this->ControlCamDistance();
	this->ControlCamRotation();

	this->CreateMatView();
}

void cMapCamera::ControlCamPosition()
{
	if (D_KEYMANAGER->IsStayKeyDown('W'))
	{

	}
}
