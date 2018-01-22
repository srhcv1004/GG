#pragma once
#include "iMap.h"

class cHeightMap : public iMap
{
private:
	std::vector<DWORD>										m_vecIndex;
	D_SYNTHESIZE_REF(std::vector<ST_PNT_VERTEX>, m_vecVertex, VecVertex);
	D_SYNTHESIZE(LPD3DXMESH, m_mapMesh, MapMesh);

	D3DXMATRIXA16											m_matWorld;
	D3DMATERIAL9											m_mtrl;

	LPDIRECT3DVERTEXBUFFER9									m_pVB;

public:
	cHeightMap();
	~cHeightMap();

	void Setup();
	void Update();
	void Render();

	void SetMaterial();

	void SetMapGrid();
	void RenderMapGrid();

	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;
};

