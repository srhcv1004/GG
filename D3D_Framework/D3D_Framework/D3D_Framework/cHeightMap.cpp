#include "stdafx.h"
#include "cHeightMap.h"


cHeightMap::cHeightMap()
	: m_mapMesh(NULL)
	, m_pVB(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
	ZeroMemory(&m_mtrl, sizeof(D3DMATERIAL9));
}


cHeightMap::~cHeightMap()
{
	D_SAFE_RELEASE(m_mapMesh);
	D_SAFE_RELEASE(m_pVB);
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
	//��ǥ
	m_vecVertex.resize(D_MAPTILENUMX * D_MAPTILENUMZ);

	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		ST_PNT_VERTEX v;

		v.p = D3DXVECTOR3((i % D_MAPTILENUMX) * D_MAPTILESIZE - D_MAPHALFSIZEX, 0, (i / D_MAPTILENUMZ) * D_MAPTILESIZE - D_MAPHALFSIZEZ);
		v.n = D3DXVECTOR3(0, 1, 0);
		v.t = D3DXVECTOR2(0, 0);

		m_vecVertex[i] = v;
	}

	////�븻
	//for (int z = 0; z < D_MAPTILENUMZ; z++)
	//{
	//	for (int x = 0; x < D_MAPTILENUMX; x++)
	//	{
	//		if ((z == 0) || (x == 0) || (z == D_MAPTILENUMZ - 1) || (x == D_MAPTILENUMX - 1))
	//		{
	//			m_vecVertex[z * D_MAPTILENUMZ + x].n = D3DXVECTOR3(0, 1, 0);
	//		}
	//		else
	//		{
	//			D3DXVECTOR3 v1 = m_vecVertex[(z + 1) * D_MAPTILENUMZ + (x - 0)].p - m_vecVertex[(z - 1) * D_MAPTILENUMZ + (x - 0)].p;
	//			D3DXVECTOR3 v2 = m_vecVertex[(z - 0) * D_MAPTILENUMZ + (x + 1)].p - m_vecVertex[(z - 0) * D_MAPTILENUMZ + (x - 1)].p;

	//			D3DXVECTOR3 vNormal;
	//			D3DXVec3Cross(&vNormal, &v1, &v2);
	//			D3DXVec3Normalize(&vNormal, &vNormal);

	//			m_vecVertex[z * D_MAPTILENUMZ + x].n = vNormal;
	//		}
	//	}
	//}

	//�ε���
	for (int x = 0; x < D_MAPTILENUMX - 1; x++)
	{
		for (int z = 0; z < D_MAPTILENUMZ - 1; z++)
		{
			int _0 = (z + 0) * D_MAPTILENUMZ + (x + 0);
			int _1 = (z + 1) * D_MAPTILENUMZ + (x + 0);
			int _2 = (z + 0) * D_MAPTILENUMZ + (x + 1);
			int _3 = (z + 1) * D_MAPTILENUMZ + (x + 1);

			m_vecIndex.push_back(_0);
			m_vecIndex.push_back(_1);
			m_vecIndex.push_back(_2);

			m_vecIndex.push_back(_3);
			m_vecIndex.push_back(_2);
			m_vecIndex.push_back(_1);
		}
	}


	//�޽�
	D3DXCreateMeshFVF(m_vecIndex.size() / 3,
		m_vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		D_DEVICE,
		&m_mapMesh);
	ST_PNT_VERTEX* pVertex;
	m_mapMesh->LockVertexBuffer(0, (void**)&pVertex);
	memcpy(pVertex, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_mapMesh->UnlockVertexBuffer();

	DWORD* pI;
	m_mapMesh->LockIndexBuffer(0, (void**)&pI);
	memcpy(pI, &m_vecIndex[0], m_vecIndex.size() * sizeof(DWORD));
	m_mapMesh->UnlockIndexBuffer();

	DWORD* pAttrBuffer;
	m_mapMesh->LockAttributeBuffer(0, &pAttrBuffer);
	ZeroMemory(pAttrBuffer, (m_vecIndex.size() / 3) * sizeof(DWORD));
	m_mapMesh->UnlockAttributeBuffer();

	//std::vector<DWORD>	vecAdj(m_vecIndex.size());
	//m_mapMesh->GenerateAdjacency(0.f, &vecAdj[0]);
	//m_mapMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
	//	&vecAdj[0],
	//	0,
	//	0,
	//	0);
}

void cHeightMap::RenderMapGrid()
{
	D_DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	D_DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	D_DEVICE->SetTransform(D3DTS_WORLD, &m_matWorld);
	D_DEVICE->SetTexture(0, NULL);
	D_DEVICE->SetMaterial(&m_mtrl);
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


	int _0 = (nZ + 0) * (D_MAPTILENUMZ)+(nX + 0);
	int _1 = (nZ + 1) * (D_MAPTILENUMZ)+(nX + 0);
	int _2 = (nZ + 0) * (D_MAPTILENUMZ)+(nX + 1);
	int _3 = (nZ + 1) * (D_MAPTILENUMZ)+(nX + 1);

	//_1.._3
	//.
	//.
	//_0.._2

	// �Ʒ� �ﰢ��
	if (fDeltaX + fDeltaZ < 1.0f)
	{
		D3DXVECTOR3 v01 = m_vecVertex[_1].p - m_vecVertex[_0].p;
		D3DXVECTOR3 v02 = m_vecVertex[_2].p - m_vecVertex[_0].p;
		y = (v01 * fDeltaZ + v02 * fDeltaX).y + m_vecVertex[_0].p.y;
		return true;
	}
	// �� �ﰢ��
	else
	{
		fDeltaX = 1.0f - fDeltaX;
		fDeltaZ = 1.0f - fDeltaZ;
		D3DXVECTOR3 v31 = m_vecVertex[_1].p - m_vecVertex[_3].p;
		D3DXVECTOR3 v32 = m_vecVertex[_2].p - m_vecVertex[_3].p;
		y = (v31 * fDeltaX + v32 * fDeltaZ).y + m_vecVertex[_3].p.y;
		return true;
	}

	return false;
}
