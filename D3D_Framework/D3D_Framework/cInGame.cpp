#include "stdafx.h"
#include "cInGame.h"
#include "cGameCamera.h"
#include "cGrid.h"
#include "cSprite.h"
#include "cXPlayer.h"

cInGame::cInGame()
	: m_pCamera(NULL)
	, m_pLineGrid(NULL)
	, m_pPlayer(NULL)
{
}

cInGame::~cInGame()
{
}

void cInGame::Setup()
{
	m_pCamera = new cGameCamera();
	m_pCamera->Setup();

	m_pLineGrid = new cLineGrid();
	m_pLineGrid->Setup();

	m_pPlayer = new cXPlayer();
	m_pPlayer->Setup();
}

void cInGame::Release()
{
	D_SAFE_DELETE(m_pCamera);

	D_SAFE_RELEASE(m_pLineGrid);
	D_SAFE_DELETE(m_pLineGrid);

	D_SAFE_RELEASE(m_pPlayer);
	D_SAFE_DELETE(m_pPlayer);
}

void cInGame::Update()
{
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pLineGrid)
		m_pLineGrid->Update();

	if (m_pPlayer)
		m_pPlayer->Update();
}

void cInGame::Render()
{
	if (m_pLineGrid)
		m_pLineGrid->Render();

	if (m_pPlayer)
		m_pPlayer->Render();
}