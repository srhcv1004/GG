#pragma once
#include "cCharacter.h"

class cCubeNode;

class cCubeMan : public cCharacter
{
protected:
	IDirect3DTexture9*										m_pTexture;

protected:
	cCubeNode*												m_pRootNode;

private:
	void SetCubeParts();

public:
	cCubeMan();
	virtual ~cCubeMan();

	virtual void Setup(const CHAR* pTextureFileName = NULL);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

