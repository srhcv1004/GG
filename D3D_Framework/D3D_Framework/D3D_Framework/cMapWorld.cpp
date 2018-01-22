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
}

void cMapWorld::Release()
{
}

void cMapWorld::Update()
{
	this->ChangeWorldMapScene();
}

void cMapWorld::Render()
{
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
	D_FONTMANAGER->DrawFontText("TimerFont", "[�̰��� �ʵ忡��.]",
		NULL,
		RectMake(D_WINSIZEX / 2, 0, 0, 0),
		D3DCOLOR_XRGB(255, 0, 0));
}