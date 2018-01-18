#pragma once
#include "cCharacter.h"

class cSkinnedMesh : public cCharacter
{
protected:
	D3DXFRAME*												m_pRootBone;

protected:
	ID3DXMesh*												m_pSphere;

protected:
	ID3DXAnimationController*								m_pAnimationController;

private:
	void SetupSkinnedMesh(ST_BONE* pBone);

private:
	void UpdateSkinnedMesh(ST_BONE* pBone);

private:
	void RenderSkinnedMesh(ST_BONE* pBone);

private:
	void RenderBones(ST_BONE* pBone, D3DXMATRIXA16* pMatWorld);
	void RenderBoneLines(ST_BONE* pBone, ST_BONE* pParent, D3DXMATRIXA16* matWorld);

public:
	cSkinnedMesh();
	virtual ~cSkinnedMesh();

	virtual void Setup(const CHAR* pFolderName, const CHAR* pFileName);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

