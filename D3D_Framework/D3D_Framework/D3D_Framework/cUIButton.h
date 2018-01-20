#pragma once
#include "cUI.h"

class cSprite;
class cUIButton;

class iButtonDelegate
{
public:
	iButtonDelegate() {}
	virtual ~iButtonDelegate() {}

	virtual void OnClickButton(cUIButton* pSender, E_BUTTON_TAG eButtonTag) = 0;
};

class cUIButton : public cUI
{
public:
	enum E_BUTTON_STATE
	{
		E_BTN_DOWN,
		E_BTN_UP,
		E_BTN_OVER,
		E_BTN_END = 3
	};

protected:
	D_SYNTHESIZE(iButtonDelegate*, m_pDelegate, Delegate);

protected:
	std::vector<cSprite*>									m_vecSprite;
	
protected:
	RECT													m_rc;

protected:
	E_BUTTON_STATE											m_eButtonState;
	E_BUTTON_TAG											m_eButtonTag;

private:
	void SetupSprite(std::string strSpriteDownKey,
		std::string strSpriteUpKey,
		std::string strSpriteOverKey);

public:
	cUIButton();
	virtual ~cUIButton();

	void Setup(std::string strSpriteDownKey,
		std::string strSpriteUpKey,
		std::string strSpriteOverKey,
		D3DXVECTOR3 vLocalPos,
		E_BUTTON_TAG eButtonTag);

	void Release();
	virtual void Update();
	virtual void Render();
};

