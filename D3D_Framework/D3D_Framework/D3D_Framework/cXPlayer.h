#pragma once
#include "cCharacter.h"

class cSkinnedMesh;

class cXPlayer : public cCharacter
{
public:
	enum E_STATE
	{
		E_STATE_RUN,
		E_STATE_WAIT,
		E_STATE_NONE,
		E_STATE_END = 3
	};

public:
	enum E_PARTS
	{
		E_PARTS_HEAD,
		E_PARTS_BODY,
		E_PARTS_HAND,
		E_PARTS_LEG,
		E_PARTS_END = 4
	};

private:
	std::vector<cSkinnedMesh*>								m_vecSkinnedPlayer;

private:
	E_STATE													m_eState;

private:
	D3DXMATRIXA16											m_matS;
	D3DXMATRIXA16											m_matR;
	D3DXMATRIXA16											m_matT;

private:
	void SetupSkinnedParts();

private:
	void StateChangeKeyInput();
	void AnimationChangeByState();
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

