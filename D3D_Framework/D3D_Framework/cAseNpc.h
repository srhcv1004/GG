#pragma once
#include "cAseObject.h"

class cAseNpc : public cAseObject
{
public:
	cAseNpc();
	virtual ~cAseNpc();

	virtual void Setup(const CHAR* pAseFolderName, const CHAR* pAseFileName);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

