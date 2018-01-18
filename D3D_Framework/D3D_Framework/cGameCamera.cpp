#include "stdafx.h"
#include "cGameCamera.h"


cGameCamera::cGameCamera()
{
}


cGameCamera::~cGameCamera()
{
}

void cGameCamera::CreateMatView()
{
	cCamera::CreateMatView();
}

void cGameCamera::CreateMatProj()
{
	cCamera::CreateMatProj();
}

void cGameCamera::ControlCamDistance()
{
	cCamera::ControlCamDistance();
}

void cGameCamera::ControlCamRotation()
{
	cCamera::ControlCamRotation();
}

void cGameCamera::Setup()
{
	// ----------------------------------------------------------------------------------------------------
	m_fCamDistance = 15.5F;
	m_vEye = D3DXVECTOR3(0.F, m_fCamDistance, -m_fCamDistance);
	m_vUp = D3DXVECTOR3(0.F, 1.F, 0.F);
	// ----------------------------------------------------------------------------------------------------

	this->CreateMatProj();
}

void cGameCamera::Update()
{
	this->ControlCamDistance();
	this->ControlCamRotation();

	this->CreateMatView();
}
