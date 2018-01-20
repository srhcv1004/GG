#pragma once
#include "cCamera.h"

class cMapCamera : public cCamera
{
private:
	void ControlCamPosition();

public:
	cMapCamera();
	virtual ~cMapCamera();

	virtual void Setup(D3DXVECTOR3* pFollowPosition = NULL);
	virtual void Update();
};

