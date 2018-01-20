#include "stdafx.h"
#include "cUIButton.h"
#include "cSprite.h"

cUIButton::cUIButton()
	: m_rc()
	, m_eButtonState(E_BTN_UP)
	, m_eButtonTag(E_TAG_NONE)
	, m_pDelegate(NULL)
{
}

cUIButton::~cUIButton()
{
}

void cUIButton::Setup(std::string strSpriteDownKey, 
	std::string strSpriteUpKey, 
	std::string strSpriteOverKey, 
	D3DXVECTOR3 vLocalPos, 
	E_BUTTON_TAG eButtonTag)
{
	cUI::Setup();

	this->SetupSprite(strSpriteDownKey, 
		strSpriteUpKey, 
		strSpriteOverKey);

	m_eButtonTag = eButtonTag;
	m_vLocalPos = vLocalPos;
}

void cUIButton::Release()
{
	cUI::Release();

	D_SAFE_DELETE(m_pDelegate);
}

void cUIButton::Update()
{
	cUI::Update();

	m_rc = RectMakeCenter(m_matWorldTM._41,
		m_matWorldTM._42,
		m_vecSprite[m_eButtonState]->GetWidth(),
		m_vecSprite[m_eButtonState]->GetHeight());

	if (PtInRect(&m_rc, g_ptMouse))
	{
		if (D_KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			if (m_eButtonState == E_BTN_OVER)
			{
				m_eButtonState = E_BTN_DOWN;
			}
		}
		else
		{
			if (m_eButtonState == E_BTN_DOWN)
			{
				if (m_pDelegate)
				{
					m_pDelegate->OnClickButton(this, m_eButtonTag);
				}
			}

			m_eButtonState = E_BTN_OVER;
		}
	}
	else
	{
		m_eButtonState = E_BTN_UP;
	}
}

void cUIButton::Render()
{
	cUI::Render();
	m_vecSprite[m_eButtonState]->Render(&m_matWorldTM);
}

void cUIButton::SetupSprite(std::string strSpriteDownKey, std::string strSpriteUpKey, std::string strSpriteOverKey)
{
	m_vecSprite.resize(E_BTN_END);

	m_vecSprite[E_BTN_DOWN] = D_SPRITEMANAGER->FindSprite(strSpriteDownKey);
	m_vecSprite[E_BTN_UP] = D_SPRITEMANAGER->FindSprite(strSpriteUpKey);
	m_vecSprite[E_BTN_OVER] = D_SPRITEMANAGER->FindSprite(strSpriteOverKey);
}
