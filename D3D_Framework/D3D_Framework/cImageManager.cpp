#include "stdafx.h"
#include "cImageManager.h"
#include "cImage.h"

cImageManager::cImageManager()
{
}

cImageManager::~cImageManager()
{
}

void cImageManager::Setup()
{
}

void cImageManager::Release()
{
}

cImage * cImageManager::AddImage(std::string strImageKey, int nWidth, int nHeight, BOOL bIsBlend)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) return pImage;

	pImage = new cImage();
	pImage->Setup(nWidth, nHeight, bIsBlend);

	m_mapImages.insert(std::make_pair(strImageKey, pImage));
	return pImage;
}

cImage * cImageManager::AddImage(std::string strImageKey, const CHAR * pImageFileName, int nWidth, int nHeight, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) return pImage;

	pImage = new cImage();
	pImage->Setup(pImageFileName, nWidth, nHeight, bIsBlend, bIsTrans, colorTrans);

	m_mapImages.insert(std::make_pair(strImageKey, pImage));
	return pImage;
}

cImage * cImageManager::AddImage(std::string strImageKey, const CHAR * pImageFileName, float fStartX, float fStartY, int nWidth, int nHeight, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) return pImage;

	pImage = new cImage();
	pImage->Setup(pImageFileName, fStartX, fStartY, nWidth, nHeight, bIsBlend, bIsTrans, colorTrans);

	m_mapImages.insert(std::make_pair(strImageKey, pImage));
	return pImage;
}

cImage * cImageManager::AddImage(std::string strImageKey, const CHAR * pImageFileName, int nWidth, int nHeight, int nMaxFrameX, int nMaxFrameY, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) return pImage;

	pImage = new cImage();
	pImage->Setup(pImageFileName, nWidth, nHeight, nMaxFrameX, nMaxFrameY, bIsBlend, bIsTrans, colorTrans);

	m_mapImages.insert(std::make_pair(strImageKey, pImage));
	return pImage;
}

cImage * cImageManager::AddImage(std::string strImageKey, const CHAR * pImageFileName, float fStartX, float fStartY, int nWidth, int nHeight, int nMaxFrameX, int nMaxFrameY, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) return pImage;

	pImage = new cImage();
	pImage->Setup(pImageFileName, fStartX, fStartY, nWidth, nHeight, nMaxFrameX, nMaxFrameY, bIsBlend, bIsTrans, colorTrans);

	m_mapImages.insert(std::make_pair(strImageKey, pImage));
	return pImage;
}

cImage * cImageManager::FindImage(std::string strImageKey)
{
	mapImageIter mapFind = m_mapImages.find(strImageKey);

	if (mapFind != m_mapImages.end())
	{
		if (mapFind->second)
			return mapFind->second;
	}

	return NULL;
}

BOOL cImageManager::DestroyImage(std::string strImageKey)
{
	mapImageIter mapFind = m_mapImages.find(strImageKey);

	if (mapFind != m_mapImages.end())
	{
		if (mapFind->second)
		{
			D_SAFE_RELEASE(mapFind->second);
			D_SAFE_DELETE(mapFind->second);
			m_mapImages.erase(mapFind);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL cImageManager::DestroyAll()
{
	mapImageIter mapFind = m_mapImages.begin();

	for (mapFind; mapFind != m_mapImages.end();)
	{
		if (mapFind->second)
		{
			D_SAFE_RELEASE(mapFind->second);
			D_SAFE_DELETE(mapFind->second);
			mapFind = m_mapImages.erase(mapFind);
		}
		else mapFind++;
	}

	return TRUE;
}

void cImageManager::Render(std::string strImageKey, HDC hdc, int nDstX, int nDstY)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) pImage->Render(hdc, nDstX, nDstY);
}

void cImageManager::Render(std::string strImageKey, HDC hdc, int nDstX, int nDstY, int nSrcX, int nSrcY, int nSrcW, int nSrcH)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) pImage->Render(hdc, nDstX, nDstY, nSrcX, nSrcY, nSrcW, nSrcH);
}

void cImageManager::FrameRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) pImage->FrameRender(hdc, nDstX, nDstY);
}

void cImageManager::FrameRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY, int nCurFrameX, int nCurFrameY)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) pImage->FrameRender(hdc, nDstX, nDstY, nCurFrameX, nCurFrameY);
}

void cImageManager::AlphaRender(std::string strImageKey, HDC hdc, BYTE uchAlpha)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) pImage->AlphaRender(hdc, uchAlpha);
}

void cImageManager::AlphaRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY, BYTE uchAlpha)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) pImage->AlphaRender(hdc, nDstX, nDstY, uchAlpha);
}

void cImageManager::AlphaRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY, int nSrcX, int nSrcY, int nSrcW, int nSrcH, BYTE uchAlpha)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) pImage->AlphaRender(hdc, nDstX, nDstY, nSrcX, nSrcY, nSrcW, nSrcH, uchAlpha);
}

void cImageManager::AlphaFrameRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY, BYTE uchAlpha)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) pImage->AlphaFrameRender(hdc, nDstX, nDstY, uchAlpha);
}

void cImageManager::AlphaFrameRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY, int nCurFrameX, int nCurFrameY, BYTE uchAlpha)
{
	cImage* pImage = this->FindImage(strImageKey);

	if (pImage) pImage->AlphaFrameRender(hdc, nDstX, nDstY, nCurFrameX, nCurFrameY, uchAlpha);
}
