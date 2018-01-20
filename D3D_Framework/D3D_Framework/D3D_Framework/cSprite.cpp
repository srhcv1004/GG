#include "stdafx.h"
#include "cSprite.h"

cSprite::cSprite()
	: m_pSprite(NULL)
	, m_pTexture(NULL)
	, m_sRect()
	, m_fStartX(0.F)
	, m_fStartY(0.F)
	, m_nWidth(0)
	, m_nHeight(0)
	, m_nMaxFrameX(0)
	, m_nMaxFrameY(0)
	, m_nCurFrameX(0)
	, m_nCurFrameY(0)
	, m_nFrameW(0)
	, m_nFrameH(0)
{
}

cSprite::~cSprite()
{
}

void cSprite::CreateSprite(const CHAR* pTextureFileName)
{
	ZeroMemory(&m_sImgInfo, sizeof(D3DXIMAGE_INFO));

	D3DXCreateTextureFromFileEx(D_DEVICE,
		pTextureFileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		&m_sImgInfo,
		NULL,
		&m_pTexture);

	m_nWidth = m_sImgInfo.Width;
	m_nHeight = m_sImgInfo.Height;

	D3DXCreateSprite(D_DEVICE, &m_pSprite);
}

void cSprite::CreateSprite(const CHAR* pTextureFileName, float fStartX, float fStartY)
{
	ZeroMemory(&m_sImgInfo, sizeof(D3DXIMAGE_INFO));

	D3DXCreateTextureFromFileEx(D_DEVICE,
		pTextureFileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		&m_sImgInfo,
		NULL,
		&m_pTexture);

	m_nWidth = m_sImgInfo.Width;
	m_nHeight = m_sImgInfo.Height;
	m_fStartX = fStartX;
	m_fStartY = fStartY;

	D3DXCreateSprite(D_DEVICE, &m_pSprite);
}

void cSprite::CreateFrameSprite(const CHAR* pTextureFileName, int nMaxFrameX, int nMaxFrameY)
{
	ZeroMemory(&m_sImgInfo, sizeof(D3DXIMAGE_INFO));

	D3DXCreateTextureFromFileEx(D_DEVICE,
		pTextureFileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		&m_sImgInfo,
		NULL,
		&m_pTexture);

	m_nWidth = m_sImgInfo.Width;
	m_nHeight = m_sImgInfo.Height;

	m_nMaxFrameX = nMaxFrameX - 1;
	m_nMaxFrameY = nMaxFrameY - 1;
	m_nFrameW = m_nWidth / nMaxFrameX;
	m_nFrameH = m_nHeight / nMaxFrameY;

	D3DXCreateSprite(D_DEVICE, &m_pSprite);
}

void cSprite::CreateFrameSprite(const CHAR* pTextureFileName, float fStartX, float fStartY, int nMaxFrameX, int nMaxFrameY)
{
	ZeroMemory(&m_sImgInfo, sizeof(D3DXIMAGE_INFO));

	D3DXCreateTextureFromFileEx(D_DEVICE,
		pTextureFileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		&m_sImgInfo,
		NULL,
		&m_pTexture);

	m_nWidth = m_sImgInfo.Width;
	m_nHeight = m_sImgInfo.Height;

	m_fStartX = fStartX;
	m_fStartY = fStartY;

	m_nMaxFrameX = nMaxFrameX - 1;
	m_nMaxFrameY = nMaxFrameY - 1;
	m_nFrameW = m_nWidth / nMaxFrameX;
	m_nFrameH = m_nHeight / nMaxFrameY;

	D3DXCreateSprite(D_DEVICE, &m_pSprite);
}

void cSprite::Release()
{
	D_SAFE_RELEASE(m_pSprite);
	D_SAFE_RELEASE(m_pTexture);
}

void cSprite::Render(D3DXMATRIXA16* pMatWorld)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	if (pMatWorld)
	{
		m_pSprite->SetTransform(pMatWorld);
	}

	m_pSprite->Draw(m_pTexture,
		&RectMake(0, 0, m_nWidth, m_nHeight),
		&D3DXVECTOR3(m_nWidth / 2, m_nHeight / 2, 0.F),
		NULL,
		D3DCOLOR_XRGB(255, 255, 255));

	m_pSprite->End();
}

void cSprite::Render(int nSrcX, int nSrcY, int nSrcW, int nSrcH, D3DXMATRIXA16* pMatWorld)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	if (pMatWorld)
	{
		m_pSprite->SetTransform(pMatWorld);
	}

	m_pSprite->Draw(m_pTexture,
		&RectMake(nSrcX, nSrcY, nSrcW, nSrcH),
		&D3DXVECTOR3(nSrcW / 2, nSrcH / 2, 0.F),
		NULL,
		D3DCOLOR_XRGB(255, 255, 255));

	m_pSprite->End();
}

void cSprite::FrameRender(D3DXMATRIXA16* pMatWorld)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	if (pMatWorld)
	{
		m_pSprite->SetTransform(pMatWorld);
	}

	m_pSprite->Draw(m_pTexture,
		&RectMake(m_nFrameW * m_nCurFrameX, m_nFrameH * m_nCurFrameY, m_nFrameW, m_nFrameH),
		&D3DXVECTOR3(m_nFrameW / 2, m_nFrameH / 2, 0.F),
		NULL,
		D3DCOLOR_XRGB(255, 255, 255));

	m_pSprite->End();
}

void cSprite::FrameRender(int nCurFrameX, int nCurFrameY, D3DXMATRIXA16* pMatWorld)
{
	m_nCurFrameX = nCurFrameX;
	m_nCurFrameY = nCurFrameY;

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	if (pMatWorld)
	{
		m_pSprite->SetTransform(pMatWorld);
	}

	m_pSprite->Draw(m_pTexture,
		&RectMake(m_nFrameW * m_nCurFrameX, m_nFrameH * m_nCurFrameY, m_nFrameW, m_nFrameH),
		&D3DXVECTOR3(m_nFrameW / 2, m_nFrameH / 2, 0.F),
		NULL,
		D3DCOLOR_XRGB(255, 255, 255));

	m_pSprite->End();
}
