#pragma once
#include "cCharacter.h"

class cXFileObj : public cCharacter
{
protected:
	D3DXFRAME*												m_pRootBone;
	ID3DXAnimationController*								m_pAnimationController;

protected:
	ID3DXMesh*												m_pMeshSphereBone;

private:
	void SetupMeshes(ST_BONE* pBone);

private:
	void DestroyAll(ST_BONE* pBone);

private:
	void UpdateMatWorldTM(ST_BONE* pBone, D3DXMATRIXA16* pMatParentWorldTM);

private:
	void RenderMeshes(ST_BONE* pBone);
	void RenderBones(ST_BONE* pBone);

public:
	cXFileObj();
	virtual ~cXFileObj();

	void Setup(const CHAR* pXFileName);
	void Release();
	void Update();
	void Render();
};

