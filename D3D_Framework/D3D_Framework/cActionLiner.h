#pragma once
#include "cAction.h"

class cCharacter;

class cActionLiner : public cAction
{
protected:
	D_SYNTHESIZE(cCharacter*, m_pOwner, Owner);
	D_SYNTHESIZE(D3DXVECTOR3, m_vFrom, From);
	D_SYNTHESIZE(D3DXVECTOR3, m_vTo, To);
	D_SYNTHESIZE(float, m_fActionTime, ActionTime);

	D3DXVECTOR3												m_vPrev;
	float													m_fStartTime;
	float													m_fPassedTime;

public:
	cActionLiner();
	virtual ~cActionLiner();

	virtual void Start();
	virtual void Update();
};

