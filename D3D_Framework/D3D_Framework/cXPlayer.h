#pragma once
#include "cCharacter.h"

class cSkinnedMesh;

class cXPlayer : public cCharacter
{
public:
	enum E_PARTS
	{
		E_PARTS_HEAD,
		E_PARTS_BODY,
		E_PARTS_HAND,
		E_PARTS_LED,
		E_PARTS_END = 4
	};

private:
	std::vector<cSkinnedMesh*>								m_vecSkinnedPlayer;

private:
	void SetupSkinnedParts();
	
private:
	void PositionChangeKeyInput();

public:
	cXPlayer();
	~cXPlayer();

	void Setup();
	void Release();
	void Update();
	void Render();
};

