#pragma once
#include "cSkinnedMesh.h"

class cSkinnedMonster : public cSkinnedMesh
{
private:
	void PositionChangeKeyInput();

public:
	cSkinnedMonster();
	virtual ~cSkinnedMonster();

	virtual void Setup(const CHAR* pFolderName, const CHAR* pFileName);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};