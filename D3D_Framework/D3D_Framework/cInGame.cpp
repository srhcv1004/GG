#include "stdafx.h"
#include "cInGame.h"
#include "cGameCamera.h"
#include "cGrid.h"
#include "cSprite.h"
#include "cXPlayer.h"
#include "cXMonsterManager.h"
cInGame::cInGame()
	: m_pCamera(NULL)
	, m_pLineGrid(NULL)
	, m_pPlayer(NULL)
	, m_pMonster(NULL)
{
}

cInGame::~cInGame()
{
}

void cInGame::Setup()
{
	m_pLineGrid = new cLineGrid();
	m_pLineGrid->Setup();

	m_pPlayer = new cXPlayer();
	m_pPlayer->Setup();

<<<<<<< HEAD
	m_pCamera = new cGameCamera();
	m_pCamera->Setup(&m_pPlayer->GetPosition());

=======
	m_pMonster = new cXMonsterManager();
	m_pMonster->MakeMonster("XFile","Monster/Shadowarmer.x",D3DXVECTOR3(0.05f, 0.05f, 0.05f), D3DXVECTOR3(10, 0, 0),E_NORMALMONSTER,0,0);
	m_pMonster->MakeMonster("XFile", "Monster/BloodGolem.x", D3DXVECTOR3(0.01f, 0.01f, 0.01f), D3DXVECTOR3(0, 0,2), E_NORMALMONSTER, 0, 0);
	m_pMonster->MakeMonster("XFile", "Monster/HoundMailgoth.x", D3DXVECTOR3(0.05f, 0.05f, 0.05f), D3DXVECTOR3(2, 0, 2), E_NORMALMONSTER, 0, 0);
>>>>>>> 086231afa0b58b93228b30bae654504751b061b1
}

void cInGame::Release()
{
	D_SAFE_DELETE(m_pCamera);

	D_SAFE_RELEASE(m_pLineGrid);
	D_SAFE_DELETE(m_pLineGrid);

	D_SAFE_RELEASE(m_pPlayer);
	D_SAFE_DELETE(m_pPlayer);

	D_SAFE_RELEASE(m_pMonster);
	D_SAFE_DELETE(m_pMonster);
}

void cInGame::Update()
{
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pLineGrid)
		m_pLineGrid->Update();

	if (m_pPlayer)
		m_pPlayer->Update();

	if (m_pMonster)
		m_pMonster->Update();
}

void cInGame::Render()
{
	if (m_pLineGrid)
		m_pLineGrid->Render();

	if (m_pPlayer)
		m_pPlayer->Render();
<<<<<<< HEAD
}
=======

	if (m_pMonster)
		m_pMonster->Render();
}
>>>>>>> 086231afa0b58b93228b30bae654504751b061b1
