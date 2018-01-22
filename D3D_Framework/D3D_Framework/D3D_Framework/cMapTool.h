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
	};

private:
	cCamera*												m_pCamera;
	cHeightMap*												m_pHeightMap;

	DWORD													m_dwCellSize;
	D3DXVECTOR3												m_vBrushPos;

	float													m_fDist;

private:
	void SetLight();

	void Picking();
	void SetHeight();
	void DrawBrush();

	void Save();
	void Load();

public:
	cMapTool();
	virtual ~cMapTool();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

