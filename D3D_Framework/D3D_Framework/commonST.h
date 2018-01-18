#pragma once

// Vertex

struct ST_PC_VERTEX
{
	ST_PC_VERTEX() {}
	ST_PC_VERTEX(D3DXVECTOR3 pos, D3DCOLOR color)
	{
		p = pos;
		c = color;
	}
	D3DXVECTOR3												p;
	D3DCOLOR												c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PT_VERTEX
{
	ST_PT_VERTEX() {}
	ST_PT_VERTEX(D3DXVECTOR3 pos, D3DXVECTOR2 uv)
	{
		p = pos;
		t = uv;
	}
	D3DXVECTOR3												p;
	D3DXVECTOR2												t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct ST_PNT_VERTEX
{
	ST_PNT_VERTEX() {}
	ST_PNT_VERTEX(D3DXVECTOR3 pos, D3DXVECTOR3 normal, D3DXVECTOR2 uv)
	{
		p = pos;
		n = normal;
		t = uv;
	}
	D3DXVECTOR3												p;
	D3DXVECTOR3												n;
	D3DXVECTOR2												t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_NORMAL };
};

struct ST_SPHERE
{
	D3DXVECTOR3 vCenter;
	float		fRadius;
	bool		bIsPicked;

	ST_SPHERE() : vCenter(0, 0, 0)
		, fRadius(0.0f), bIsPicked(false) {}
};

// Skinned Animation
struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16											matWorldTM;
};

struct ST_BONEMESH : public D3DXMESHCONTAINER
{
	ID3DXMesh*												pMeshOrigin;

	std::vector<D3DMATERIAL9>								vecMaterial;
	std::vector<IDirect3DTexture9*>							vecTexture;

	D3DXATTRIBUTERANGE*										pAttribute;
	DWORD													dwAttributeCount;

	D3DXMATRIXA16**											ppMat;
	D3DXMATRIXA16*											pMatOffset;
	D3DXMATRIXA16*											pMatCurrent;
};