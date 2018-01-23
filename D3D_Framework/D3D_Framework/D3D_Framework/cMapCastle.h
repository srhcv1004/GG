#pragma once
#include "cGameNode.h"
#include "cMap.h"

class iGrid;
class cParticle;

class cMapCastle : public cMap
{
private:
	iGrid*													m_pLineGrid;

private:
	cParticle*												m_pParticle;

private:
	void ChangeWorldMapScene();

private:
	void RenderNowMapInfo();

public:
	cMapCastle();
	virtual ~cMapCastle();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

