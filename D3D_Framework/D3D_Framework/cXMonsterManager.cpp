#include "stdafx.h"
#include "cXMonsterManager.h"

cXMonsterManager::cXMonsterManager()
	:m_vMonster(NULL)
{
}


cXMonsterManager::~cXMonsterManager()
{
	if (!m_vMonster.empty())
	{
		for (int i = 0; i < m_vMonster.size(); i++)
		{
			D_SAFE_RELEASE(m_vMonster[i]);
			D_SAFE_DELETE(m_vMonster[i]);
		}
	}
}


void cXMonsterManager::Setup()
{
	
}

void cXMonsterManager::Release()
{
}

void cXMonsterManager::Update()
{
	if (!m_vMonster.empty())
	{
		for (int i = 0; i < m_vMonster.size(); i++)
		{
			if (m_vMonster[i] != NULL)
			{
				m_vMonster[i]->Update();
			}
		}
	}
}

void cXMonsterManager::Render()
{
	if (!m_vMonster.empty())
	{
		for (int i = 0; i < m_vMonster.size(); i++)
		{
			if (m_vMonster[i] != NULL)
			{
				m_vMonster[i]->Render();
			}
		}
	}
}

void cXMonsterManager::MakeMonster(const CHAR * pFolderName, const CHAR * pFileName, D3DXVECTOR3 Size, D3DXVECTOR3 Position, E_MonsterKind MonsterKind, int MonsterInfor, int MonsterLevel)
{
	switch (MonsterKind)
	{
		case E_NORMALMONSTER:
			cXMonster* temp;
			temp = new cXNormalMonster;
			temp->Setup(pFolderName, pFileName, Size, Position, MonsterInfor, MonsterLevel);
			m_vMonster.push_back(temp);
		break;

		case E_BOSSMONSTER:

		break;
	}

}

