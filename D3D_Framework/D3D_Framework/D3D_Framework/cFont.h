#pragma once

class cFont
{
private:
	D3DXFONT_DESC											m_sFontDesc;
	ID3DXFont*												m_pFont;

public:
	cFont();
	~cFont();

	void Setup(const CHAR* pFontFileName, INT  nHeight, UINT nWidth, 
		UINT nWeight   = FW_BOLD,		  BOOL bIsItalic		 = FALSE,
		BYTE chCharSet = DEFAULT_CHARSET, BYTE chOutputPercision = OUT_DEFAULT_PRECIS,
		BYTE chQuality = DEFAULT_QUALITY, BYTE chPitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE);
	void Release();

	D3DXFONT_DESC GetFontDesc() { return m_sFontDesc; }
	void SetFontDesc(D3DXFONT_DESC sFontDesc) { m_sFontDesc = sFontDesc; }

	ID3DXFont* GetFont() { return m_pFont; }
	void SetFont(ID3DXFont* pFont) { m_pFont = pFont; }
};

