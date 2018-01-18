#pragma once
#include "cCamera.h"

class cGameCamera : public cCamera
{
public:
	cGameCamera();
	virtual ~cGameCamera();

	virtual void CreateMatView();
	virtual void CreateMatProj();

	virtual void ControlCamDistance();
	virtual void ControlCamRotation();

	void Setup();
	void Update();
};

