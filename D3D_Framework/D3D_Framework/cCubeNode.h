#pragma once
#include "cCube.h"

class cCubeNode : public cCubePNT
{
protected:
	std::vector<cCubeNode*>									m_vecChild;

protected:
	D_SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM)
	D3DXMATRIXA16											m_matLocalTM;
	D3DXMATRIXA16											m_matWorldTM;

protected:
	D3DXVECTOR3												m_vLocalPos;

protected:
	D_SYNTHESIZE(float, m_fAniDeltaX, AniDeltaX)
	float													m_fAniRotX;
	int														m_nAniFrameCount;

public:
	cCubeNode();
	virtual ~cCubeNode();

	void Setup();
	void Release();
	void Update();
	void Render();

	void AddChild(cCubeNode* pChild);
	void KeyAnimation();
	void ActionAnimation();
};

