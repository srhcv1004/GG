#pragma once
#include "cSingletonBase.h"

class cObjLoadManager : public cSingletonBase<cObjLoadManager>
{
public:
	cObjLoadManager();
	virtual ~cObjLoadManager();

	void Setup();
	void Release();

	void Load(const CHAR* pObjFolderName, const CHAR* pObjFileName);
};

