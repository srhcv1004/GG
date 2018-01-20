#pragma once
#include "cCamera.h"

class cMapCamera : public cCamera
{
private:
	void ControlCamPosition();

public:
	cMapCamera();
	virtual ~cMapCamera();

	virtual void Setup();
	virtual void Update();
};

