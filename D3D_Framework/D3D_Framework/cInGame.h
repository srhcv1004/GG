#pragma once
#include "cGameNode.h"

class cCamera;
class iGrid;

class cXPlayer;


//∏ÛΩ∫≈Õ
class cXMonsterManager;

class cInGame : public cGameNode
{
private:
	cCamera*												m_pCamera;

private:
	iGrid*													m_pLineGrid;

private:
	cXPlayer*												m_pPlayer;
	cXMonsterManager*										m_pMonster;
public:
	cInGame();
	virtual ~cInGame();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

