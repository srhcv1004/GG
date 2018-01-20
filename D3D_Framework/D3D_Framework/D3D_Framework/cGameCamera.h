#pragma once
#include "cCamera.h"

class cGameCamera : public cCamera
{
public:
	cGameCamera();
	virtual ~cGameCamera();

	virtual void Setup(D3DXVECTOR3* pFollowPosition = NULL);
	virtual void Update();
};

