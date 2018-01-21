#pragma once
#include "cXPlayer.h"

class cEquip;

class cXPlayerAnimation
{
private:
	cEquip*													m_pEquip;

private:
	DOUBLE													m_dCurAnimationTime;

private:
	cXPlayer::E_STATE*										m_pCurState;

private:
	cXPlayer::E_STATE FindChangeState();

private:
	void StateChangeKeyInput();
	void StopSkillAnimation();

public:
	cXPlayerAnimation();
	~cXPlayerAnimation();

	void Setup(cXPlayer::E_STATE* pCurState);
	void Release();
	void Update();
	void Render();

	void ConnectionEquip(cEquip* pEquip) { m_pEquip = pEquip; }
	void AnimationChangeByState();
};

