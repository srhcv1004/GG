#include "stdafx.h"
#include "cCubeParts.h"

cCubeParts::cCubeParts()
{
}

cCubeParts::~cCubeParts()
{
}

void cCubeParts::Setup(D3DXVECTOR3 vScale, D3DXVECTOR3 vAniLocal, D3DXVECTOR3 vLocalPos)
{
	cCubeNode::Setup();

	D3DXMATRIXA16 matS, matT, matLocal;

	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);
	D3DXMatrixTranslation(&matT, vAniLocal.x, vAniLocal.y, vAniLocal.z);

	matLocal = matS * matT;

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matLocal);
	}

	m_vLocalPos = vLocalPos;
}
