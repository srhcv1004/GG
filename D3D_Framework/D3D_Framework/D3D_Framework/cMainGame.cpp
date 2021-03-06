#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cMainMenu.h"
#include "cMapTool.h"
#include "cOption.h"

#include "cMap.h"
#include "cMapCastle.h"
#include "cMapCave.h"
#include "cMapWorld.h"

cMainGame::cMainGame()
{
}

cMainGame::~cMainGame()
{
}

void cMainGame::Setup()
{
	cGameNode::Setup();

	this->AddFonts();
	this->AddSprites();
	this->AddScenes();
}

void cMainGame::Release()
{
	cGameNode::Release();
}

void cMainGame::Update()
{
	cGameNode::Update();

	D_SCENEMANAGER->Update();
}

void cMainGame::Render()
{
	cGameNode::Render();
	D_TIMEMANAGER->Render();

	D_DEVICE->BeginScene();

	D_SCENEMANAGER->Render();

	D_DEVICE->EndScene();
	D_DEVICE->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::AddScenes()
{
	cGameNode* pMainMenu = new cMainMenu();
	D_SCENEMANAGER->AddScene("MainMenuScene", pMainMenu);

	cGameNode* pMapCave = new cMapCave();
	D_SCENEMANAGER->AddScene("MapCaveScene", pMapCave);

	cGameNode* pMapCastle = new cMapCastle();
	D_SCENEMANAGER->AddScene("MapCastleScene", pMapCastle);

	cGameNode* pMapWorld = new cMapWorld();
	D_SCENEMANAGER->AddScene("MapWorldScene", pMapWorld);

	cGameNode* pMapTool = new cMapTool();
	D_SCENEMANAGER->AddScene("MapToolScene", pMapTool);

	cGameNode* pOption = new cOption();
	D_SCENEMANAGER->AddScene("OptionScene", pOption);

	D_SCENEMANAGER->ChangeScene("MainMenuScene");
}

void cMainGame::AddFonts()
{
	D_FONTMANAGER->AddFont("TimerFont", "1���Ͼ������ R", 14, 7);
}

void cMainGame::AddSprites()
{
	D_SPRITEMANAGER->AddSprite("background", "UI/background.jpg");
	D_SPRITEMANAGER->AddSprite("start", "UI/gamestart.png");
	D_SPRITEMANAGER->AddSprite("option", "UI/option.png");
	D_SPRITEMANAGER->AddSprite("maptool", "UI/maptool.png");
	D_SPRITEMANAGER->AddSprite("tera", "UI/tera.png");
}

void cMainGame::AddSounds()
{
}
