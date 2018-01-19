#pragma once
#include "cGameNode.h"

class cHeightMap;
class cCamera;

class cMapTool : public cGameNode
{
private:
	struct ST_BRUSH
	{
		D3DXVECTOR3		p;
		D3DCOLOR		c;

		enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
		//....또 뭐가 필요할까..
	};

private:
	cCamera*												m_pCamera;

	DWORD													m_dwCellSize;
	D3DXVECTOR3												m_vBrushPos;

	cHeightMap*												m_pHeightMap;

	LPD3DXMESH												m_pMesh;

public:
	cMapTool();
	virtual ~cMapTool();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	void SetLight();

	void Picking();
	void DrawBrush();

	void Save();
	void Load();
};

