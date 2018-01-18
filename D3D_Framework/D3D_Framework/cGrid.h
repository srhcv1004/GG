#pragma once

class iRectTile;

class iGrid
{
public:
	iGrid() {}
	virtual ~iGrid() {}

	virtual void Setup() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

class cLineGrid : public iGrid
{
private:
	std::vector<ST_PC_VERTEX>								m_vecLine;

private:
	D3DXMATRIXA16											m_matWorldTM;

public:
	cLineGrid();
	virtual ~cLineGrid();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

class cRectGrid : public iGrid
{
private:
	IDirect3DTexture9*										m_pTexture;

private:
	iRectTile*												m_arTile[D_TILENUMX][D_TILENUMZ];

private:
	D3DXMATRIXA16											m_matWorldTM;

public:
	cRectGrid();
	virtual ~cRectGrid();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};
