#pragma once
#include "cUIButton.h"

class cUI;

class cMainMenuUI : public iButtonDelegate
{
private:
	cUI*													m_pRootUI;

private:
	void SetupUI();

private:

public:
	cMainMenuUI();
	~cMainMenuUI();

	void Setup();
	void Release();
	void Update();
	void Render();

	virtual void OnClickButton(cUIButton* pSender,
		E_BUTTON_TAG eButtonTag);
};

