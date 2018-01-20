#pragma once

class cTexMtl
{
private:
	D_SYNTHESIZE(IDirect3DTexture9*, m_pTex, Tex);
	D_SYNTHESIZE_REF(D3DMATERIAL9, m_sMtl, Mtl);

public:
	cTexMtl();
	~cTexMtl();

	void Release();
	void CreateTexture(const CHAR* pTexFileName);
};

