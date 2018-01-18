#pragma once

class cImage
{
public:
	enum E_IMAGE_LOAD_KIND
	{
		E_LOAD_EMPTY,
		E_LOAD_RESOURCE,
		E_LOAD_FILE,
		E_LOAD_END = 3
	};

public:
	struct ST_IMAGE_INFO
	{
		DWORD												ulResID;
		HDC													hMemDC;
		HBITMAP												hBit;
		HBITMAP												hOBit;

		float												fStartX;
		float												fStartY;
		int													nWidth;
		int													nHeight;

		int													nMaxFrameX;
		int													nMaxFrameY;
		int													nCurFrameX;
		int													nCurFrameY;
		int													nFrameW;
		int													nFrameH;

		BYTE												uchLoadKind;

		ST_IMAGE_INFO()
			: ulResID(0)
			, hMemDC(NULL)
			, hBit(NULL)
			, hOBit(NULL)
			, fStartX(0.F)
			, fStartY(0.F)
			, nWidth(0)
			, nHeight(0)
			, nMaxFrameX(0)
			, nMaxFrameY(0)
			, nCurFrameX(0)
			, nCurFrameY(0)
			, nFrameW(0)
			, nFrameH(0)
			, uchLoadKind(E_LOAD_EMPTY)
		{

		}
	};

private:
	ST_IMAGE_INFO*											m_pImageInfo;
	ST_IMAGE_INFO*											m_pBlendImageInfo;

private:
	CHAR*													m_pImageFileName;

private:
	BOOL													m_bIsTrans;
	BOOL													m_bIsBlend;

private:
	BLENDFUNCTION											m_sBlendFunc;
	COLORREF												m_colorTrans;

public:
	cImage();
	~cImage();

	void Setup(int nWidth, int nHeight, BOOL bIsBlend);
	void Setup(const CHAR* pImageFileName, int nWidth, int nHeight, 
		BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans);
	void Setup(const CHAR* pImageFileName, float fStartX, float fStartY, int nWidth, int nHeight,
		BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans);

	void Setup(const CHAR* pImageFileName, int nWidth, int nHeight,
		int nMaxFrameX, int nMaxFrameY, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans);
	void Setup(const CHAR* pImageFileName, float fStartX, float fStartY, int nWidth, int nHeight,
		int nMaxFrameX, int nMaxFrameY, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans);

	void Release();
	void SetTransColor(BOOL bIsTrans, COLORREF colorTrans);

	void Render(HDC hdc, int nDstX, int nDstY);
	void Render(HDC hdc, int nDstX, int nDstY, int nSrcX, int nSrcY, int nSrcW, int nSrcH);

	void FrameRender(HDC hdc, int nDstX, int nDstY);
	void FrameRender(HDC hdc, int nDstX, int nDstY, int nCurFrameX, int nCurFrameY);

	void AlphaRender(HDC hdc, BYTE uchAlpha);
	void AlphaRender(HDC hdc, int nDstX, int nDstY, BYTE uchAlpha);
	void AlphaRender(HDC hdc, int nDstX, int nDstY, int nSrcX, int nSrcY, int nSrcW, int nSrcH, BYTE uchAlpha);

	void AlphaFrameRender(HDC hdc, int nDstX, int nDstY, BYTE uchAlpha);
	void AlphaFrameRender(HDC hdc, int nDstX, int nDstY, int nCurFrameX, int nCurFrameY, BYTE uchAlpha);

	// ----------------------------------------------------------------------------------------------------

	inline HDC GetMemDC() { return m_pImageInfo->hMemDC; }
	inline float GetStartX() { return m_pImageInfo->fStartX; }
	inline float GetStartY() { return m_pImageInfo->fStartY; }
	inline float GetCenterX()
	{
		return m_pImageInfo->nMaxFrameX <= 0 ? m_pImageInfo->fStartX + (float)m_pImageInfo->nWidth / 2.F :
			m_pImageInfo->fStartX + (float)m_pImageInfo->nFrameW / 2.F;
	}
	inline float GetCenterY()
	{
		return m_pImageInfo->nMaxFrameY <= 0 ? m_pImageInfo->fStartY + (float)m_pImageInfo->nHeight / 2.F :
			m_pImageInfo->fStartY + (float)m_pImageInfo->nFrameH / 2.F;
	}

	inline int GetWidth() { return m_pImageInfo->nWidth; }
	inline int GetHeight() { return m_pImageInfo->nHeight; }

	inline int GetMaxFrameX() { return m_pImageInfo->nMaxFrameX; }
	inline int GetMaxFrameY() { return m_pImageInfo->nMaxFrameY; }
	inline int GetCurFrameX() { return m_pImageInfo->nCurFrameX; }
	inline int GetCurFrameY() { return m_pImageInfo->nCurFrameY; }
	inline int GetFrameW() { return m_pImageInfo->nFrameW; }
	inline int GetFrameH() { return m_pImageInfo->nFrameH; }

	// ----------------------------------------------------------------------------------------------------



	// ----------------------------------------------------------------------------------------------------
	inline void SetStartX(float fStartX) { m_pImageInfo->fStartX = fStartX; }
	inline void SetStartY(float fStartY) { m_pImageInfo->fStartY = fStartY; }
	inline void SetCenter(float fCenterX, float fCenterY)
	{
		m_pImageInfo->fStartX = fCenterX - (float)m_pImageInfo->nWidth / 2.F;
		m_pImageInfo->fStartY = fCenterY - (float)m_pImageInfo->nHeight / 2.F;
	}

	inline void SetCurFrameX(int nCurFrameX)
	{
		m_pImageInfo->nCurFrameX = nCurFrameX;
		if (m_pImageInfo->nMaxFrameX < nCurFrameX) m_pImageInfo->nCurFrameX = m_pImageInfo->nMaxFrameX;
	}
	inline void SetCurFrameY(int nCurFrameY)
	{
		m_pImageInfo->nCurFrameY = nCurFrameY;
		if (m_pImageInfo->nMaxFrameY < nCurFrameY) m_pImageInfo->nCurFrameY = m_pImageInfo->nMaxFrameY;
	}
	// ----------------------------------------------------------------------------------------------------
};

