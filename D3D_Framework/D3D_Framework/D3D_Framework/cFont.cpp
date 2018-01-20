#include "stdafx.h"
#include "cFont.h"

cFont::cFont()
	: m_sFontDesc()
	, m_pFont(NULL)
{
}


cFont::~cFont()
{
}

void cFont::Setup(const CHAR* pFontFileName, INT nHeight, UINT nWidth, UINT nWeight, BOOL bIsItalic, 
	BYTE chCharSet, BYTE chOutputPercision, BYTE chQuality, BYTE chPitchAndFamily)
{
	ZeroMemory(&m_sFontDesc, sizeof(D3DXFONT_DESC));								
	m_sFontDesc.Height					= nHeight;
	m_sFontDesc.Width					= nWidth;
	m_sFontDesc.Weight					= nWeight;
	m_sFontDesc.MipLevels				= 0;
	m_sFontDesc.Italic					= bIsItalic;
	m_sFontDesc.CharSet					= chCharSet;
	m_sFontDesc.OutputPrecision			= chOutputPercision;
	m_sFontDesc.Quality					=chQuality;
	m_sFontDesc.PitchAndFamily			= chPitchAndFamily;

	std::string strFullName = std::string("MyFonts/") + std::string(pFontFileName) + std::string(".ttf");

	AddFontResource(strFullName.c_str());
	strcpy_s(m_sFontDesc.FaceName, pFontFileName);

	D3DXCreateFontIndirect(D_DEVICE, &m_sFontDesc, &m_pFont);
}

void cFont::Release()
{
	D_SAFE_RELEASE(m_pFont);
}
