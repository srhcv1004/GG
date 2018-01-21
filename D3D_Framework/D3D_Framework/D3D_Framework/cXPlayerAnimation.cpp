#include "stdafx.h"
#include "cXPlayerAnimation.h"
#include "cSkinnedMesh.h"
#include "cEquip.h"

cXPlayerAnimation::cXPlayerAnimation()
	: m_dCurAnimationTime(0)
	, m_pEquip(NULL)
{
}

cXPlayerAnimation::~cXPlayerAnimation()
{
}

void cXPlayerAnimation::Setup(cXPlayer::E_STATE* pCurState)
{
	m_pCurState = pCurState;
	this->AnimationChangeByState();
}

void cXPlayerAnimation::Release()
{
}

void cXPlayerAnimation::Update()
{
	this->StateChangeKeyInput();
	this->StopSkillAnimation();
}

void cXPlayerAnimation::Render()
{
}

cXPlayer::E_STATE cXPlayerAnimation::FindChangeState()
{
	switch ((*m_pCurState))
	{
	case cXPlayer::E_STATE_RUN:
	{
		return cXPlayer::E_STATE_RUN;
	}
	break;

	default:
	{
		return cXPlayer::E_STATE_WAIT;
	}
	break;
	}

	return cXPlayer::E_STATE_NONE;
}

void cXPlayerAnimation::StateChangeKeyInput()
{
	m_dCurAnimationTime += D_TIMEMANAGER->GetElapsedTime();

	if (D_KEYMANAGER->IsOnceKeyDown(VK_UP))
	{
		m_dCurAnimationTime = 0.F;
		(*m_pCurState) = cXPlayer::E_STATE_RUN;
		this->AnimationChangeByState();
	}
	else if (D_KEYMANAGER->IsOnceKeyUp(VK_UP))
	{
		m_dCurAnimationTime = 0.F;
		(*m_pCurState) = cXPlayer::E_STATE_WAIT;
		this->AnimationChangeByState();
	}
	else if (D_KEYMANAGER->IsOnceKeyDown('1'))
	{
		m_dCurAnimationTime = 0.F;
		(*m_pCurState) = cXPlayer::E_STATE_NANMU1;
		this->AnimationChangeByState();
	}
	else if (D_KEYMANAGER->IsOnceKeyDown('2'))
	{
		m_dCurAnimationTime = 0.F;
		(*m_pCurState) = cXPlayer::E_STATE_NANMU2;
		this->AnimationChangeByState();
	}
	else if (D_KEYMANAGER->IsOnceKeyDown('3'))
	{
		m_dCurAnimationTime = 0.F;
		(*m_pCurState) = cXPlayer::E_STATE_NANMU3;
		this->AnimationChangeByState();
	}
	else if (D_KEYMANAGER->IsOnceKeyDown('4'))
	{
		m_dCurAnimationTime = 0.F;
		(*m_pCurState) = cXPlayer::E_STATE_NANMU4;
		this->AnimationChangeByState();
	}
	else if (D_KEYMANAGER->IsOnceKeyDown('5'))
	{
		m_dCurAnimationTime = 0.F;
		(*m_pCurState) = cXPlayer::E_STATE_NANMU5;
		this->AnimationChangeByState();
	}
	else if (D_KEYMANAGER->IsOnceKeyDown('6'))
	{
		m_dCurAnimationTime = 0.F;
		(*m_pCurState) = cXPlayer::E_STATE_NANMU6;
		this->AnimationChangeByState();
	}
}

void cXPlayerAnimation::AnimationChangeByState()
{
	std::vector<cSkinnedMesh*>& vecSkinnedMesh = 
		m_pEquip->GetVecSkinnedPlayer();

	for (size_t i = 0; i < vecSkinnedMesh.size(); i++)
	{
		if (vecSkinnedMesh[i])
		{
			vecSkinnedMesh[i]->SetAnimationIndexBlend((*m_pCurState));
		}
	}
}

void cXPlayerAnimation::StopSkillAnimation()
{
	std::vector<cSkinnedMesh*>& vecSkinnedMesh =
		m_pEquip->GetVecSkinnedPlayer();

	for (size_t i = 0; i < vecSkinnedMesh.size(); i++)
	{
		if (vecSkinnedMesh[i])
		{
			ID3DXAnimationController* pAniCtrl = NULL;
			LPD3DXANIMATIONSET pAniSet = NULL;

			pAniCtrl = vecSkinnedMesh[i]->GetAnimationController();
			pAniCtrl->GetAnimationSet((*m_pCurState), &pAniSet);

			DOUBLE dPeriodTime = pAniSet->GetPeriod();
			if (m_dCurAnimationTime >= dPeriodTime)
			{
				(*m_pCurState) = this->FindChangeState();
				this->AnimationChangeByState();
				m_dCurAnimationTime = 0.F;
			}
		}
	}
}
