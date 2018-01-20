#include "stdafx.h"
#include "cSkinnedPlayer.h"

cSkinnedPlayer::cSkinnedPlayer()
{
}

cSkinnedPlayer::~cSkinnedPlayer()
{
}

void cSkinnedPlayer::Setup(const CHAR* pFolderName, const CHAR* pFileName)
{
	cSkinnedMesh::Setup(pFolderName, pFileName);
	m_fSpeed = 0.2F;
}

void cSkinnedPlayer::Release()
{
	cSkinnedMesh::Release();
}

void cSkinnedPlayer::Update()
{
	cSkinnedMesh::Update();

	this->PositionChangeKeyInput();
}

void cSkinnedPlayer::Render()
{
	cSkinnedMesh::Render();
}

void cSkinnedPlayer::PositionChangeKeyInput()
{
	if (D_KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		m_pAnimationController->AdvanceTime(D_TIMEMANAGER->GetElapsedTime(), NULL);
		m_vPosition += m_vDirection * m_fSpeed;
	}

	if (D_KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		m_pAnimationController->AdvanceTime(D_TIMEMANAGER->GetElapsedTime(), NULL);
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
