#include "stdafx.h"
#include "cCharacter.h"

cCharacter::cCharacter()
	: m_vPosition(0.F, 0.F, 0.F)
	, m_vDirection(0.F, 0.F, 0.F)
	, m_fRotY(0.F)
	, m_fSpeed(0.F)
{
	D3DXMatrixIdentity(&m_matWorldTM);
}

cCharacter::~cCharacter()
{
}

void cCharacter::Setup()
{
	m_vDirection = D3DXVECTOR3(1.F, 0.F, 0.F);
	m_vPosition = D3DXVECTOR3(0.F, 0.F, 0.F);
}

void cCharacter::Release()
{
}

void cCharacter::Update()
{
}

void cCharacter::Render()
{
}
