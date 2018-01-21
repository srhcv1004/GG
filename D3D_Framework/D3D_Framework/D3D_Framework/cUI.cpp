#include "stdafx.h"
#include "cUI.h"

cUI::cUI()
	: m_pParentUI(NULL)
	, m_vLocalPos(0.F, 0.F, 0.F)
	, m_bIsHidden(false)
{
	D3DXMatrixIdentity(&m_matWorldTM);
}

cUI::~cUI()
{
}

void cUI::Setup()
{
}

void cUI::Release()
{
	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		if (m_vecChild[i])
		{
			m_vecChild[i]->Release();
			D_SAFE_DELETE(m_vecChild[i]);
		}
	}
}

void cUI::Update()
{
	if (m_bIsHidden) return;

	m_matWorldTM._41 = m_vLocalPos.x;
	m_matWorldTM._42 = m_vLocalPos.y;
	m_matWorldTM._43 = m_vLocalPos.z;

	if (m_pParentUI)
	{
		m_matWorldTM._41 += m_pParentUI->m_matWorldTM._41;
		m_matWorldTM._42 += m_pParentUI->m_matWorldTM._42;
		m_matWorldTM._43 += m_pParentUI->m_matWorldTM._43;
	}

	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		if (m_vecChild[i])
			m_vecChild[i]->Update();
	}
}

void cUI::Render()
{
	if (m_bIsHidden) return;

	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		if (m_vecChild[i])
			m_vecChild[i]->Render();
	}
}

void cUI::AddChild(cUI* pUI)
{
	m_vecChild.push_back(pUI);
	pUI->SetParentUI(this);
}