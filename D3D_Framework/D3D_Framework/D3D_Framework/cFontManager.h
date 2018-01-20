#pragma once
#include "cSingletonBase.h"

class cFont;

class cFontManager : public cSingletonBase<cFontManager>
{
private:
	typedef std::map<std::string, cFont*>					mapFont;
	typedef std::map<std::string, cFont*>::iterator			mapFontIter;

private:
	mapFont													m_mapFonts;

private:
	cFont* FindFont(std::string strFontKey);
	BOOL DestroyFontAll();

public:
	cFontManager();
	virtual ~cFontManager();

	void Setup();
	void Release();

	void AddFont(std::string strFontKey, const CHAR* pFontFileName, INT nHeight, UINT nWidth, 
		UINT nWeight   = FW_BOLD,		  BOOL bIsItalic		 = FALSE, 
		BYTE chCharSet = DEFAULT_CHARSET, BYTE chOutputPercision = OUT_DEFAULT_PRECIS,
		BYTE chQuality = DEFAULT_QUALITY, BYTE chPitchAndFamily	 = DEFAULT_PITCH | FF_DONTCARE);

	BOOL DestroyFont(std::string strFontKey);
	ID3DXFont* FindID3DXFont(std::string strFontKey);

	void DrawFontText(std::string strFontKey, std::string strDrawText, ID3DXSprite* pSprite, 
		RECT sRc, D3DCOLOR color);
};

