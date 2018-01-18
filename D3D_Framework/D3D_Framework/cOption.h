#pragma once
#include "cGameNode.h"

class cOption : public cGameNode
{
public:
	cOption();
	virtual ~cOption();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

