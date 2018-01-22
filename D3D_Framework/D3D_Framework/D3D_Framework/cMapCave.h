#pragma once
#include "cMap.h"

class cMapCave : public cMap
{
private:
	void ChangeWorldMapScene();

private:
	void RenderNowMapInfo();

public:
	cMapCave();
	virtual ~cMapCave();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

