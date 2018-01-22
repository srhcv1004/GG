#pragma once
#include "cMap.h"

class cMapWorld : public cMap
{
private:
	void ChangeWorldMapScene();

private:
	void RenderNowMapInfo();

public:
	cMapWorld();
	virtual ~cMapWorld();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

