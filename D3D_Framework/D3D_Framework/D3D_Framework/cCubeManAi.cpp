#include "stdafx.h"
#include "cCubeManAi.h"
#include "cCubeNode.h"

cCubeManAi::cCubeManAi()
{
}

cCubeManAi::~cCubeManAi()
{
}

void cCubeManAi::Setup(const CHAR* pTextureFileName)
{
	cCubeMan::Setup(pTextureFileName);
}

void cCubeManAi::Release()
{
	cCubeMan::Release();
}

void cCubeManAi::Update()
{

}

void cCubeManAi::Render()
{
	cCubeMan::Render();
}
