#include "stdafx.h"
#include "cMainMenu.h"
#include "cImage.h"
#include "cSprite.h"
#include "cMainMenuUI.h"

cMainMenu::cMainMenu()
	: m_pUI(NULL)
{
}

cMainMenu::~cMainMenu()
{
}

void cMainMenu::Setup()
{
	D_SPRITEMANAGER->AddSprite("메인메뉴", "Images/Sample/Image2D/MainMenu.bmp", D_WINSIZEX, D_WINSIZEY);

	m_pUI = new cMainMenuUI();
	m_pUI->Setup();
}

void cMainMenu::Release()
{
}

void cMainMenu::Update()
{
	if (m_pUI)
		m_pUI->Update();
}

void cMainMenu::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matWorld,
		D_SPRITEMANAGER->FindSprite("background")->GetWidth() / 2.F,
		D_SPRITEMANAGER->FindSprite("background")->GetHeight() / 2.F,
		0.F);

	D_SPRITEMANAGER->Render("background", &matWorld);

	if (m_pUI)
		m_pUI->Render();
}