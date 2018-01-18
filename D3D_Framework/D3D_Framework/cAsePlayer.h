#pragma once
#include "cAseObject.h"

class cAsePlayer : public cAseObject
{
public:
	cAsePlayer();
	virtual ~cAsePlayer();

	virtual void Setup(const CHAR* pAseFolderName, const CHAR* pAseFileName);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

