#include "stdafx.h"
#include "cMapWorld.h"

cMapWorld::cMapWorld()
{
}

cMapWorld::~cMapWorld()
{
}

void cMapWorld::Setup()
{
	cMap::Setup();
}

void cMapWorld::Release()
{
	cMap::Release();
}

void cMapWorld::Update()
{
	cMap::Update();

	this->ChangeWorldMapScene();
}

void cMapWorld::Render()
{
	cMap::Render();

	this->RenderNowMapInfo();
}

void cMapWorld::ChangeWorldMapScene()
{
	if (D_KEYMANAGER->IsOnceKeyDown('P'))
	{
		D_SCENEMANAGER->ChangeScene("MapCaveScene");
	}

	if (D_KEYMANAGER->IsOnceKeyDown('O'))
	{
		D_SCENEMANAGER->ChangeScene("MapCastleScene");
	}
}

void cMapWorld::RenderNowMapInfo()
{
	D_FONTMANAGER->DrawFontText("TimerFont", "[이곳은 필드에요.]",
		NULL,
		RectMake(D_WINSIZEX / 2, 0, 0, 0),
		D3DCOLOR_XRGB(255, 0, 0));
}