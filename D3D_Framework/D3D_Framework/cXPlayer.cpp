#include "stdafx.h"
#include "cXPlayer.h"
#include "cSkinnedMesh.h"
#include "cSkinnedPlayer.h"

cXPlayer::cXPlayer()
{
}

cXPlayer::~cXPlayer()
{
}

void cXPlayer::Setup()
{
	this->SetupSkinnedParts();
}

void cXPlayer::Release()
{
	for (size_t i = 0; i < m_vecSkinnedPlayer.size(); i++)
	{
		D_SAFE_RELEASE(m_vecSkinnedPlayer[i]);
		D_SAFE_DELETE(m_vecSkinnedPlayer[i]);
	}
}

void cXPlayer::Update()
{
	for (size_t i = 0; i < m_vecSkinnedPlayer.size(); i++)
	{
		if (m_vecSkinnedPlayer[i])
			m_vecSkinnedPlayer[i]->Update();
	}
}

void cXPlayer::Render()
{
	for (size_t i = 0; i < m_vecSkinnedPlayer.size(); i++)
	{
		if (m_vecSkinnedPlayer[i])
			m_vecSkinnedPlayer[i]->Render();
	}
}

void cXPlayer::SetupSkinnedParts()
{
	m_vecSkinnedPlayer.resize(E_PARTS_END);

	cSkinnedMesh* pAllParts = new cSkinnedPlayer();
	pAllParts->Setup("XFile", "run.x");
	m_vecSkinnedPlayer[E_PARTS_BODY] = pAllParts;
}
