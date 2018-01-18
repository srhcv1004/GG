#pragma once

// ----------------------------------------------------------------------------------------------------
class iRectTile
{
public:
	iRectTile() {}
	virtual ~iRectTile() {}

	virtual void Setup(int nIdxX, int nIdxZ) = 0;
	virtual void Release() = 0;
	virtual void Render() = 0;
};
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
class cRectTilePC : public iRectTile
{
private:
	int														m_nIdxX;
	int														m_nIdxZ;

private:
	std::vector<ST_PC_VERTEX>								m_vecVertex;

private:
	void SetupRectTileVertex();
	void RenderRectTileVertex();

public:
	cRectTilePC();
	virtual ~cRectTilePC();

	virtual void Setup(int nIdxX, int nIdxZ);
	virtual void Release();
	virtual void Render();
};
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
class cRectTilePT : public iRectTile
{
private:
	int														m_nIdxX;
	int														m_nIdxZ;

private:
	std::vector<ST_PT_VERTEX>								m_vecVertex;

private:
	void SetupRectTileVertex();
	void RenderRectTileVertex();

public:
	cRectTilePT();
	virtual ~cRectTilePT();

	virtual void Setup(int nIdxX, int nIdxZ);
	virtual void Release();
	virtual void Render();
};
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
class cRectTilePNT : public iRectTile
{
private:
	int														m_nIdxX;
	int														m_nIdxZ;

private:
	std::vector<ST_PNT_VERTEX>								m_vecVertex;

private:
	void SetupRectTileVertex();
	void RenderRectTileVertex();

public:
	cRectTilePNT();
	virtual ~cRectTilePNT();

	void Setup(int nIdxX, int nIdxZ);
	void Release();
	void Render();
};
// ----------------------------------------------------------------------------------------------------