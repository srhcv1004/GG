#include "stdafx.h"
#include "cAseAi.h"
#include "cAseObject.h"

cAseAi::cAseAi()
{
}

cAseAi::~cAseAi()
{
}

void cAseAi::Setup(const CHAR * pAseFolderName, const CHAR * pAseFileName)
{
	cAseObject::Setup(pAseFolderName, pAseFileName);
}

void cAseAi::Release()
{
	cAseObject::Release();
}

void cAseAi::Update()
{
	cAseObject::Update();
}

void cAseAi::Render()
{
	cAseObject::Render();
}
