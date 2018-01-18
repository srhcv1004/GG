#include "stdafx.h"
#include "cAseNode.h"
#include "cAnimation.h"

cAseNode::cAseNode()
	: m_pParentWorldTM(NULL)
	, m_pAnimation(NULL)
{
	D3DXMatrixIdentity(&m_matWorldTM);
	D3DXMatrixIdentity(&m_matLocalTM);
}

cAseNode::~cAseNode()
{
}

void cAseNode::Setup()
{
	cAse::Setup();

	if (m_pParentWorldTM)
	{
		D3DXMATRIXA16 matInvParentWorldTM;
		D3DXMatrixInverse(&matInvParentWorldTM, NULL, m_pParentWorldTM);
		m_matLocalTM = m_matWorldTM * matInvParentWorldTM;
	}
	else
	{
		m_matLocalTM = m_matWorldTM;
	}
	
	D3DXMATRIXA16 matInvWorldTM;
	D3DXMatrixInverse(&matInvWorldTM, NULL, &m_matWorldTM);
	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matInvWorldTM);
	}

	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Setup();
	}
}

void cAseNode::Release()
{
	cAse::Release();

	D_SAFE_RELEASE(m_pAnimation);
	D_SAFE_DELETE(m_pAnimation);

	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Release();
	}
}

void cAseNode::Update(float* pFrame)
{
	m_pAnimation->Update(pFrame, &m_matLocalTM);
	D3DXMATRIXA16& matAnimation = m_pAnimation->GetMatAnimation();

	m_matWorldTM = matAnimation;
	if (m_pParentWorldTM)
		m_matWorldTM *= (*m_pParentWorldTM);

	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Update(pFrame);
	}
}

void cAseNode::Render()
{
	D_DEVICE->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	cAse::Render();

	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Render();
	}
}

void cAseNode::AddChild(cAseNode * pChild)
{
	m_vecChild.push_back(pChild);
	pChild->m_pParentWorldTM = &m_matWorldTM;
}
