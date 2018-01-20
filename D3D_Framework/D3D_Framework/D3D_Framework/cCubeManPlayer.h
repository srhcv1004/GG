#pragma once
#include "cCubeMan.h"

class cCubeManPlayer : public cCubeMan
{
private:
	void KeyControlPlayer();

public:
	cCubeManPlayer();
	virtual ~cCubeManPlayer();

	virtual void Setup(const CHAR* pTextureFileName = NULL);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

