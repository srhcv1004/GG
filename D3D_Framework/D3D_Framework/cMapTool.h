#pragma once
#include "cGameNode.h"

class cCamera;

class cMapTool : public cGameNode
{
private:
	struct ST_MAPTILE
	{
		ST_PNT_VERTEX	stVertex;
		float			fHeightY;
	};

	struct ST_BRUSH
	{
		D3DXVECTOR3		vPick;
		float			fRadius;
		//....또 뭐가 필요할까..
	};

private:
	cCamera*												m_pCamera;
	LPD3DXMESH												m_mapMesh;
	D3DXMATRIXA16											m_matWorld;
	D3DMATERIAL9											m_mtrl;

public:
	cMapTool();
	virtual ~cMapTool();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	void SetMapGrid();
	void SetMaterial();
	void SetLight();
	void RenderMapGrid();

	void Save();
	void Load();
};

