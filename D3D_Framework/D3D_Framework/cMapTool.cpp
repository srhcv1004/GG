#include "stdafx.h"
#include "cMapTool.h"
#include "cGrid.h"
#include "cCamera.h"

cMapTool::cMapTool()
	: m_pCamera(NULL)
{
	ZeroMemory(&m_mtrl, sizeof(D3DMATERIAL9));
}

cMapTool::~cMapTool()
{
	if (m_pCamera)
		m_pCamera->Release();
	D_SAFE_RELEASE(m_mapMesh);
}

void cMapTool::Setup()
{
	m_pCamera = new cCamera();
	m_pCamera->Setup();

	SetLight();
	SetMaterial();
	SetMapGrid();
}

void cMapTool::Update()
{
	if (m_pCamera)
		m_pCamera->Update();
}

void cMapTool::Render()
{
	RenderMapGrid();
}

void cMapTool::SetMapGrid()
{
	std::vector<ST_PNT_VERTEX>		vecVertex;
	std::vector<DWORD>				vecIndex;

	//ÁÂÇ¥
	for (int i = 0; i < D_MAPTILENUMZ; i++)
	{
		for (int j = 0; j < D_MAPTILENUMX; j++)
		{
			ST_PNT_VERTEX v;

			v.p = D3DXVECTOR3(-50 + j * D_MAPTILESIZE, 0, -50 + i * D_MAPTILESIZE);
			v.n = D3DXVECTOR3(0, 1, 0);
			v.t = D3DXVECTOR2(0, 0);
			vecVertex.push_back(v);
		}
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

void cMapTool::SetMaterial()
{
	m_mtrl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtrl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

void cMapTool::SetLight()
{
	D3DLIGHT9	stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3		vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	D_DEVICE->SetLight(0, &stLight);
	D_DEVICE->LightEnable(0, true);
}

void cMapTool::RenderMapGrid()
{
	D_DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	D_DEVICE->SetTransform(D3DTS_WORLD, &m_matWorld);
	D_DEVICE->SetTexture(0, NULL);
	D_DEVICE->SetMaterial(&m_mtrl);
	D_DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_mapMesh->DrawSubset(0);
}

void cMapTool::Save()
{
}

void cMapTool::Load()
{
}
