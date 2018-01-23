#include "stdafx.h"
#include "cMap.h"
#include "cCamera.h"
#include "cXPlayer.h"

cMap::cMap()
	: m_pCamera(NULL)
	, m_pPlayer(NULL)
{
}

cMap::~cMap()
{
}

void cMap::Setup()
{
}

void cMap::Release()
{
	D_SAFE_DELETE(m_pCamera);

	D_SAFE_RELEASE(m_pPlayer);
	D_SAFE_DELETE(m_pPlayer);
}

void cMap::Update()
{
}

void cMap::Render()
{
}
