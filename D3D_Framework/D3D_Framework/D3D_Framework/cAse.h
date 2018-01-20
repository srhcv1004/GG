#pragma once

class cTexMtl;

class cAse
{
protected:
	D_SYNTHESIZE_REF(std::vector<ST_PNT_VERTEX>, m_vecVertex, VecVertex);
	D_SYNTHESIZE(cTexMtl*, m_pTexMtl, TexMtl);

public:
	cAse();
	virtual ~cAse();

	virtual void Setup();
	virtual void Release();
	virtual void Render();
};

