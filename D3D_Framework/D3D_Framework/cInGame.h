#pragma once
#include "cGameNode.h"

class cGameCamera;
class iGrid;

class cXPlayer;

class cInGame : public cGameNode
{
private:
	cGameCamera*											m_pCamera;

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

