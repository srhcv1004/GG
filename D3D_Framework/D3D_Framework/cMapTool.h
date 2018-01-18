#pragma once
#include "cGameNode.h"

class cCamera;
class cLineGrid;

class cMapTool : public cGameNode
{
private:
	cCamera*												m_pCamera;

private:
	cLineGrid*												m_pGrid;

private:
	void Save();
	void Load();

public:
	cMapTool();
	virtual ~cMapTool();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

