#pragma once

class cSkinnedMesh
{
protected:
	D_SYNTHESIZE(D3DXFRAME*, m_pRootBone, RootBone);

protected:
	ID3DXMesh*												m_pSphere;

protected:
	ID3DXAnimationController*								m_pAnimationController;

protected:
	D_SYNTHESIZE(D3DXMATRIXA16*, m_pMatWorldPtr, MatWorldPtr);

protected:
	float													m_fPassedBlendTime;
	float													m_fBlendTime;
	bool													m_bIsBlend;

private:
	void SetupSkinnedMesh(ST_BONE* pBone);

private:
	void UpdateSkinnedMesh(ST_BONE* pBone);

private:
	void RenderSkinnedMesh(ST_BONE* pBone);

private:
	void RenderBones(ST_BONE* pBone, D3DXMATRIXA16* pMatWorld);
	void RenderBoneLines(ST_BONE* pBone, ST_BONE* pParent, D3DXMATRIXA16* matWorld);

protected:
	void UpdateAnimation();

public:
	cSkinnedMesh();
	virtual ~cSkinnedMesh();

	virtual void Setup(const CHAR* pFolderName, const CHAR* pFileName);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);

};

