#pragma once
#include "cGameNode.h"

class cMainMenuUI;

class cMainMenu : public cGameNode
{
private:
	cMainMenuUI*											m_pUI;

public:
	cMainMenu();
	virtual ~cMainMenu();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

