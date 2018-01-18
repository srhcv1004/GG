#include "stdafx.h"
#include "cSkinnedMonster.h"

cSkinnedMonster::cSkinnedMonster()
{
}

cSkinnedMonster::~cSkinnedMonster()
{
}

void cSkinnedMonster::Setup(const CHAR* pFolderName, const CHAR* pFileName)
{
	cSkinnedMesh::Setup(pFolderName, pFileName);
	m_fSpeed = 0.2F;
}

void cSkinnedMonster::Release()
{
	cSkinnedMesh::Release();
}

void cSkinnedMonster::Update()
{
	cSkinnedMesh::Update();

	this->PositionChangeKeyInput();
}

void cSkinnedMonster::Render()
{
	cSkinnedMesh::Render();
}

void cSkinnedMonster::PositionChangeKeyInput()
{
	
	D3DXMATRIXA16 matS, matR, matT;

	D3DXMatrixScaling(&matS, 0.05F, 0.05F, 0.05F);
	D3DXMatrixTranslation(&matT, m_vPosition.x,
		m_vPosition.y,
		m_vPosition.z);
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(1.F, 0.F, 0.F);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	m_matWorldTM = matS * matR * matT;
}
