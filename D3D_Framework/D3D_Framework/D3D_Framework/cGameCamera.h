#pragma once
#include "cCamera.h"

class cGameCamera : public cCamera
{
public:
	cGameCamera();
	virtual ~cGameCamera();

	virtual void Setup();
	virtual void Update();
};

