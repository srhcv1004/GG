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

	if (D_KEYMANAGER->IsStayKeyDown(VK_RBUTTON))
	{
		SetHeight();
	}
	if (D_KEYMANAGER->IsOnceKeyDown(VK_F1))
	{
		Save();
	}
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

void cMapTool::Save()
{
	FILE* fp = NULL;

	errno_t errNo = fopen_s(&fp, "map01.txt", "w");

	if (errNo) return;

	std::vector<ST_PNT_VERTEX>& vecVertex = m_pHeightMap->GetVecVertex();

	int count = 0;

	for (int i = 0; i < vecVertex.size(); i++)
	{
		count++;
		fprintf_s(fp, "[%d] : %f\n", i, vecVertex[i].p.y);
	}

	fclose(fp);
}

void cMapTool::Load()
{
}
