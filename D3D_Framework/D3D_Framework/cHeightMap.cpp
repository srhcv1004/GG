#include "stdafx.h"
#include "cHeightMap.h"


cHeightMap::cHeightMap()
	: m_mapMesh(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
	ZeroMemory(&m_mtrl, sizeof(D3DMATERIAL9));
}


cHeightMap::~cHeightMap()
{
	D_SAFE_RELEASE(m_mapMesh);
}

void cHeightMap::Setup()
{
	SetMapGrid();
	SetMaterial();
}

void cHeightMap::Update()
{
}

void cHeightMap::Render()
{
	RenderMapGrid();
}

void cHeightMap::SetMaterial()
{
	m_mtrl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtrl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

void cHeightMap::SetMapGrid()
{
	std::vector<ST_PNT_VERTEX>		vecVertex;
	std::vector<DWORD>				vecIndex;

	//ÁÂÇ¥
	vecVertex.resize(D_MAPTILENUMX * D_MAPTILENUMZ);
	m_vecVertex.resize(D_MAPTILENUMX * D_MAPTILENUMZ);

	for (int i = 0; i < vecVertex.size(); i++)
	{
		ST_PNT_VERTEX v;

		v.p = D3DXVECTOR3((i % D_MAPTILENUMX) * D_MAPTILESIZE - D_MAPHALFSIZEX, 0, (i / D_MAPTILENUMZ) * D_MAPTILESIZE - D_MAPHALFSIZEZ);
		v.n = D3DXVECTOR3(0, 1, 0);
		v.t = D3DXVECTOR2(0, 0);

		vecVertex[i] = v;
		m_vecVertex[i] = v.p;
	}

	//³ë¸»
	for (int z = 0; z < D_MAPTILENUMZ; z++)
	{
		for (int x = 0; x < D_MAPTILENUMX; x++)
		{
			if ((z == 0) || (x == 0) || (z == D_MAPTILENUMZ - 1) || (x == D_MAPTILENUMX - 1))
			{
				vecVertex[z * D_MAPTILENUMZ + x].n = D3DXVECTOR3(0, 1, 0);
			}
			else
			{
				D3DXVECTOR3 v1 = vecVertex[(z + 1) * D_MAPTILENUMZ + (x - 0)].p - vecVertex[(z - 1) * D_MAPTILENUMZ + (x - 0)].p;
				D3DXVECTOR3 v2 = vecVertex[(z - 0) * D_MAPTILENUMZ + (x + 1)].p - vecVertex[(z - 0) * D_MAPTILENUMZ + (x - 1)].p;

				D3DXVECTOR3 vNormal;
				D3DXVec3Cross(&vNormal, &v1, &v2);
				D3DXVec3Normalize(&vNormal, &vNormal);

				vecVertex[z * D_MAPTILENUMZ + x].n = vNormal;
			}
		}
	}

	//ÀÎµ¦½º
	for (int x = 0; x < D_MAPTILENUMX - 1; x++)
	{
		for (int z = 0; z < D_MAPTILENUMZ - 1; z++)
		{
			int _0 = (z + 0) * D_MAPTILENUMZ + (x + 0);
			int _1 = (z + 1) * D_MAPTILENUMZ + (x + 0);
			int _2 = (z + 0) * D_MAPTILENUMZ + (x + 1);
			int _3 = (z + 1) * D_MAPTILENUMZ + (x + 1);

			vecIndex.push_back(_0);
			vecIndex.push_back(_1);
			vecIndex.push_back(_2);

			vecIndex.push_back(_3);
			vecIndex.push_back(_2);
			vecIndex.push_back(_1);
		}
	}

	//¸Þ½¬
	D3DXCreateMeshFVF(vecIndex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		D_DEVICE,
		&m_mapMesh);

	ST_PNT_VERTEX* pVertex;
	m_mapMesh->LockVertexBuffer(0, (void**)&pVertex);
	memcpy(pVertex, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_mapMesh->UnlockVertexBuffer();

	DWORD* pI;
	m_mapMesh->LockIndexBuffer(0, (void**)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	m_mapMesh->UnlockIndexBuffer();

	DWORD* pAttrBuffer;
	m_mapMesh->LockAttributeBuffer(0, &pAttrBuffer);
	ZeroMemory(pAttrBuffer, (vecIndex.size() / 3) * sizeof(DWORD));
	m_mapMesh->UnlockAttributeBuffer();

	std::vector<DWORD>	vecAdj(vecIndex.size());
	m_mapMesh->GenerateAdjacency(0.f, &vecAdj[0]);
	m_mapMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		0,
		0,
		0);
}

void cHeightMap::RenderMapGrid()
{
	D_DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	D_DEVICE->SetTransform(D3DTS_WORLD, &m_matWorld);
	D_DEVICE->SetTexture(0, NULL);
	D_DEVICE->SetMaterial(&m_mtrl);
	D_DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_mapMesh->DrawSubset(0);
}

bool cHeightMap::GetHeight(IN float x, OUT float & y, IN float z)
{
	if (x < 0.0f || z < 0.0f
		|| x >= (D_MAPTILENUMX) || z >= (D_MAPTILENUMZ))
	{
		return false;
	}

	int nX = x;
	int nZ = z;

	float fDeltaX = x - nX;
	float fDeltaZ = z - nZ;

	int _0 = (nZ + 0) * (D_MAPTILENUMZ) + (nX + 0);
	int _1 = (nZ + 1) * (D_MAPTILENUMZ) + (nX + 0);
	int _2 = (nZ + 0) * (D_MAPTILENUMZ) + (nX + 1);
	int _3 = (nZ + 1) * (D_MAPTILENUMZ) + (nX + 1);

	//_1.._3
	//.
	//.
	//_0.._2

	// ¾Æ·¡ »ï°¢Çü
	if (fDeltaX + fDeltaZ < 1.0f)
	{
		D3DXVECTOR3 v01 = m_vecVertex[_1] - m_vecVertex[_0];
		D3DXVECTOR3 v02 = m_vecVertex[_2] - m_vecVertex[_0];
		y = (v01 * fDeltaZ + v02 * fDeltaX).y + m_vecVertex[_0].y;
		return true;
	}
	// À§ »ï°¢Çü
	else
	{
		fDeltaX = 1.0f - fDeltaX;
		fDeltaZ = 1.0f - fDeltaZ;
		D3DXVECTOR3 v31 = m_vecVertex[_1] - m_vecVertex[_3];
		D3DXVECTOR3 v32 = m_vecVertex[_2] - m_vecVertex[_3];
		y = (v31 * fDeltaX + v32 * fDeltaZ).y + m_vecVertex[_3].y;
		return true;
	}

	return false;
}
