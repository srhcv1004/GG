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
	void SetKeys();

	void SetHeight();
	void DrawBrush();

	void Save(IN char* szFolder, IN char* szFileName);
	void Load(IN char* szFolder, IN char* szFileName);

public:
	cMapTool();
	virtual ~cMapTool();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

