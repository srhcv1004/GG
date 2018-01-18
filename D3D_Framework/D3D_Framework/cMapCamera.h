#pragma once
#include "cCamera.h"

class cMapCamera : public cCamera
{
public:
	cMapCamera();
	virtual ~cMapCamera();

	virtual void CreateMatView();
	virtual void CreateMatProj();

	virtual void ControlCamDistance();
	virtual void ControlCamRotation();

	void Setup();
	void Update();

	void ControlCamPosition();
};

