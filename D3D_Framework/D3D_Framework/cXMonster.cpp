#include "stdafx.h"
#include "cXMonster.h"
#include "cSkinnedMesh.h"
#include "cSkinnedMonster.h"


cXMonster::cXMonster()
	:m_Monster(NULL)
{
}


cXMonster::~cXMonster()
{
	D_SAFE_DELETE(m_Monster);
}

void cXMonster::Setup()
{
	m_Monster = new cSkinnedMonster;
	m_Monster->Setup();
}

void cXMonster::Release()
{
	if (m_Monster)
		m_Monster->Release();
}

void cXMonster::Update()
{
	if (m_Monster)
		m_Monster->Update();
}

void cXMonster::Render()
{
	if (m_Monster)
		m_Monster->Render();
}
