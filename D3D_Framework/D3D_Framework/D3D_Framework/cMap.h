#pragma once
#include "cGameNode.h"

class cCamera;
class cXPlayer;

class cMap : public cGameNode
{
protected:
	cCamera*												m_pCamera;

protected:
	cXPlayer*												m_pPlayer;

public:
	cMap();
	virtual ~cMap();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};