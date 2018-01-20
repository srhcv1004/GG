#include "stdafx.h"
#include "cXMonster.h"
#include "cSkinnedMesh.h"

cXMonster::cXMonster()
	:m_Monster(NULL)
{
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
}

cXMonster::~cXMonster()
{
	D_SAFE_RELEASE(m_Monster);
	D_SAFE_DELETE(m_Monster);
}

void cXMonster::Setup(const CHAR* pFolderName, const CHAR* pFileName, D3DXVECTOR3 Size, D3DXVECTOR3 Position, int MonsterInfor, int MonsterLevel)
{

	cCharacter::Setup();
	m_Monster = new cSkinnedMesh;

	m_Monster->Setup(pFolderName, pFileName);
	

	D3DXMatrixScaling(&matS, Size.x, Size.y, Size.y);
	m_vPosition = Position;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorldTM = matS * matT;

	m_Monster->SetMatWorldPtr(&m_matWorldTM);

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
	//몬스터 이동
	MonsterMove();
}

void cXMonster::Render()
{
	if (m_Monster)
		m_Monster->Render();
}

void cXMonster::MonsterMove()
{

	//이동
	D3DXMatrixTranslation(&matT, m_vPosition.x,m_vPosition.y,m_vPosition.z);
	//회전
	D3DXMatrixRotationY(&matR, m_fRotY);
	//방향
	m_vDirection = D3DXVECTOR3(1.F, 0.F, 0.F);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	//월드행렬 적용
	m_matWorldTM = matS*matR * matT;
}
