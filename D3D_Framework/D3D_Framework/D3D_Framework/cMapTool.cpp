#include "stdafx.h"
#include "cMapTool.h"
#include "cGrid.h"
#include "cMapCamera.h"
#include "cHeightMap.h"
#include "cRay.h"

cMapTool::cMapTool()
	: m_pCamera(NULL)
	, m_dwCellSize(1)
	, m_vBrushPos(0, 0, 0)
	, m_pHeightMap(NULL)
	, m_fDist(0.f)
{
}

cMapTool::~cMapTool()
{
	D_SAFE_DELETE(m_pCamera);
	D_SAFE_DELETE(m_pHeightMap);
}

void cMapTool::Setup()
{
	m_pCamera = new cMapCamera();
	m_pCamera->Setup();

	m_pHeightMap = new cHeightMap();
	m_pHeightMap->Setup();

	SetLight();
}

void cMapTool::Update()
{
	if (m_pCamera)
		m_pCamera->Update();

	Picking();
	SetKeys();
}

void cMapTool::Render()
{
	if (m_pHeightMap)
		m_pHeightMap->Render();

	DrawBrush();
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

void cMapTool::Picking()
{
	std::vector<ST_PNT_VERTEX>& vecVertex = m_pHeightMap->GetVecVertex();
	int nTileCount = D_MAPTILENUMX - 1;
	int nCol = nTileCount + 1;

	cRay r = cRay::RayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);

	for (int x = 0; x < nTileCount; x++)
	{
		for (int z = 0; z < nTileCount; z++)
		{
			D3DXVECTOR3 vPickedPos1;
			D3DXVECTOR3 vPickedPos2;

			int _0 = (z + 0) * nCol + (x + 0);
			int _1 = (z + 1) * nCol + (x + 0);
			int _2 = (z + 0) * nCol + (x + 1);
			int _3 = (z + 1) * nCol + (x + 1);

			bool b1 = r.IntersectTri(vecVertex[_0].p,
				vecVertex[_1].p,
				vecVertex[_2].p,
				vPickedPos1);

			bool b2 = r.IntersectTri(vecVertex[_3].p,
				vecVertex[_2].p,
				vecVertex[_1].p,
				vPickedPos2);

			if (b1)
			{
				m_vBrushPos = vPickedPos1;
				return;
			}
			if (b2)
			{
				m_vBrushPos = vPickedPos2;
				return;
			}
		}
	}
}

void cMapTool::SetKeys()
{
	if (D_KEYMANAGER->IsStayKeyDown(VK_RBUTTON))
	{
		SetHeight();
	}
	if (D_KEYMANAGER->IsOnceKeyDown(VK_F1))
	{
		Save("map", "map01.txt");
	}
	if (D_KEYMANAGER->IsOnceKeyDown(VK_F2))
	{
		Load("map", "map01.txt");
	}
}

void cMapTool::SetHeight()
{
	ST_PNT_VERTEX* pVertex;
	m_pHeightMap->GetMapMesh()->LockVertexBuffer(0, (void**)&pVertex);

	for (int i = 0; i < m_pHeightMap->GetVecVertex().size(); i++)
	{
		D3DXVECTOR3 vMapPos = (pVertex[i].p);
		D3DXVECTOR3 vTempBrushPos = m_vBrushPos;
		vMapPos.y = vTempBrushPos.y = 0.f;
		float fDist = D3DXVec3Length(&(vMapPos - vTempBrushPos));
		float fHeight = 0.1f;

		if (fDist <= m_dwCellSize)
		{
			pVertex[i].p.y += fHeight - fDist * 0.1f;
			m_pHeightMap->GetVecVertex()[i].p.y += fHeight - fDist * 0.1f;;
		}
	}

	m_pHeightMap->GetMapMesh()->UnlockVertexBuffer();
}

void cMapTool::DrawBrush()
{
	//점 개수가 많을수록 원이 더 동그란 모양이 됨
	int nNumCircleDot = 50;

	float fRadian = D3DX_PI * 2.0f / nNumCircleDot;

	//CellSize가 커질수록 브러쉬의 크기가 커짐
	float fBrushSize = 1.0f * m_dwCellSize;

	//브러쉬를 그릴 구조체
	ST_BRUSH brushLine[2];

	D3DXVECTOR3 vCurPos(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3	vNewPos;

	m_fDist = D3DXVec3Length(&(vCurPos * fBrushSize - m_vBrushPos));

	D3DXMATRIXA16	matR;

	brushLine[1].p = vCurPos * fBrushSize + m_vBrushPos;
	brushLine[1].c = brushLine[0].c = D3DCOLOR_XRGB(120, 120, 255);

	for (int i = 0; i < nNumCircleDot + 1; i++)
	{
		brushLine[0] = brushLine[1];

		D3DXMatrixRotationY(&matR, i * fRadian);

		D3DXVec3TransformCoord(&vNewPos, &vCurPos, &matR);
		D3DXVec3Normalize(&vNewPos, &vNewPos);

		brushLine[1].p = vNewPos * fBrushSize + m_vBrushPos;

		if (brushLine[1].p.x < -D_MAPHALFSIZEX ||
			brushLine[1].p.x > D_MAPHALFSIZEX ||
			brushLine[1].p.z < -D_MAPHALFSIZEZ ||
			brushLine[1].p.z > D_MAPHALFSIZEZ)
		{
			continue;
		}
		else
		{
			D_DEVICE->SetRenderState(D3DRS_LIGHTING, false);
			D_DEVICE->SetFVF(ST_BRUSH::FVF);
			D_DEVICE->DrawPrimitiveUP(D3DPT_LINELIST, 1, brushLine, sizeof(ST_BRUSH));
		}
	}
}

void cMapTool::Save(IN char* szFolder, IN char* szFileName)
{
	FILE* fp = NULL;

	std::string sFullPath = std::string(szFolder) + std::string("/") + std::string(szFileName);

	errno_t errNo = fopen_s(&fp, sFullPath.c_str(), "w");

	if (errNo) return;

	std::vector<ST_PNT_VERTEX>& vecVertex = m_pHeightMap->GetVecVertex();

	int nSize = vecVertex.size();
	fprintf_s(fp, "[SIZE] : %d\n", nSize);

	for (int i = 0; i < vecVertex.size(); i++)
	{
		fprintf_s(fp, "[%d] : %f\n", i, vecVertex[i].p.y);
	}

	fclose(fp);
}

void cMapTool::Load(IN char* szFolder, IN char* szFileName)
{
	FILE* fp = NULL;

	std::string sFullPath = std::string(szFolder) + std::string("/") + std::string(szFileName);

	errno_t errNo = fopen_s(&fp, sFullPath.c_str(), "r");

	if (errNo) return;

	int nSize, nRow, nCol;
	fscanf_s(fp, "%*s : %d\n", &nSize);
	nRow = nCol = sqrt(nSize);
	float fMapHalfSizeX, fMapHalfSizeZ;
	fMapHalfSizeX = nRow * D_MAPTILESIZE / 2.f;
	fMapHalfSizeZ = nCol * D_MAPTILESIZE / 2.f;

	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::vector<DWORD>			vecIndex;
	vecVertex.resize(nSize);

	//좌표
	float fHeight;
	for (int i = 0; i < vecVertex.size(); i++)
	{
		ST_PNT_VERTEX v;
		fscanf_s(fp, "%*s : %f\n", &fHeight);

		v.p = D3DXVECTOR3((i % nRow) * D_MAPTILESIZE - fMapHalfSizeX, fHeight, (i / nCol) * D_MAPTILESIZE - fMapHalfSizeZ);
		v.n = D3DXVECTOR3(0, 1, 0);
		v.t = D3DXVECTOR2(0, 0);

		vecVertex[i] = v;
	}

	fclose(fp);

	////노말
	//for (int z = 0; z < nCol; z++)
	//{
	//	for (int x = 0; x < nRow; x++)
	//	{
	//		if ((z == 0) || (x == 0) || (z == nCol - 1) || (x == nRow - 1))
	//		{
	//			vecVertex[z * nCol + x].n = D3DXVECTOR3(0, 1, 0);
	//		}
	//		else
	//		{
	//			D3DXVECTOR3 v1 = vecVertex[(z + 1) * nCol + (x - 0)].p - vecVertex[(z - 1) * nCol + (x - 0)].p;
	//			D3DXVECTOR3 v2 = vecVertex[(z - 0) * nCol + (x + 1)].p - vecVertex[(z - 0) * nCol + (x - 1)].p;

	//			D3DXVECTOR3 vNormal;
	//			D3DXVec3Cross(&vNormal, &v1, &v2);
	//			D3DXVec3Normalize(&vNormal, &vNormal);

	//			vecVertex[z * nCol + x].n = vNormal;
	//		}
	//	}
	//}

	////인덱스
	//for (int x = 0; x < nRow - 1; x++)
	//{
	//	for (int z = 0; z < nCol - 1; z++)
	//	{
	//		int _0 = (z + 0) * nCol + (x + 0);
	//		int _1 = (z + 1) * nCol + (x + 0);
	//		int _2 = (z + 0) * nCol + (x + 1);
	//		int _3 = (z + 1) * nCol + (x + 1);

	//		vecIndex.push_back(_0);
	//		vecIndex.push_back(_1);
	//		vecIndex.push_back(_2);

	//		vecIndex.push_back(_3);
	//		vecIndex.push_back(_2);
	//		vecIndex.push_back(_1);
	//	}
	//}


	////메쉬
	//D3DXCreateMeshFVF(vecIndex.size() / 3,
	//	vecIndex.size(),
	//	D3DXMESH_MANAGED | D3DXMESH_32BIT,
	//	ST_PNT_VERTEX::FVF,
	//	D_DEVICE,
	//	&m_mapMesh);
	//ST_PNT_VERTEX* pVertex;
	//m_mapMesh->LockVertexBuffer(0, (void**)&pVertex);
	//memcpy(pVertex, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	//m_mapMesh->UnlockVertexBuffer();

	//DWORD* pI;
	//m_mapMesh->LockIndexBuffer(0, (void**)&pI);
	//memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	//m_mapMesh->UnlockIndexBuffer();

	//DWORD* pAttrBuffer;
	//m_mapMesh->LockAttributeBuffer(0, &pAttrBuffer);
	//ZeroMemory(pAttrBuffer, (vecIndex.size() / 3) * sizeof(DWORD));
	//m_mapMesh->UnlockAttributeBuffer();

	//std::vector<DWORD>	vecAdj(m_vecIndex.size());
	//m_mapMesh->GenerateAdjacency(0.f, &vecAdj[0]);
	//m_mapMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
	//	&vecAdj[0],
	//	0,
	//	0,
	//	0);
}
