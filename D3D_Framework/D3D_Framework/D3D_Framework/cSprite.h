#pragma once

class cSprite
{
private:
	ID3DXSprite*											m_pSprite;
	IDirect3DTexture9*										m_pTexture;

private:
	D3DXIMAGE_INFO											m_sImgInfo;

private:
	RECT													m_sRect;

	float													m_fStartX;
	float													m_fStartY;
	int														m_nWidth;
	int														m_nHeight;

private:
	int														m_nMaxFrameX;
	int														m_nMaxFrameY;
	int														m_nCurFrameX;
	int														m_nCurFrameY;
	int														m_nFrameW;
	int														m_nFrameH;

public:
	cSprite();
	~cSprite();

	void CreateSprite(const CHAR* pTextureFileName);
	void CreateSprite(const CHAR* pTextureFileName, float fStartX, float fStartY);

	void CreateFrameSprite(const CHAR* pTextureFileName, int nMaxFrameX, int nMaxFrameY);
	void CreateFrameSprite(const CHAR* pTextureFileName, float fStartX, float fStartY, int nMaxFrameX, int nMaxFrameY);

	void Release();

	void Render(D3DXMATRIXA16* pMatWorld = NULL);
	void Render(int nSrcX, int nSrcY, int nSrcW, int nSrcH, D3DXMATRIXA16* pMatWorld = NULL);

	void FrameRender(D3DXMATRIXA16* pMatWorld = NULL);
	void FrameRender(int nCurFrameX, int nCurFrameY, D3DXMATRIXA16* pMatWorld = NULL);

	//

	inline int GetCurFrameX() { return m_nCurFrameX; }
	inline int GetCurFrameY() { return m_nCurFrameY; }
	inline int GetMaxFrameX() { return m_nMaxFrameX; }
	inline int GetMaxFrameY() { return m_nMaxFrameY; }
	inline int GetWidth() { return m_nWidth; }
	inline int GetHeight() { return m_nHeight; }

	//

	inline void SetCurFrameX(int nCurFrameX) { m_nCurFrameX = nCurFrameX; }
	inline void SetCurFrameY(int nCurFrameY) { m_nCurFrameY = nCurFrameY; }
};

