#pragma once
#include "iMap.h"

class cHeightMap : public iMap
{
private:
	D_SYNTHESIZE_REF(std::vector<D3DXVECTOR3>, m_vecVertex, VecVertex);

	LPD3DXMESH												m_mapMesh;
	D3DXMATRIXA16											m_matWorld;
	D3DMATERIAL9											m_mtrl;

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

