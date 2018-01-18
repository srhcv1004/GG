#include "stdafx.h"
#include "cAsePlayer.h"

cAsePlayer::cAsePlayer()
{
}

cAsePlayer::~cAsePlayer()
{
}

void cAsePlayer::Setup(const CHAR * pAseFolderName, const CHAR * pAseFileName)
{
	cAseObject::Setup(pAseFolderName, pAseFileName);
}

void cAsePlayer::Release()
{
	cAseObject::Release();
}

void cAsePlayer::Update()
{
	cAseObject::Update();
}

void cAsePlayer::Render()
{
	cAseObject::Render();
}
