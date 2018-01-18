#pragma once
#include "cCubeMan.h"

class cCubeManNpc : public cCubeMan
{
private:
	void ActionControlNpc();

public:
	cCubeManNpc();
	virtual ~cCubeManNpc();

	virtual void Setup(const CHAR* pTextureFileName = NULL);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

