#include "stdafx.h"
#include "cImage.h"

cImage::cImage()
	: m_pImageInfo(NULL)
	, m_pBlendImageInfo(NULL)
	, m_pImageFileName(NULL)
	, m_bIsTrans(FALSE)
	, m_bIsBlend(FALSE)
	, m_sBlendFunc()
{
}

cImage::~cImage()
{
}

void cImage::Setup(int nWidth, int nHeight, BOOL bIsBlend)
{
	if (m_pImageInfo) this->Release();

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo						= new ST_IMAGE_INFO();
	m_pImageInfo->ulResID				= 0;
	m_pImageInfo->uchLoadKind			= E_LOAD_EMPTY;
	m_pImageInfo->hMemDC				= CreateCompatibleDC(hdc);
	m_pImageInfo->hBit					= (HBITMAP)CreateCompatibleBitmap(hdc, nWidth, nHeight);
	m_pImageInfo->hOBit					= (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth				= nWidth;
	m_pImageInfo->nHeight				= nHeight;

	m_pImageFileName = NULL;
	m_bIsTrans		 = FALSE;
	m_colorTrans	 = RGB(0, 0, 0);

	if (!m_pImageInfo->hBit)
	{
		this->Release();
		return;
	}

	m_bIsBlend = bIsBlend;
	if (m_bIsBlend)
	{
		m_sBlendFunc.AlphaFormat		= 0;
		m_sBlendFunc.BlendFlags			= 0;
		m_sBlendFunc.BlendOp			= AC_SRC_OVER;

		m_pBlendImageInfo				= new ST_IMAGE_INFO();
		m_pBlendImageInfo->ulResID		= 0;
		m_pBlendImageInfo->uchLoadKind	= E_LOAD_EMPTY;
		m_pBlendImageInfo->hMemDC		= CreateCompatibleDC(hdc);
		m_pBlendImageInfo->hBit			= (HBITMAP)CreateCompatibleBitmap(hdc, D_WINSIZEX, D_WINSIZEY);
		m_pBlendImageInfo->hOBit		= (HBITMAP)SelectObject(m_pBlendImageInfo->hMemDC, m_pBlendImageInfo->hBit);
		m_pBlendImageInfo->nWidth		= D_WINSIZEX;
		m_pBlendImageInfo->nHeight		= D_WINSIZEY;

		if (!m_pBlendImageInfo->hBit)
		{
			this->Release();
			return;
		}
	}

	ReleaseDC(g_hWnd, hdc);
}

void cImage::Setup(const CHAR * pImageFileName, int nWidth, int nHeight, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans)
{
	if (!pImageFileName) return;
	if (m_pImageInfo) this->Release();

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo						= new ST_IMAGE_INFO();
	m_pImageInfo->ulResID				= 0;
	m_pImageInfo->uchLoadKind			= E_LOAD_FILE;
	m_pImageInfo->hMemDC				= CreateCompatibleDC(hdc);
	m_pImageInfo->hBit					= (HBITMAP)LoadImage(g_hInstance, pImageFileName, IMAGE_BITMAP, nWidth, nHeight, LR_LOADFROMFILE);
	m_pImageInfo->hOBit					= (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth				= nWidth;
	m_pImageInfo->nHeight				= nHeight;

	int nLen = strlen(pImageFileName) + 1;

	m_pImageFileName = new CHAR[nLen]();
	m_bIsTrans		 = bIsTrans;
	m_colorTrans	 = colorTrans;

	strncpy_s(m_pImageFileName, nLen, pImageFileName, nLen);

	if (!m_pImageInfo->hBit)
	{
		this->Release();
		return;
	}

	m_bIsBlend = bIsBlend;
	if (m_bIsBlend)
	{
		m_sBlendFunc.AlphaFormat		= 0;
		m_sBlendFunc.BlendFlags			= 0;
		m_sBlendFunc.BlendOp			= AC_SRC_OVER;

		m_pBlendImageInfo				= new ST_IMAGE_INFO();
		m_pBlendImageInfo->ulResID		= 0;
		m_pBlendImageInfo->uchLoadKind	= E_LOAD_EMPTY;
		m_pBlendImageInfo->hMemDC		= CreateCompatibleDC(hdc);
		m_pBlendImageInfo->hBit			= (HBITMAP)CreateCompatibleBitmap(hdc, D_WINSIZEX, D_WINSIZEY);
		m_pBlendImageInfo->hOBit		= (HBITMAP)SelectObject(m_pBlendImageInfo->hMemDC, m_pBlendImageInfo->hBit);
		m_pBlendImageInfo->nWidth		= D_WINSIZEX;
		m_pBlendImageInfo->nHeight		= D_WINSIZEY;

		if (!m_pBlendImageInfo->hBit)
		{
			this->Release();
			return;
		}
	}

	ReleaseDC(g_hWnd, hdc);
}

void cImage::Setup(const CHAR * pImageFileName, float fStartX, float fStartY, int nWidth, int nHeight, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans)
{
	if (!pImageFileName) return;
	if (m_pImageInfo) this->Release();

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo						= new ST_IMAGE_INFO();
	m_pImageInfo->ulResID				= 0;
	m_pImageInfo->uchLoadKind			= E_LOAD_FILE;
	m_pImageInfo->hMemDC				= CreateCompatibleDC(hdc);
	m_pImageInfo->hBit					= (HBITMAP)LoadImage(g_hInstance, pImageFileName, IMAGE_BITMAP, nWidth, nHeight, LR_LOADFROMFILE);
	m_pImageInfo->hOBit					= (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth				= nWidth;
	m_pImageInfo->nHeight				= nHeight;
	m_pImageInfo->fStartX				= fStartX;
	m_pImageInfo->fStartY				= fStartY;

	int nLen = strlen(pImageFileName) + 1;

	m_pImageFileName = new CHAR[nLen]();
	m_bIsTrans		 = bIsTrans;
	m_colorTrans	 = colorTrans;

	strncpy_s(m_pImageFileName, nLen, pImageFileName, nLen);

	if (!m_pImageInfo->hBit)
	{
		this->Release();
		return;
	}

	m_bIsBlend = bIsBlend;
	if (m_bIsBlend)
	{
		m_sBlendFunc.AlphaFormat		= 0;
		m_sBlendFunc.BlendFlags			= 0;
		m_sBlendFunc.BlendOp			= AC_SRC_OVER;

		m_pBlendImageInfo				= new ST_IMAGE_INFO();
		m_pBlendImageInfo->ulResID		= 0;
		m_pBlendImageInfo->uchLoadKind	= E_LOAD_EMPTY;
		m_pBlendImageInfo->hMemDC		= CreateCompatibleDC(hdc);
		m_pBlendImageInfo->hBit			= (HBITMAP)CreateCompatibleBitmap(hdc, D_WINSIZEX, D_WINSIZEY);
		m_pBlendImageInfo->hOBit		= (HBITMAP)SelectObject(m_pBlendImageInfo->hMemDC, m_pBlendImageInfo->hBit);
		m_pBlendImageInfo->nWidth		= D_WINSIZEX;
		m_pBlendImageInfo->nHeight		= D_WINSIZEY;

		if (!m_pBlendImageInfo->hBit)
		{
			this->Release();
			return;
		}
	}

	ReleaseDC(g_hWnd, hdc);
}

void cImage::Setup(const CHAR * pImageFileName, int nWidth, int nHeight, int nMaxFrameX, int nMaxFrameY, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans)
{
	if (!pImageFileName) return;
	if (m_pImageInfo) this->Release();

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo						= new ST_IMAGE_INFO();
	m_pImageInfo->ulResID				= 0;
	m_pImageInfo->uchLoadKind			= E_LOAD_FILE;
	m_pImageInfo->hMemDC				= CreateCompatibleDC(hdc);
	m_pImageInfo->hBit					= (HBITMAP)LoadImage(g_hInstance, pImageFileName, IMAGE_BITMAP, nWidth, nHeight, LR_LOADFROMFILE);
	m_pImageInfo->hOBit					= (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth				= nWidth;
	m_pImageInfo->nHeight				= nHeight;

	m_pImageInfo->nMaxFrameX			= nMaxFrameX - 1;
	m_pImageInfo->nMaxFrameY			= nMaxFrameY - 1;
	m_pImageInfo->nFrameW				= nWidth / nMaxFrameX;
	m_pImageInfo->nFrameH				= nHeight / nMaxFrameY;

	int nLen = strlen(pImageFileName) + 1;

	m_pImageFileName = new CHAR[nLen]();
	m_bIsTrans		 = bIsTrans;
	m_colorTrans	 = colorTrans;

	strncpy_s(m_pImageFileName, nLen, pImageFileName, nLen);

	if (!m_pImageInfo->hBit)
	{
		this->Release();
		return;
	}

	m_bIsBlend = bIsBlend;
	if (m_bIsBlend)
	{
		m_sBlendFunc.AlphaFormat		= 0;
		m_sBlendFunc.BlendFlags			= 0;
		m_sBlendFunc.BlendOp			= AC_SRC_OVER;

		m_pBlendImageInfo				= new ST_IMAGE_INFO();
		m_pBlendImageInfo->ulResID		= 0;
		m_pBlendImageInfo->uchLoadKind	= E_LOAD_EMPTY;
		m_pBlendImageInfo->hMemDC		= CreateCompatibleDC(hdc);
		m_pBlendImageInfo->hBit			= (HBITMAP)CreateCompatibleBitmap(hdc, D_WINSIZEX, D_WINSIZEY);
		m_pBlendImageInfo->hOBit		= (HBITMAP)SelectObject(m_pBlendImageInfo->hMemDC, m_pBlendImageInfo->hBit);
		m_pBlendImageInfo->nWidth		= D_WINSIZEX;
		m_pBlendImageInfo->nHeight		= D_WINSIZEY;

		if (!m_pBlendImageInfo->hBit)
		{
			this->Release();
			return;
		}
	}

	ReleaseDC(g_hWnd, hdc);
}

void cImage::Setup(const CHAR * pImageFileName, float fStartX, float fStartY, int nWidth, int nHeight, int nMaxFrameX, int nMaxFrameY, BOOL bIsBlend, BOOL bIsTrans, COLORREF colorTrans)
{
	if (!pImageFileName) return;
	if (m_pImageInfo) this->Release();

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo						= new ST_IMAGE_INFO();
	m_pImageInfo->ulResID				= 0;
	m_pImageInfo->uchLoadKind			= E_LOAD_FILE;
	m_pImageInfo->hMemDC				= CreateCompatibleDC(hdc);
	m_pImageInfo->hBit					= (HBITMAP)LoadImage(g_hInstance, pImageFileName, IMAGE_BITMAP, nWidth, nHeight, LR_LOADFROMFILE);
	m_pImageInfo->hOBit					= (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth				= nWidth;
	m_pImageInfo->nHeight				= nHeight;
	m_pImageInfo->fStartX				= fStartX;
	m_pImageInfo->fStartY				= fStartY;

	m_pImageInfo->nMaxFrameX			= nMaxFrameX - 1;
	m_pImageInfo->nMaxFrameY			= nMaxFrameY - 1;
	m_pImageInfo->nFrameW				= nWidth / nMaxFrameX;
	m_pImageInfo->nFrameH				= nHeight / nMaxFrameY;

	int nLen = strlen(pImageFileName) + 1;

	m_pImageFileName = new CHAR[nLen]();
	m_bIsTrans		 = bIsTrans;
	m_colorTrans	 = colorTrans;

	strncpy_s(m_pImageFileName, nLen, pImageFileName, nLen);

	if (!m_pImageInfo->hBit)
	{
		this->Release();
		return;
	}

	m_bIsBlend = bIsBlend;
	if (m_bIsBlend)
	{
		m_sBlendFunc.AlphaFormat		= 0;
		m_sBlendFunc.BlendFlags			= 0;
		m_sBlendFunc.BlendOp			= AC_SRC_OVER;

		m_pBlendImageInfo				= new ST_IMAGE_INFO();
		m_pBlendImageInfo->ulResID		= 0;
		m_pBlendImageInfo->uchLoadKind	= E_LOAD_EMPTY;
		m_pBlendImageInfo->hMemDC		= CreateCompatibleDC(hdc);
		m_pBlendImageInfo->hBit			= (HBITMAP)CreateCompatibleBitmap(hdc, D_WINSIZEX, D_WINSIZEY);
		m_pBlendImageInfo->hOBit		= (HBITMAP)SelectObject(m_pBlendImageInfo->hMemDC, m_pBlendImageInfo->hBit);
		m_pBlendImageInfo->nWidth		= D_WINSIZEX;
		m_pBlendImageInfo->nHeight		= D_WINSIZEY;

		if (!m_pBlendImageInfo->hBit)
		{
			this->Release();
			return;
		}
	}

	ReleaseDC(g_hWnd, hdc);
}

void cImage::Release()
{
	if (m_pImageInfo)
	{
		SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hOBit);
		DeleteObject(m_pImageInfo->hBit);
		DeleteDC(m_pImageInfo->hMemDC);

		D_SAFE_DELETE(m_pImageInfo);
		D_SAFE_DELETE_ARR(m_pImageFileName);

		m_bIsTrans	 = FALSE;
		m_colorTrans = RGB(0, 0, 0);
	}
	
	if (m_pBlendImageInfo)
	{
		SelectObject(m_pBlendImageInfo->hMemDC, m_pBlendImageInfo->hOBit);
		DeleteObject(m_pBlendImageInfo->hBit);
		DeleteDC(m_pBlendImageInfo->hMemDC);

		D_SAFE_DELETE(m_pBlendImageInfo);

		m_bIsBlend	 = FALSE;
		m_sBlendFunc = {};
	}
}

void cImage::SetTransColor(BOOL bIsTrans, COLORREF colorTrans)
{
	m_bIsTrans							= bIsTrans;
	m_colorTrans						= colorTrans;
}

void cImage::Render(HDC hdc, int nDstX, int nDstY)
{
	if (m_bIsTrans)
	{
		GdiTransparentBlt(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_colorTrans);
	}
	else
	{
		BitBlt(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0,
			0,
			SRCCOPY);
	}
}

void cImage::Render(HDC hdc, int nDstX, int nDstY, int nSrcX, int nSrcY, int nSrcW, int nSrcH)
{
	if (m_bIsTrans)
	{
		GdiTransparentBlt(hdc,
			nDstX,
			nDstY,
			nSrcW,
			nSrcH,
			m_pImageInfo->hMemDC,
			nSrcX,
			nSrcY,
			nSrcW,
			nSrcH,
			m_colorTrans);
	}
	else
	{
		BitBlt(hdc,
			nDstX,
			nDstY,
			nSrcW,
			nSrcH,
			m_pImageInfo->hMemDC,
			nSrcX,
			nSrcY,
			SRCCOPY);
	}
}

void cImage::FrameRender(HDC hdc, int nDstX, int nDstY)
{
	if (m_bIsTrans)
	{
		GdiTransparentBlt(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_pImageInfo->hMemDC,
			m_pImageInfo->nFrameW * m_pImageInfo->nCurFrameX,
			m_pImageInfo->nFrameH * m_pImageInfo->nCurFrameY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_colorTrans);
	}
	else
	{
		BitBlt(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_pImageInfo->hMemDC,
			m_pImageInfo->nFrameW * m_pImageInfo->nCurFrameX,
			m_pImageInfo->nFrameH * m_pImageInfo->nCurFrameY,
			SRCCOPY);
	}
}

void cImage::FrameRender(HDC hdc, int nDstX, int nDstY, int nCurFrameX, int nCurFrameY)
{
	m_pImageInfo->nCurFrameX = nCurFrameX;
	m_pImageInfo->nCurFrameY = nCurFrameY;

	if (m_bIsTrans)
	{
		GdiTransparentBlt(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_pImageInfo->hMemDC,
			m_pImageInfo->nFrameW * m_pImageInfo->nCurFrameX,
			m_pImageInfo->nFrameH * m_pImageInfo->nCurFrameY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_colorTrans);
	}
	else
	{
		BitBlt(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_pImageInfo->hMemDC,
			m_pImageInfo->nFrameW * m_pImageInfo->nCurFrameX,
			m_pImageInfo->nFrameH * m_pImageInfo->nCurFrameY,
			SRCCOPY);
	}
}

void cImage::AlphaRender(HDC hdc, BYTE uchAlpha)
{
	if (!m_bIsBlend) return;

	m_sBlendFunc.SourceConstantAlpha	= uchAlpha;

	if (m_bIsTrans)
	{
		BitBlt(m_pBlendImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			hdc,
			(int)m_pImageInfo->fStartX,
			(int)m_pImageInfo->fStartY,
			SRCCOPY);

		GdiTransparentBlt(m_pBlendImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_colorTrans);

		AlphaBlend(hdc,
			(int)m_pImageInfo->fStartX,
			(int)m_pImageInfo->fStartY,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_pBlendImageInfo->hMemDC, 
			0,
			0,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_sBlendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			(int)m_pImageInfo->fStartX,
			(int)m_pImageInfo->fStartY,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_sBlendFunc);
	}
}

void cImage::AlphaRender(HDC hdc, int nDstX, int nDstY, BYTE uchAlpha)
{
	if (!m_bIsBlend) return;

	m_sBlendFunc.SourceConstantAlpha = uchAlpha;

	if (m_bIsTrans)
	{
		BitBlt(m_pBlendImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			hdc,
			nDstX,
			nDstY,
			SRCCOPY);

		GdiTransparentBlt(m_pBlendImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_colorTrans);

		AlphaBlend(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_pBlendImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_sBlendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,
			m_sBlendFunc);
	}
}

void cImage::AlphaRender(HDC hdc, int nDstX, int nDstY, int nSrcX, int nSrcY, int nSrcW, int nSrcH, BYTE uchAlpha)
{
	if (!m_bIsBlend) return;

	m_sBlendFunc.SourceConstantAlpha = uchAlpha;

	if (m_bIsTrans)
	{
		BitBlt(m_pBlendImageInfo->hMemDC,
			0,
			0,
			nSrcW,
			nSrcH,
			hdc,
			nDstX,
			nDstY,
			SRCCOPY);

		GdiTransparentBlt(m_pBlendImageInfo->hMemDC,
			0,
			0,
			nSrcW,
			nSrcH,
			m_pImageInfo->hMemDC,
			nSrcX,
			nSrcY,
			nSrcW,
			nSrcH,
			m_colorTrans);

		AlphaBlend(hdc,
			nDstX,
			nDstY,
			nSrcW,
			nSrcH,
			m_pBlendImageInfo->hMemDC,
			0,
			0,
			nSrcW,
			nSrcH,
			m_sBlendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			nDstX,
			nDstY,
			nSrcW,
			nSrcH,
			m_pImageInfo->hMemDC,
			nSrcX,
			nSrcY,
			nSrcW,
			nSrcH,
			m_sBlendFunc);
	}
}

void cImage::AlphaFrameRender(HDC hdc, int nDstX, int nDstY, BYTE uchAlpha)
{
	if (!m_bIsBlend) return;

	m_sBlendFunc.SourceConstantAlpha = uchAlpha;

	if (m_bIsTrans)
	{
		BitBlt(m_pBlendImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			hdc,
			nDstX,
			nDstY,
			SRCCOPY);

		GdiTransparentBlt(m_pBlendImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_pImageInfo->hMemDC,
			m_pImageInfo->nFrameW * m_pImageInfo->nCurFrameX,
			m_pImageInfo->nFrameH * m_pImageInfo->nCurFrameY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_colorTrans);

		AlphaBlend(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_pBlendImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_sBlendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_pImageInfo->hMemDC,
			m_pImageInfo->nFrameW * m_pImageInfo->nCurFrameX,
			m_pImageInfo->nFrameH * m_pImageInfo->nCurFrameY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_sBlendFunc);
	}
}

void cImage::AlphaFrameRender(HDC hdc, int nDstX, int nDstY, int nCurFrameX, int nCurFrameY, BYTE uchAlpha)
{
	if (!m_bIsBlend) return;

	m_pImageInfo->nCurFrameX = nCurFrameX;
	m_pImageInfo->nCurFrameY = nCurFrameY;

	m_sBlendFunc.SourceConstantAlpha = uchAlpha;

	if (m_bIsTrans)
	{
		BitBlt(m_pBlendImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			hdc,
			nDstX,
			nDstY,
			SRCCOPY);

		GdiTransparentBlt(m_pBlendImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_pImageInfo->hMemDC,
			m_pImageInfo->nFrameW * m_pImageInfo->nCurFrameX,
			m_pImageInfo->nFrameH * m_pImageInfo->nCurFrameY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_colorTrans);

		AlphaBlend(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_pBlendImageInfo->hMemDC,
			0,
			0,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_sBlendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			nDstX,
			nDstY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_pImageInfo->hMemDC,
			m_pImageInfo->nFrameW * m_pImageInfo->nCurFrameX,
			m_pImageInfo->nFrameH * m_pImageInfo->nCurFrameY,
			m_pImageInfo->nFrameW,
			m_pImageInfo->nFrameH,
			m_sBlendFunc);
	}
}
