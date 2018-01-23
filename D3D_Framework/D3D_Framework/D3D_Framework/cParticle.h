#pragma once

class cParticle
{
public:
	enum E_SETUP_KIND
	{
		E_SETUP_CIRCLE,
		E_SETUP_COLUMN,
		E_SETUP_SQUARE,
		E_SETUP_DEFAULT
	};

	enum E_UPDATE_KIND
	{
		E_UPDATE_TOIN_CIRCLE,
		E_UPDATE_TOOUT_CIRCLE,
		E_UPDATE_DROP,
		E_UPDATE_DEFAULT
	};

private:
	IDirect3DTexture9*									m_pTexture;

private:
	std::vector<ST_PC_VERTEX>							m_vecPaticle;
	std::vector<ST_PC_VERTEX>							m_vecSnow;

public:
	cParticle();
	~cParticle();

	void Setup(const CHAR* pTextureFileName, int nVecSize, E_SETUP_KIND eKind);
	void Release();
	void Update();
	void Render();
};

