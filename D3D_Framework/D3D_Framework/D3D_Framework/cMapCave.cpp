#include "stdafx.h"
#include "cMapCave.h"

cMapCave::cMapCave()
{
}

cMapCave::~cMapCave()
{
}

void cMapCave::Setup()
{
}

void cMapCave::Release()
{
}

void cMapCave::Update()
{
	this->ChangeWorldMapScene();
}

void cMapCave::Render()
{
	this->RenderNowMapInfo();
}

void cMapCave::ChangeWorldMapScene()
{
	if (D_KEYMANAGER->IsOnceKeyDown('O'))
	{
		D_SCENEMANAGER->ChangeScene("MapWorldScene");
	}
}

void cMapCave::RenderNowMapInfo()
{
	D_FONTMANAGER->DrawFontText("TimerFont", "[이곳은 동굴이에요.]",
		NULL,
		RectMake(D_WINSIZEX / 2, 0, 0, 0),
		D3DCOLOR_XRGB(255, 0, 0));
}