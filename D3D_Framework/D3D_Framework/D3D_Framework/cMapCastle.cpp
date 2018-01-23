#include "stdafx.h"
#include "cMapCastle.h"
#include "cGameCamera.h"
#include "cGrid.h"
#include "cSprite.h"
#include "cXPlayer.h"
#include "cSkinnedMesh.h"

cMapCastle::cMapCastle()
	: m_pLineGrid(NULL)
	, m_pWeaponTest(NULL)
{
}

cMapCastle::~cMapCastle()
{
}

void cMapCastle::Setup()
{
	cMap::Setup();

	m_pLineGrid = new cLineGrid();
	m_pLineGrid->Setup();

	//m_pPlayer = new cXPlayer();
	//m_pPlayer->Setup();

	m_pCamera = new cGameCamera();
	m_pCamera->Setup();
	//&m_pPlayer->GetPosition()

	m_pWeaponTest = new cSkinnedMesh();
	m_pWeaponTest->Setup("XFile/XItem/Weapon", "[0]Weapon.X");
}

void cMapCastle::Release()
{
	cMap::Release();
<<<<<<< HEAD
=======

	D_SAFE_DELETE(m_pCamera);
>>>>>>> 0f2ac7118d51c54005fc3acb7dc25d6823ddcf35

	D_SAFE_RELEASE(m_pLineGrid);
	D_SAFE_DELETE(m_pLineGrid);
}

void cMapCastle::Update()
{
	cMap::Update();

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pLineGrid)
		m_pLineGrid->Update();

	//if (m_pPlayer)
	//	m_pPlayer->Update();

	if (m_pWeaponTest)
		m_pWeaponTest->Update();

	this->ChangeWorldMapScene();
}

void cMapCastle::Render()
{
	cMap::Render();

	if (m_pLineGrid)
		m_pLineGrid->Render();

	//if (m_pPlayer)
	//	m_pPlayer->Render();

	if (m_pWeaponTest)
		m_pWeaponTest->Render();

	this->RenderNowMapInfo();
}

void cMapCastle::ChangeWorldMapScene()
{
	if (D_KEYMANAGER->IsOnceKeyDown('P'))
	{
		D_SCENEMANAGER->ChangeScene("MapWorldScene");
	}
}

void cMapCastle::RenderNowMapInfo()
{
	D_FONTMANAGER->DrawFontText("TimerFont", "[이곳은 성이에요.]",
		NULL,
		RectMake(D_WINSIZEX / 2, 0, 0, 0),
		D3DCOLOR_XRGB(255, 0, 0));
}