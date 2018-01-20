#include "stdafx.h"
#include "cGameCamera.h"

cGameCamera::cGameCamera()
{
}

cGameCamera::~cGameCamera()
{
}

void cGameCamera::Setup(D3DXVECTOR3* pFollowPosition)
{
	cCamera::Setup(pFollowPosition);
}

void cGameCamera::Update()
{
	cCamera::Update();
}