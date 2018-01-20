#pragma once
#include "cSkinnedMesh.h"

class cSkinnedPlayer : public cSkinnedMesh
{
private:
	void PositionChangeKeyInput();

public:
	cSkinnedPlayer();
	virtual ~cSkinnedPlayer();

	virtual void Setup(const CHAR* pFolderName, const CHAR* pFileName);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};