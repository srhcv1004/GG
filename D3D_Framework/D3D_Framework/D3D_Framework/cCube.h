#pragma once

// ----------------------------------------------------------------------------------------------------
class iCube
{
public:
	iCube() {}
	virtual ~iCube() {}

	virtual void Setup() = 0;
	virtual void Release() = 0;
	virtual void Render() = 0;
};
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
class cCubePC : public iCube
{
protected:
	std::vector<ST_PC_VERTEX>								m_vecVertex;

private:
	void SetupCubeVertex();
	void RenderCubeVertex();

public:
	cCubePC();
	virtual ~cCubePC();

	virtual void Setup();
	virtual void Release();
	virtual void Render();
};
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
class cCubePT : public iCube
{
protected:
	std::vector<ST_PT_VERTEX>								m_vecVertex;

private:
	void SetupCubeVertex();
	void RenderCubeVertex();

public:
	cCubePT();
	virtual ~cCubePT();

	virtual void Setup();
	virtual void Release();
	virtual void Render();
};
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
class cCubePNT : public iCube
{
protected:
	std::vector<ST_PNT_VERTEX>								m_vecVertex;

private:
	void SetupCubeVertex();
	void RenderCubeVertex();

public:
	cCubePNT();
	virtual ~cCubePNT();

	virtual void Setup();
	virtual void Release();
	virtual void Render();
};
// ----------------------------------------------------------------------------------------------------