#include "stdafx.h"
#include "cCubeManNpc.h"
#include "cCubeNode.h"

cCubeManNpc::cCubeManNpc()
{
}

cCubeManNpc::~cCubeManNpc()
{
}

void cCubeManNpc::Setup(const CHAR* pTextureFileName)
{
	cCubeMan::Setup(pTextureFileName);
}

void cCubeManNpc::Release()
{
	cCubeMan::Release();
}

void cCubeManNpc::Update()
{
	cCubeMan::Update();

	this->ActionControlNpc();
}

void cCubeManNpc::Render()
{
	cCubeMan::Render();
}

void cCubeManNpc::ActionControlNpc()
{
	cCubeMan::Update();

	D3DXMATRIXA16 matR, matT;

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	NS_UTILS::GetDirection(matR, m_vDirection, m_vChangeDir);
	m_matWorldTM = matR * matT;

	if (m_pRootNode)
		m_pRootNode->ActionAnimation();
}
