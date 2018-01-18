#pragma once
#include "cSingletonBase.h"

class cImage;

class cImageManager : public cSingletonBase<cImageManager>
{
private:
	typedef std::map<std::string, cImage*>					mapImage;
	typedef std::map<std::string, cImage*>::iterator		mapImageIter;

private:
	mapImage												m_mapImages;

public:
	cImageManager();
	virtual ~cImageManager();

	void Setup();
	void Release();

	cImage* AddImage(std::string strImageKey, int nWidth, int nHeight, BOOL bIsBlend);
	cImage* AddImage(std::string strImageKey, const CHAR* pImageFileName, int nWidth, int nHeight, 
		BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans);
	cImage* AddImage(std::string strImageKey, const CHAR* pImageFileName, float fStartX, float fStartY, int nWidth, int nHeight,
		BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans);

	cImage* AddImage(std::string strImageKey, const CHAR* pImageFileName, int nWidth, int nHeight,
		int nMaxFrameX, int nMaxFrameY, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans);
	cImage* AddImage(std::string strImageKey, const CHAR* pImageFileName, float fStartX, float fStartY, int nWidth, int nHeight,
		int nMaxFrameX, int nMaxFrameY, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans);

	cImage* FindImage(std::string strImageKey);
	BOOL DestroyImage(std::string strImageKey);
	BOOL DestroyAll();

	void Render(std::string strImageKey, HDC hdc, int nDstX, int nDstY);
	void Render(std::string strImageKey, HDC hdc, int nDstX, int nDstY, int nSrcX, int nSrcY, int nSrcW, int nSrcH);

	void FrameRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY);
	void FrameRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY, int nCurFrameX, int nCurFrameY);

	void AlphaRender(std::string strImageKey, HDC hdc, BYTE uchAlpha);
	void AlphaRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY, BYTE uchAlpha);
	void AlphaRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY, int nSrcX, int nSrcY, int nSrcW, int nSrcH, BYTE uchAlpha);

	void AlphaFrameRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY, BYTE uchAlpha);
	void AlphaFrameRender(std::string strImageKey, HDC hdc, int nDstX, int nDstY, int nCurFrameX, int nCurFrameY, BYTE uchAlpha);
};

