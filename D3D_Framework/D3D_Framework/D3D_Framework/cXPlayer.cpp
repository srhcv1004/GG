#include "stdafx.h"
#include "cXPlayer.h"
#include "cSkinnedMesh.h"

cXPlayer::cXPlayer()
{
}

cXPlayer::~cXPlayer()
{
}

void cXPlayer::Setup()
{
	cCharacter::Setup();

	m_fSpeed = 0.2F;

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

	this->PositionChangeKeyInput();
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

	cSkinnedMesh* pAllParts = new cSkinnedMesh();
	pAllParts->Setup("XFile", "run.x");
	pAllParts->SetMatWorldPtr(&m_matWorldTM);
	m_vecSkinnedPlayer[E_PARTS_BODY] = pAllParts;
}

void cXPlayer::PositionChangeKeyInput()
{
	if (D_KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		m_vPosition += m_vDirection * m_fSpeed;
	}

	if (D_KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		m_vPosition -= m_vDirection * m_fSpeed;
	}

	if (D_KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		m_fRotY -= 0.1F;
	}

	if (D_KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		m_fRotY += 0.1F;
	}

	D3DXMATRIXA16 matS, matR, matT;

	D3DXMatrixScaling(&matS, 0.05F, 0.05F, 0.05F);
	D3DXMatrixTranslation(&matT, m_vPosition.x,
		m_vPosition.y,
		m_vPosition.z);
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(1.F, 0.F, 0.F);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	m_matWorldTM = matS * matR * matT;
}
