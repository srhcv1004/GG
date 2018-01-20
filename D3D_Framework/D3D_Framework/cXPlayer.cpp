#include "stdafx.h"
#include "cXPlayer.h"
#include "cSkinnedMesh.h"

cXPlayer::cXPlayer()
	: m_eState(E_STATE_WAIT)
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

	D3DXMatrixScaling(&m_matS, 0.05F, 0.05F, 0.05F);
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

	// 키 입력을 통해서 현재 플레이어 상태를 변경
	this->StateChangeKeyInput();

	// 플레이어 상태 변경시 알맞는 애니메이션으로 변경
	this->AnimationChangeByState();

	this->UpdatePosition();
	this->UpdateRotation();

	m_matWorldTM = m_matS * m_matR * m_matT;
}

void cXPlayer::Render()
{
	D_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (size_t i = 0; i < m_vecSkinnedPlayer.size(); i++)
	{
		if (m_vecSkinnedPlayer[i])
			m_vecSkinnedPlayer[i]->Render();
	}
}

void cXPlayer::SetupSkinnedParts()
{
	m_vecSkinnedPlayer.resize(E_PARTS_END);

	// Head parts
	//cSkinnedMesh* pHand = new cSkinnedMesh();
	//pHand->Setup("XFile/XPlayer", "1.x");
	//pHand->SetMatWorldPtr(&m_matWorldTM);
	//m_vecSkinnedPlayer[E_PARTS_HEAD] = pHand;

	// Body parts
	cSkinnedMesh* pBody = new cSkinnedMesh();
	pBody->Setup("XFile/XPlayer", "[0]Body.x");
	pBody->SetMatWorldPtr(&m_matWorldTM);
	m_vecSkinnedPlayer[E_PARTS_BODY] = pBody;

	// Hand parts
	cSkinnedMesh* pHand = new cSkinnedMesh();
	pHand->Setup("XFile/XPlayer", "[0]Hand.x");
	pHand->SetMatWorldPtr(&m_matWorldTM);
	m_vecSkinnedPlayer[E_PARTS_HAND] = pHand;

	// Leg parts
	cSkinnedMesh* pLeg = new cSkinnedMesh();
	pLeg->Setup("XFile/XPlayer", "[0]Leg.x");
	pLeg->SetMatWorldPtr(&m_matWorldTM);
	m_vecSkinnedPlayer[E_PARTS_LEG] = pLeg;
}

void cXPlayer::StateChangeKeyInput()
{
	if (D_KEYMANAGER->IsOnceKeyDown(VK_UP))
	{
		m_eState = E_STATE_RUN;
	}
	else if (D_KEYMANAGER->IsOnceKeyUp(VK_UP))
	{
		m_eState = E_STATE_WAIT;
	}
}

void cXPlayer::AnimationChangeByState()
{
	for (size_t i = 0; i < m_vecSkinnedPlayer.size(); i++)
	{
		if (m_vecSkinnedPlayer[i])
			m_vecSkinnedPlayer[i]->SetAnimationIndexBlend(m_eState);
	}
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
	if (D_KEYMANAGER->IsStayKeyDown(VK_LEFT)) m_fRotY -= 0.1F;
	if (D_KEYMANAGER->IsStayKeyDown(VK_RIGHT)) m_fRotY += 0.1F;

	D3DXMatrixRotationY(&m_matR, m_fRotY);
	m_vDirection = D3DXVECTOR3(1.F, 0.F, 0.F);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &m_matR);
}