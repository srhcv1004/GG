#pragma once
#include "cAse.h"

class cAnimation;

class cAseNode : public cAse
{
private:
	D_SYNTHESIZE(cAnimation*, m_pAnimation, Animation);

private:
	std::vector<cAseNode*>									m_vecChild;

private:
	D3DXMATRIXA16											m_matLocalTM;

private:
	D_SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	D_SYNTHESIZE_REF(D3DXMATRIXA16, m_matWorldTM, MatWorldTM);

public:
	cAseNode();
	virtual ~cAseNode();

	virtual void Setup();
	virtual void Release();
	virtual void Update(float* pFrame);
	virtual void Render();

	void AddChild(cAseNode* pChild);
};

