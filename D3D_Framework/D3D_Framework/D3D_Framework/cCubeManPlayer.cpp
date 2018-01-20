#include "stdafx.h"
#include "cCubeManPlayer.h"
#include "cCubeNode.h"

cCubeManPlayer::cCubeManPlayer()
{
}

cCubeManPlayer::~cCubeManPlayer()
{
}

void cCubeManPlayer::Setup(const CHAR* pTextureFileName)
{
	cCubeMan::Setup(pTextureFileName);
}

void cCubeManPlayer::Release()
{
	cCubeMan::Release();
}

void cCubeManPlayer::Update()
{
	cCubeMan::Update();

	this->KeyControlPlayer();
}

void cCubeManPlayer::Render()
{
	cCubeMan::Render();
}

void cCubeManPlayer::KeyControlPlayer()
{
	if (D_KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		m_fRotY -= 0.05F;
	}
	else if (D_KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		m_fRotY += 0.05F;
	}

	if (D_KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		m_vPosition += m_vDirection * 0.1F;
	}
	else if (D_KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		m_vPosition -= m_vDirection * 0.1F;
	}

	D3DXMATRIXA16 matR, matT;

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDirection = D3DXVECTOR3(0.F, 0.F, 1.F);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	m_matWorldTM = matR * matT;

	if (m_pRootNode)
		m_pRootNode->KeyAnimation();
}