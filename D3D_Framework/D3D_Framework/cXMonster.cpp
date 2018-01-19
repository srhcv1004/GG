#include "stdafx.h"
#include "cXMonster.h"
#include "cSkinnedMesh.h"

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
<<<<<<< HEAD
	//m_Monster = new cSkinnedMonster;
=======
	m_Monster = new cSkinnedMonster;
>>>>>>> ce453d3fcd9addc1d862da3fd79249e07d0d599f
	//m_Monster->Setup();
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
