#include "stdafx.h"
#include "cFontManager.h"
#include "cFont.h"

cFontManager::cFontManager()
{
}

cFontManager::~cFontManager()
{
}

void cFontManager::Setup()
{
}

void cFontManager::Release()
{
	this->DestroyFontAll();
}

void cFontManager::AddFont(std::string strFontKey, const CHAR * pFontFileName, INT nHeight, UINT nWidth, 
	UINT nWeight,   BOOL bIsItalic, 
	BYTE chCharSet, BYTE chOutputPercision, 
	BYTE chQuality, BYTE chPitchAndFamily)
{
	cFont* pFont = this->FindFont(strFontKey);

	if (pFont) return;

	pFont = new cFont();
	pFont->Setup(pFontFileName, nHeight, nWidth, nWeight, bIsItalic, chCharSet, chOutputPercision, chQuality, chPitchAndFamily);

	m_mapFonts.insert(std::make_pair(strFontKey, pFont));
}

void cFontManager::DrawFontText(std::string strFontKey, std::string strDrawText, ID3DXSprite * pSprite,
	RECT sRc, D3DCOLOR color)
{
	mapFontIter mapFind = m_mapFonts.find(strFontKey);

	if (mapFind == m_mapFonts.end()) return;

	ID3DXFont* pFont = mapFind->second->GetFont();

	pFont->DrawText(pSprite,
		strDrawText.c_str(),
		strDrawText.length(),
		&sRc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		color);
}

cFont* cFontManager::FindFont(std::string strFontKey)
{
	mapFontIter mapFind = m_mapFonts.find(strFontKey);

	if (mapFind != m_mapFonts.end())
	{
		if (mapFind->second)
			return mapFind->second;
	}

	return NULL;
}

BOOL cFontManager::DestroyFont(std::string strFontKey)
{
	mapFontIter mapFind = m_mapFonts.find(strFontKey);

	if (mapFind != m_mapFonts.end())
	{
		if (mapFind->second)
		{
			D_SAFE_RELEASE(mapFind->second);
			D_SAFE_DELETE(mapFind->second);
			m_mapFonts.erase(mapFind);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL cFontManager::DestroyFontAll()
{
	mapFontIter mapFind = m_mapFonts.begin();

	for (mapFind; mapFind != m_mapFonts.end();)
	{
		if (mapFind->second)
		{
			D_SAFE_RELEASE(mapFind->second);
			D_SAFE_DELETE(mapFind->second);
			mapFind = m_mapFonts.erase(mapFind);
		}
		else mapFind++;
	}

	return FALSE;
}


ID3DXFont* cFontManager::FindID3DXFont(std::string strFontKey)
{
	mapFontIter mapFind = m_mapFonts.find(strFontKey);

	if (mapFind != m_mapFonts.end())
	{
		if (mapFind->second)
			return mapFind->second->GetFont();
	}

	return NULL;
}

