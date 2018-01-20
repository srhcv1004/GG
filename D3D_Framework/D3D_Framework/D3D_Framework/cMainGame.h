#pragma once
#include "cGameNode.h"

class cMainGame : public cGameNode
{
public:
	cMainGame();
	virtual ~cMainGame();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void AddScenes();
	void AddFonts();
	void AddSprites();
	void AddSounds();
};

