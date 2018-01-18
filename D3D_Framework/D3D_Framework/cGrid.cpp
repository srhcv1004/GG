#include "stdafx.h"
#include "cGrid.h"
#include "cRectTile.h"

// ----------------------------------------------------------------------------------------------------
cLineGrid::cLineGrid()
{
	D3DXMatrixIdentity(&m_matWorldTM);
}

cLineGrid::~cLineGrid()
{
}

void cLineGrid::Setup()
{
	for (int i = -D_TILENUMZ; i < D_TILENUMZ; i++)
	{
		for (int j = -D_TILENUMX; j < D_TILENUMX; j++)
		{
			ST_PC_VERTEX v;

			v.p = D3DXVECTOR3(i * D_TILESIZEX, 0, j * D_TILESIZEY);
			v.c = D3DCOLOR_XRGB(255, 255, 255);
			m_vecLine.push_back(v);

			v.p = D3DXVECTOR3(i * D_TILESIZEX, 0, j * D_TILESIZEY + D_TILESIZEY);
			v.c = D3DCOLOR_XRGB(255, 255, 255);
			m_vecLine.push_back(v);

			v.p = D3DXVECTOR3(j * D_TILESIZEX, 0, i * D_TILESIZEY);
			v.c = D3DCOLOR_XRGB(255, 255, 255);
			m_vecLine.push_back(v);

			v.p = D3DXVECTOR3(j * D_TILESIZEX + D_TILESIZEX, 0, i * D_TILESIZEY);
			v.c = D3DCOLOR_XRGB(255, 255, 255);
			m_vecLine.push_back(v);
		}
	}

	ST_PC_VERTEX v;

	v.p = D3DXVECTOR3(-D_TILENUMX * D_TILESIZEX, 0, D_TILENUMZ * D_TILESIZEY);
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	m_vecLine.push_back(v);

	v.p = D3DXVECTOR3(D_TILENUMX * D_TILESIZEX, 0, D_TILENUMZ * D_TILESIZEY);
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	m_vecLine.push_back(v);

	v.p = D3DXVECTOR3(D_TILENUMX * D_TILESIZEX, 0, -D_TILENUMZ * D_TILESIZEY);
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	m_vecLine.push_back(v);

	v.p = D3DXVECTOR3(D_TILENUMX * D_TILESIZEX, 0, D_TILENUMZ * D_TILESIZEY);
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	m_vecLine.push_back(v);
}

void cLineGrid::Release()
{
}

void cLineGrid::Update()
{
}

void cLineGrid::Render()
{
	D_DEVICE->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	D_DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	D_DEVICE->DrawPrimitiveUP(D3DPRIMITIVETYPE::D3DPT_LINELIST,
		m_vecLine.size() / 2, &m_vecLine[0], sizeof(ST_PC_VERTEX));
}
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
cRectGrid::cRectGrid()
	: m_pTexture(NULL)
	, m_arTile()
{
	D3DXMatrixIdentity(&m_matWorldTM);
}

cRectGrid::~cRectGrid()
{
}

void cRectGrid::Setup()
{
	D3DXCreateTextureFromFile(D_DEVICE, "Images/Sample/Texture/Grid/Block.jpg", &m_pTexture);

	for (int i = 0; i < D_TILENUMZ; i++)
	{
		for (int j = 0; j < D_TILENUMX; j++)
		{
			m_arTile[i][j] = new cRectTilePNT();
			m_arTile[i][j]->Setup(i, j);
		}
	}
}

void cRectGrid::Release()
{
	D_SAFE_RELEASE(m_pTexture);
}

void cRectGrid::Update()
{
}

void cRectGrid::Render()
{
	D_DEVICE->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	D_DEVICE->SetTexture(0, m_pTexture);

	for (int i = 0; i < D_TILENUMZ; i++)
	{
		for (int j = 0; j < D_TILENUMX; j++)
		{
			m_arTile[i][j]->Render();
		}
	}
}
// ----------------------------------------------------------------------------------------------------

