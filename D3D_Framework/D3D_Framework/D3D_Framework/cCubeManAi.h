#pragma once
#include "cCubeMan.h"

class cCubeManAi : public cCubeMan
{
public:
	cCubeManAi();
	virtual ~cCubeManAi();

	virtual void Setup(const CHAR* pTextureFileName = NULL);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

