#include "stdafx.h"
#include "cAseNpc.h"

cAseNpc::cAseNpc()
{
}

cAseNpc::~cAseNpc()
{
}

void cAseNpc::Setup(const CHAR * pAseFolderName, const CHAR * pAseFileName)
{
	cAseObject::Setup(pAseFolderName, pAseFileName);
}

void cAseNpc::Release()
{
	cAseObject::Release();
}

void cAseNpc::Update()
{
	cAseObject::Update();
}

void cAseNpc::Render()
{
	cAseObject::Render();
}
