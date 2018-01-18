#include "stdafx.h"
#include "cInterpolation.h"
#include "cCharacter.h"
#include "cActionSequence.h"
#include "cActionLiner.h"

cInterpolation::cInterpolation()
	: m_pOwner(NULL)
	, m_pActionSeq(NULL)
{
}

cInterpolation::~cInterpolation()
{
}

void cInterpolation::Setup(cCharacter * pOwner)
{
	m_pOwner = pOwner;

	this->SetupVecLine();
	this->SetupActionSequence();

	if (m_pActionSeq)
		m_pActionSeq->Start();
}

void cInterpolation::Release()
{
	D_SAFE_DELETE(m_pActionSeq);
}

void cInterpolation::Update()
{
	if (m_pOwner)
		m_pOwner->Update();

	if (m_pActionSeq)
		m_pActionSeq->Update();
}

void cInterpolation::Render()
{
	if (m_pOwner)
		m_pOwner->Render();
}

void cInterpolation::SetupVecLine()
{
	float fRadius = 10.F;
	for (int i = 0; i < 60; i++)
	{
		ST_PC_VERTEX v;
		v.p = D3DXVECTOR3(cosf(i * D3DX_PI / 30.F) * fRadius,
			0.F, sinf(i * D3DX_PI / 30.F) * fRadius);
		v.c = D3DCOLOR_XRGB(255, 0, 0);

		m_vecLine.push_back(v);
	}
	m_vecLine.push_back(m_vecLine.front());
}

void cInterpolation::SetupActionSequence()
{
	m_pActionSeq = new cActionSequence();

	for (size_t i = 0; i < m_vecLine.size() - 1; i++)
	{
		cActionLiner* pLiner = new cActionLiner();

		pLiner->SetOwner(m_pOwner);
		pLiner->SetDelegate(m_pActionSeq);
		pLiner->SetActionTime(0.1F);
		pLiner->SetFrom(m_vecLine[i].p);
		pLiner->SetTo(m_vecLine[i + 1].p);

		m_pActionSeq->AddAction(pLiner);
	}
}
