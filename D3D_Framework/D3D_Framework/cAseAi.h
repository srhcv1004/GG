#pragma once
#include "cAseObject.h"

class cAseAi : public cAseObject
{
public:
	cAseAi();
	virtual ~cAseAi();

	virtual void Setup(const CHAR* pAseFolderName, const CHAR* pAseFileName);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

