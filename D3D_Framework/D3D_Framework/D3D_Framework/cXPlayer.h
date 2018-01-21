#pragma once
#include "cCharacter.h"

class cEquip;
class cXPlayerAnimation;

class cXPlayer : public cCharacter
{
public:
	enum E_STATE
	{
		E_STATE_NANMU1,
		E_STATE_NANMU2,
		E_STATE_NANMU3,
		E_STATE_NANMU4,
		E_STATE_NANMU5,
		E_STATE_NANMU6,
		E_STATE_RUN,
		E_STATE_WAIT,
		E_STATE_NONE,
		E_STATE_END = 9
	};

private:
	D_SYNTHESIZE_REF(E_STATE, m_eState, State);

private:
	cEquip*													m_pEquip;
	cXPlayerAnimation*										m_pAnimation;

private:
	D3DXMATRIXA16											m_matS;
	D3DXMATRIXA16											m_matR;
	D3DXMATRIXA16											m_matT;

private:
	void UpdatePosition();
	void UpdateRotation();

public:
	cXPlayer();
	~cXPlayer();

	void Setup();
	void Release();
	void Update();
	void Render();
};

