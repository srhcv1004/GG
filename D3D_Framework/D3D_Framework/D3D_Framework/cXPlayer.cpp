#include "stdafx.h"
#include "cXPlayer.h"
#include "cEquip.h"
#include "cXPlayerAnimation.h"

cXPlayer::cXPlayer()
	: m_eState(E_STATE_WAIT)
	, m_pEquip(NULL)
	, m_pAnimation(NULL)
{
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
}

cXPlayer::~cXPlayer()
{
}

void cXPlayer::Setup()
{
	cCharacter::Setup();

	m_pEquip = new cEquip();
	m_pAnimation = new cXPlayerAnimation();

	m_pEquip->ConnectXPlayerAnimation(m_pAnimation);
	m_pEquip->Setup(&m_matWorldTM);

	m_pAnimation->ConnectionEquip(m_pEquip);
	m_pAnimation->Setup(&m_eState);

	D3DXMatrixScaling(&m_matS, 0.05F, 0.05F, 0.05F);
	m_fSpeed = 0.2F;
}

void cXPlayer::Release()
{
	D_SAFE_RELEASE(m_pEquip);
	D_SAFE_DELETE(m_pEquip);

	D_SAFE_RELEASE(m_pAnimation);
	D_SAFE_DELETE(m_pAnimation);
}

void cXPlayer::Update()
{
	if (m_pEquip)
		m_pEquip->Update();

	if (m_pAnimation)
		m_pAnimation->Update();

	this->UpdatePosition();
	this->UpdateRotation();

	m_matWorldTM = m_matS * m_matR * m_matT;
}

void cXPlayer::Render()
{
	if (m_pEquip)
		m_pEquip->Render();

	if (m_pAnimation)
		m_pAnimation->Render();
}

void cXPlayer::UpdatePosition()
{
	if (m_eState != E_STATE_RUN) return;

	m_vPosition += m_vDirection * m_fSpeed;
	D3DXMatrixTranslation(&m_matT, m_vPosition.x,
		m_vPosition.y,
		m_vPosition.z);
}

void cXPlayer::UpdateRotation()
{
	if (m_eState == E_STATE_NANMU1 ||
		m_eState == E_STATE_NANMU2 ||
		m_eState == E_STATE_NANMU3 ||
		m_eState == E_STATE_NANMU4 ||
		m_eState == E_STATE_NANMU5 ||
		m_eState == E_STATE_NANMU6) return;

	if (D_KEYMANAGER->IsStayKeyDown(VK_LEFT)) m_fRotY -= 0.1F;
	if (D_KEYMANAGER->IsStayKeyDown(VK_RIGHT)) m_fRotY += 0.1F;

	D3DXMatrixRotationY(&m_matR, m_fRotY);
	m_vDirection = D3DXVECTOR3(1.F, 0.F, 0.F);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &m_matR);
}
