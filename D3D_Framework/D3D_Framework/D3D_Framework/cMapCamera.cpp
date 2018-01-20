#include "stdafx.h"
#include "cMapCamera.h"


cMapCamera::cMapCamera()
{
}


cMapCamera::~cMapCamera()
{
}

void cMapCamera::Setup()
{
	cCamera::Setup();
}

void cMapCamera::Update()
{
	cCamera::Update();
	ControlCamPosition();
}

void cMapCamera::ControlCamPosition()
{
	if (D_KEYMANAGER->IsStayKeyDown('W'))
	{
		exit(0);
	}
	if (D_KEYMANAGER->IsStayKeyDown('S'))
	{
		m_vEye.z -= 1.f;
	}
	if (D_KEYMANAGER->IsStayKeyDown('A'))
	{
		m_vEye.x -= 1.f;
	}
	if (D_KEYMANAGER->IsStayKeyDown('D'))
	{
		m_vEye.x += 1.f;
	}
}
