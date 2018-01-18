#include "stdafx.h"
#include "cActionLiner.h"
#include "cCharacter.h"

cActionLiner::cActionLiner()
	: m_pOwner(NULL)
	, m_vFrom(0.F, 0.F, 0.F)
	, m_vTo(0.F, 0.F, 0.F)
	, m_fActionTime(0.F)
	, m_fStartTime(0.F)
	, m_fPassedTime(0.F)
{
}

cActionLiner::~cActionLiner()
{
}

void cActionLiner::Start()
{
	if (m_pOwner)
	{
		m_pOwner->SetPosition(m_vFrom);
		m_fStartTime = D_TIMEMANAGER->GetWorldTime();
		m_fPassedTime = 0.F;
		m_vPrev = m_vFrom;
	}
}

void cActionLiner::Update()
{
	m_fPassedTime = D_TIMEMANAGER->GetWorldTime() - m_fStartTime;

	if (m_fPassedTime > m_fActionTime)
	{
		m_pOwner->SetPosition(m_vTo);
		if (m_pDelegate)
		{
			m_pDelegate->ActionFinish();
		}
	}
	else
	{
		float t = m_fPassedTime / m_fActionTime;
		D3DXVECTOR3 p = ((1.F - t) * m_vFrom) + (t * m_vTo);
		m_pOwner->SetPosition(p);

		D3DXVECTOR3 vDir = p - m_vPrev;
		m_pOwner->SetChangeDir(vDir);
	}
}
