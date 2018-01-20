#pragma once
#include "cGameNode.h"

class cCamera;
class iGrid;

class cXPlayer;

class cInGame : public cGameNode
{
private:
	cCamera*												m_pCamera;

private:
	iGrid*													m_pLineGrid;

private:
	cXPlayer*												m_pPlayer;

public:
	cInGame();
	virtual ~cInGame();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

