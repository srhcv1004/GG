#include "stdafx.h"
#include "cCubeNode.h"

cCubeNode::cCubeNode()
	: m_pParentWorldTM(NULL)
	, m_fAniRotX(0.F)
	, m_fAniDeltaX(0.F)
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}

cCubeNode::~cCubeNode()
{
}

void cCubeNode::Setup()
{
	cCubePNT::Setup();
}

void cCubeNode::Release()
{
	cCubePNT::Release();
}

void cCubeNode::Update()
{
	D3DXMATRIXA16 matR, matT;

	D3DXMatrixTranslation(&matT, m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);
	D3DXMatrixRotationX(&matR, m_fAniRotX);

	m_matLocalTM = matR * matT;
	m_matWorldTM = m_matLocalTM;
	if (m_pParentWorldTM)
	{
		m_matWorldTM *= (*m_pParentWorldTM);
	}

	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		if (m_vecChild[i])
			m_vecChild[i]->Update();
	}
}

void cCubeNode::Render()
{
	D_DEVICE->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	cCubePNT::Render();

	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		if (m_vecChild[i])
			m_vecChild[i]->Render();
	}
}

void cCubeNode::AddChild(cCubeNode * pChild)
{
	m_vecChild.push_back(pChild);
	pChild->m_pParentWorldTM = &m_matWorldTM;
}

void cCubeNode::KeyAnimation()
{
	if (D_KEYMANAGER->IsStayKeyDown(VK_UP) ||
		D_KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		m_fAniRotX += m_fAniDeltaX;
	}

	if (m_fAniRotX >= D3DX_PI / 4.F)
	{
		m_fAniRotX = D3DX_PI / 4.F;
		m_fAniDeltaX *= -1.F;
	}
	if (m_fAniRotX <= -D3DX_PI / 4.F)
	{
		m_fAniRotX = -D3DX_PI / 4.F;
		m_fAniDeltaX *= -1.F;
	}

	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		if (m_vecChild[i])
			m_vecChild[i]->KeyAnimation();
	}
}

void cCubeNode::ActionAnimation()
{
	m_fAniRotX += m_fAniDeltaX;

	if (m_fAniRotX >= D3DX_PI / 4.F)
	{
		m_fAniRotX = D3DX_PI / 4.F;
		m_fAniDeltaX *= -1.F;
	}
	if (m_fAniRotX <= -D3DX_PI / 4.F)
	{
		m_fAniRotX = -D3DX_PI / 4.F;
		m_fAniDeltaX *= -1.F;
	}

	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		if (m_vecChild[i])
			m_vecChild[i]->ActionAnimation();
	}
}
