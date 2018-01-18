#pragma once

// ----------------------------------------------------------------------------------------------------
class iCubeTile
{
public:
	iCubeTile() {}
	virtual ~iCubeTile() {}

	virtual void Setup() = 0;
	virtual void Release() = 0;
	virtual void Render() = 0;
};
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
class cCubeTilePC : public iCubeTile
{
private:
	std::vector<ST_PC_VERTEX>								m_vecVertex;

private:
	void SetupCubeTileVertex();
	void RenderCubeTileVertex();

public:
	cCubeTilePC();
	virtual ~cCubeTilePC();

	virtual void Setup();
	virtual void Release();
	virtual void Render();
};
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
class cCubeTilePT : public iCubeTile
{
private:
	std::vector<ST_PT_VERTEX>								m_vecVertex;

private:
	void SetupCubeTileVertex();
	void RenderCubeTileVertex();

public:
	cCubeTilePT();
	virtual ~cCubeTilePT();

	virtual void Setup();
	virtual void Release();
	virtual void Render();
};
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
class cCubeTilePNT : public iCubeTile
{
private:
	std::vector<ST_PNT_VERTEX>								m_vecVertex;

private:
	void SetupCubeTileVertex();
	void RenderCubeTileVertex();

public:
	cCubeTilePNT();
	virtual ~cCubeTilePNT();

	void Setup();
	void Release();
	void Render();
};
// ----------------------------------------------------------------------------------------------------