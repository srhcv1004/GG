#include "stdafx.h"
#include "cTexMtl.h"

cTexMtl::cTexMtl()
{
}

cTexMtl::~cTexMtl()
{
}

void cTexMtl::Release()
{
	D_SAFE_RELEASE(m_pTex);
}

void cTexMtl::CreateTexture(const CHAR* pTexFileName)
{
	D3DXCreateTextureFromFile(D_DEVICE, pTexFileName, &m_pTex);
}
