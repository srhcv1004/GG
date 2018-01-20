#include "stdafx.h"
#include "cCube.h"

// ----------------------------------------------------------------------------------------------------
cCubePC::cCubePC()
{
}

cCubePC::~cCubePC()
{
}

void cCubePC::Setup()
{
	this->SetupCubeVertex();
}

void cCubePC::Release()
{
}

void cCubePC::Render()
{
	this->RenderCubeVertex();
}

void cCubePC::SetupCubeVertex()
{
	std::vector<ST_PC_VERTEX> vecVertex;
	vecVertex.resize(8);

	vecVertex[0].p = D3DXVECTOR3(-0.5F, -0.5F, -0.5F);
	vecVertex[1].p = D3DXVECTOR3(-0.5F,  0.5F, -0.5F);
	vecVertex[2].p = D3DXVECTOR3( 0.5F,  0.5F, -0.5F);
	vecVertex[3].p = D3DXVECTOR3( 0.5F, -0.5F, -0.5F);

	vecVertex[4].p = D3DXVECTOR3(-0.5F, -0.5F,  0.5F);
	vecVertex[5].p = D3DXVECTOR3(-0.5F,  0.5F,  0.5F);
	vecVertex[6].p = D3DXVECTOR3( 0.5F,  0.5F,  0.5F);
	vecVertex[7].p = D3DXVECTOR3( 0.5F, -0.5F,  0.5F);

	std::vector<DWORD> vecIdx;

	//����
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	//����
	vecIdx.push_back(5);
	vecIdx.push_back(4);
	vecIdx.push_back(7);

	vecIdx.push_back(5);
	vecIdx.push_back(7);
	vecIdx.push_back(6);

	//����
	vecIdx.push_back(4);
	vecIdx.push_back(5);
	vecIdx.push_back(1);

	vecIdx.push_back(4);
	vecIdx.push_back(1);
	vecIdx.push_back(0);

	//������
	vecIdx.push_back(3);
	vecIdx.push_back(2);
	vecIdx.push_back(6);

	vecIdx.push_back(3);
	vecIdx.push_back(6);
	vecIdx.push_back(7);

	//����
	vecIdx.push_back(1);
	vecIdx.push_back(5);
	vecIdx.push_back(6);

	vecIdx.push_back(1);
	vecIdx.push_back(6);
	vecIdx.push_back(2);

	//�Ʒ���
	vecIdx.push_back(4);
	vecIdx.push_back(0);
	vecIdx.push_back(3);

	vecIdx.push_back(4);
	vecIdx.push_back(3);
	vecIdx.push_back(7);

	m_vecVertex.resize(36);

	//position
	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		m_vecVertex[i].p	 = vecVertex[vecIdx[i]].p;
		m_vecVertex[i + 1].p = vecVertex[vecIdx[i + 1]].p;
		m_vecVertex[i + 2].p = vecVertex[vecIdx[i + 2]].p;
	}

	//color
	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		m_vecVertex[i].c	 = D3DCOLOR_XRGB(255, 0, 0);
		m_vecVertex[i + 1].c = D3DCOLOR_XRGB(255, 0, 0);
		m_vecVertex[i + 2].c = D3DCOLOR_XRGB(255, 0, 0);
	}
}

void cCubePC::RenderCubeVertex()
{
	D_DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	D_DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, (UINT)m_vecVertex.size() / (UINT)3,
		&m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
cCubePT::cCubePT()
{
}

cCubePT::~cCubePT()
{
}

void cCubePT::Setup()
{
	this->SetupCubeVertex();
}

void cCubePT::Release()
{
}

void cCubePT::Render()
{
	this->RenderCubeVertex();
}

void cCubePT::SetupCubeVertex()
{
	std::vector<ST_PT_VERTEX> vecVertex;
	vecVertex.resize(8);

	vecVertex[0].p = D3DXVECTOR3(-0.5F, -0.5F, -0.5F);
	vecVertex[1].p = D3DXVECTOR3(-0.5F,  0.5F, -0.5F);
	vecVertex[2].p = D3DXVECTOR3( 0.5F,  0.5F, -0.5F);
	vecVertex[3].p = D3DXVECTOR3( 0.5F, -0.5F, -0.5F);

	vecVertex[4].p = D3DXVECTOR3(-0.5F, -0.5F,  0.5F);
	vecVertex[5].p = D3DXVECTOR3(-0.5F,  0.5F,  0.5F);
	vecVertex[6].p = D3DXVECTOR3( 0.5F,  0.5F,  0.5F);
	vecVertex[7].p = D3DXVECTOR3( 0.5F, -0.5F,  0.5F);

	std::vector<DWORD> vecIdx;

	//����
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	//����
	vecIdx.push_back(5);
	vecIdx.push_back(4);
	vecIdx.push_back(7);

	vecIdx.push_back(5);
	vecIdx.push_back(7);
	vecIdx.push_back(6);

	//����
	vecIdx.push_back(4);
	vecIdx.push_back(5);
	vecIdx.push_back(1);

	vecIdx.push_back(4);
	vecIdx.push_back(1);
	vecIdx.push_back(0);

	//������
	vecIdx.push_back(3);
	vecIdx.push_back(2);
	vecIdx.push_back(6);

	vecIdx.push_back(3);
	vecIdx.push_back(6);
	vecIdx.push_back(7);

	//����
	vecIdx.push_back(1);
	vecIdx.push_back(5);
	vecIdx.push_back(6);

	vecIdx.push_back(1);
	vecIdx.push_back(6);
	vecIdx.push_back(2);

	//�Ʒ���
	vecIdx.push_back(4);
	vecIdx.push_back(0);
	vecIdx.push_back(3);

	vecIdx.push_back(4);
	vecIdx.push_back(3);
	vecIdx.push_back(7);

	m_vecVertex.resize(36);

	//position
	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		m_vecVertex[i].p	 = vecVertex[vecIdx[i]].p;
		m_vecVertex[i + 1].p = vecVertex[vecIdx[i + 1]].p;
		m_vecVertex[i + 2].p = vecVertex[vecIdx[i + 2]].p;
	}

	//uv
	for (size_t i = 0; i < m_vecVertex.size(); i += 6)
	{
		m_vecVertex[i].t	 = D3DXVECTOR2(0, 1);
		m_vecVertex[i + 1].t = D3DXVECTOR2(0, 0);
		m_vecVertex[i + 2].t = D3DXVECTOR2(1, 0);

		m_vecVertex[i + 3].t = D3DXVECTOR2(0, 1);
		m_vecVertex[i + 4].t = D3DXVECTOR2(1, 0);
		m_vecVertex[i + 5].t = D3DXVECTOR2(1, 1);
	}
}

void cCubePT::RenderCubeVertex()
{
	D_DEVICE->SetFVF(ST_PT_VERTEX::FVF);
	D_DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, (UINT)m_vecVertex.size() / (UINT)3,
		&m_vecVertex[0], sizeof(ST_PT_VERTEX));
}
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
cCubePNT::cCubePNT()
{
}

cCubePNT::~cCubePNT()
{
}

void cCubePNT::Setup()
{
	this->SetupCubeVertex();
}

void cCubePNT::Release()
{
}

void cCubePNT::Render()
{
	this->RenderCubeVertex();
}

void cCubePNT::SetupCubeVertex()
{
	std::vector<ST_PNT_VERTEX> vecVertex;
	vecVertex.resize(8);

	vecVertex[0].p = D3DXVECTOR3(-0.5F, -0.5F, -0.5F);
	vecVertex[1].p = D3DXVECTOR3(-0.5F,  0.5F, -0.5F);
	vecVertex[2].p = D3DXVECTOR3( 0.5F,  0.5F, -0.5F);
	vecVertex[3].p = D3DXVECTOR3( 0.5F, -0.5F, -0.5F);

	vecVertex[4].p = D3DXVECTOR3(-0.5F, -0.5F,  0.5F);
	vecVertex[5].p = D3DXVECTOR3(-0.5F,  0.5F,  0.5F);
	vecVertex[6].p = D3DXVECTOR3( 0.5F,  0.5F,  0.5F);
	vecVertex[7].p = D3DXVECTOR3( 0.5F, -0.5F,  0.5F);

	std::vector<DWORD> vecIdx;

	//����
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	//����
	vecIdx.push_back(5);
	vecIdx.push_back(4);
	vecIdx.push_back(7);

	vecIdx.push_back(5);
	vecIdx.push_back(7);
	vecIdx.push_back(6);

	//����
	vecIdx.push_back(4);
	vecIdx.push_back(5);
	vecIdx.push_back(1);

	vecIdx.push_back(4);
	vecIdx.push_back(1);
	vecIdx.push_back(0);

	//������
	vecIdx.push_back(3);
	vecIdx.push_back(2);
	vecIdx.push_back(6);

	vecIdx.push_back(3);
	vecIdx.push_back(6);
	vecIdx.push_back(7);

	//����
	vecIdx.push_back(1);
	vecIdx.push_back(5);
	vecIdx.push_back(6);

	vecIdx.push_back(1);
	vecIdx.push_back(6);
	vecIdx.push_back(2);

	//�Ʒ���
	vecIdx.push_back(4);
	vecIdx.push_back(0);
	vecIdx.push_back(3);

	vecIdx.push_back(4);
	vecIdx.push_back(3);
	vecIdx.push_back(7);

	m_vecVertex.resize(36);

	//position
	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		m_vecVertex[i].p	 = vecVertex[vecIdx[i]].p;
		m_vecVertex[i + 1].p = vecVertex[vecIdx[i + 1]].p;
		m_vecVertex[i + 2].p = vecVertex[vecIdx[i + 2]].p;
	}

	//uv
	for (size_t i = 0; i < m_vecVertex.size(); i += 6)
	{
		m_vecVertex[i].t	 = D3DXVECTOR2(0, 1);
		m_vecVertex[i + 1].t = D3DXVECTOR2(0, 0);
		m_vecVertex[i + 2].t = D3DXVECTOR2(1, 0);

		m_vecVertex[i + 3].t = D3DXVECTOR2(0, 1);
		m_vecVertex[i + 4].t = D3DXVECTOR2(1, 0);
		m_vecVertex[i + 5].t = D3DXVECTOR2(1, 1);
	}

	//normal
	D3DXVECTOR3 v1, v2;
	D3DXVECTOR3 n;

	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		v1 = m_vecVertex[i + 1].p - m_vecVertex[i].p;
		v2 = m_vecVertex[i + 2].p - m_vecVertex[i].p;

		D3DXVec3Normalize(&v1, &v1);
		D3DXVec3Normalize(&v2, &v2);
		D3DXVec3Cross(&n, &v1, &v2);

		m_vecVertex[i].n	 = n;
		m_vecVertex[i + 1].n = n;
		m_vecVertex[i + 2].n = n;
	}
}

void cCubePNT::RenderCubeVertex()
{
	D_DEVICE->SetFVF(ST_PNT_VERTEX::FVF);
	D_DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, (UINT)m_vecVertex.size() / (UINT)3,
		&m_vecVertex[0], sizeof(ST_PNT_VERTEX));
}
// ----------------------------------------------------------------------------------------------------