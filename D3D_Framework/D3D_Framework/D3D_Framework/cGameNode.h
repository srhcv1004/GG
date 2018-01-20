#pragma once
#include "cImage.h"

class cGameNode
{
public:
	cGameNode();
	virtual ~cGameNode();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

