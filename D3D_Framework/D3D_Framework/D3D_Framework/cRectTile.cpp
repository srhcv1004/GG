#include "stdafx.h"
#include "cRectTile.h"

// ----------------------------------------------------------------------------------------------------
cRectTilePC::cRectTilePC()
	: m_nIdxX(0)
	, m_nIdxZ(0)
{
}

cRectTilePC::~cRectTilePC()
{
}

void cRectTilePC::Setup(int nIdxX, int nIdxZ)
{
	m_nIdxX								= nIdxX;
	m_nIdxZ								= nIdxZ;

	this->SetupRectTileVertex();
}

void cRectTilePC::Release()
{
}

void cRectTilePC::Render()
{
	this->RenderRectTileVertex();
}

void cRectTilePC::SetupRectTileVertex()
{
	std::vector<ST_PT_VERTEX> vecVertex;
	vecVertex.resize(4);

	D3DXVECTOR3 vZeroPos = D3DXVECTOR3(m_nIdxX * D_TILESIZEX - D_GRIDHALFSIZEX,
		0.F, m_nIdxZ * D_TILESIZEZ - D_GRIDHALFSIZEZ);

	vecVertex[0].p = vZeroPos;
	vecVertex[1].p = vZeroPos + D3DXVECTOR3(0.F, 0.F, D_TILESIZEZ);
	vecVertex[2].p = vZeroPos + D3DXVECTOR3(D_TILESIZEX, 0.F, D_TILESIZEZ);
	vecVertex[3].p = vZeroPos + D3DXVECTOR3(D_TILESIZEX, 0.F, 0.F);

	std::vector<DWORD> vecIdx;

	//앞쪽
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	m_vecVertex.resize(6);

	//position
	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		m_vecVertex[i].p	 = vecVertex[vecIdx[i]].p;
		m_vecVertex[i + 1].p = vecVertex[vecIdx[i + 1]].p;
		m_vecVertex[i + 2].p = vecVertex[vecIdx[i + 2]].p;
	}

	//color
	for (size_t i = 0; i < m_vecVertex.size(); i += 6)
	{
		m_vecVertex[i].c	 = D3DCOLOR_XRGB(255, 0, 0);
		m_vecVertex[i + 1].c = D3DCOLOR_XRGB(0, 255, 0);
		m_vecVertex[i + 2].c = D3DCOLOR_XRGB(0, 0, 255);

		m_vecVertex[i + 3].c = D3DCOLOR_XRGB(0, 0, 255);
		m_vecVertex[i + 4].c = D3DCOLOR_XRGB(0, 255, 0);
		m_vecVertex[i + 5].c = D3DCOLOR_XRGB(255, 0, 0);
	}
}

void cRectTilePC::RenderRectTileVertex()
{
	D_DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	D_DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, (UINT)m_vecVertex.size() / (UINT)3,
		&m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
cRectTilePT::cRectTilePT()
	: m_nIdxX(0)
	, m_nIdxZ(0)
{
}

cRectTilePT::~cRectTilePT()
{
}

void cRectTilePT::Setup(int nIdxX, int nIdxZ)
{
	m_nIdxX								= nIdxX;
	m_nIdxZ								= nIdxZ;

	this->SetupRectTileVertex();
}

void cRectTilePT::Release()
{
}

void cRectTilePT::Render()
{
	this->RenderRectTileVertex();
}

void cRectTilePT::SetupRectTileVertex()
{
	std::vector<ST_PT_VERTEX> vecVertex;
	vecVertex.resize(4);

	D3DXVECTOR3 vZeroPos = D3DXVECTOR3(m_nIdxX * D_TILESIZEX - D_GRIDHALFSIZEX,
		0.F, m_nIdxZ * D_TILESIZEZ - D_GRIDHALFSIZEZ);

	vecVertex[0].p = vZeroPos;
	vecVertex[1].p = vZeroPos + D3DXVECTOR3(0.F, 0.F, D_TILESIZEZ);
	vecVertex[2].p = vZeroPos + D3DXVECTOR3(D_TILESIZEZ, 0.F, D_TILESIZEZ);
	vecVertex[3].p = vZeroPos + D3DXVECTOR3(D_TILESIZEZ, 0.F, 0.F);

	std::vector<DWORD> vecIdx;

	//앞쪽
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	m_vecVertex.resize(6);

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

void cRectTilePT::RenderRectTileVertex()
{
	D_DEVICE->SetFVF(ST_PT_VERTEX::FVF);
	D_DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, (UINT)m_vecVertex.size() / (UINT)3,
		&m_vecVertex[0], sizeof(ST_PT_VERTEX));
}
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
cRectTilePNT::cRectTilePNT()
	: m_nIdxX(0)
	, m_nIdxZ(0)
{
}

cRectTilePNT::~cRectTilePNT()
{
}

void cRectTilePNT::Setup(int nIdxX, int nIdxZ)
{
	m_nIdxX								= nIdxX;
	m_nIdxZ								= nIdxZ;

	this->SetupRectTileVertex();
}

void cRectTilePNT::Release()
{
}

void cRectTilePNT::Render()
{
	this->RenderRectTileVertex();
}

void cRectTilePNT::SetupRectTileVertex()
{
	std::vector<ST_PNT_VERTEX> vecVertex;
	vecVertex.resize(4);

	D3DXVECTOR3 vZeroPos = D3DXVECTOR3(m_nIdxX * D_TILESIZEX - D_GRIDHALFSIZEX, 
		0.F, m_nIdxZ * D_TILESIZEZ - D_GRIDHALFSIZEZ);

	vecVertex[0].p = vZeroPos;
	vecVertex[1].p = vZeroPos + D3DXVECTOR3(0.F, 0.F, D_TILESIZEZ);
	vecVertex[2].p = vZeroPos + D3DXVECTOR3(D_TILESIZEZ, 0.F, D_TILESIZEZ);
	vecVertex[3].p = vZeroPos + D3DXVECTOR3(D_TILESIZEZ, 0.F, 0.F);

	std::vector<DWORD> vecIdx;

	//앞쪽
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	m_vecVertex.resize(6);

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

void cRectTilePNT::RenderRectTileVertex()
{
	D_DEVICE->SetFVF(ST_PNT_VERTEX::FVF);
	D_DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, (UINT)m_vecVertex.size() / (UINT)3,
		&m_vecVertex[0], sizeof(ST_PNT_VERTEX));
}
// ----------------------------------------------------------------------------------------------------