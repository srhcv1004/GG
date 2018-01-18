#pragma once
#include "cUIButton.h"

class cOptionUI : public iButtonDelegate
{
private:

public:
	cOptionUI();
	virtual ~cOptionUI();

	void Setup();
	void Release();
	void Update();
	void Render();
};