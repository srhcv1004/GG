#include "stdafx.h"
#include "cSpriteManager.h"
#include "cSprite.h"

cSpriteManager::cSpriteManager()
{
}

cSpriteManager::~cSpriteManager()
{
}

void cSpriteManager::Setup()
{
}

void cSpriteManager::Release()
{
	this->DestroyAll();
}

cSprite * cSpriteManager::AddSprite(std::string strSpriteKey, const CHAR * pSpriteFileName)
{
	cSprite* pSprite = this->FindSprite(strSpriteKey);

	if (pSprite) return pSprite;

	pSprite = new cSprite();
	pSprite->CreateSprite(pSpriteFileName);

	m_mapSprites.insert(std::make_pair(strSpriteKey, pSprite));
	return pSprite;
}

cSprite * cSpriteManager::AddSprite(std::string strSpriteKey, const CHAR * pSpriteFileName, float fStartX, float fStartY)
{
	cSprite* pSprite = this->FindSprite(strSpriteKey);

	if (pSprite) return pSprite;

	pSprite = new cSprite();
	pSprite->CreateSprite(pSpriteFileName, fStartX, fStartY);

	m_mapSprites.insert(std::make_pair(strSpriteKey, pSprite));
	return pSprite;
}

cSprite * cSpriteManager::AddFrameSprite(std::string strSpriteKey, const CHAR * pSpriteFileName, int nMaxFrameX, int nMaxFrameY)
{
	cSprite* pSprite = this->FindSprite(strSpriteKey);

	if (pSprite) return pSprite;

	pSprite = new cSprite();
	pSprite->CreateFrameSprite(pSpriteFileName, nMaxFrameX, nMaxFrameY);

	m_mapSprites.insert(std::make_pair(strSpriteKey, pSprite));
	return pSprite;
}

cSprite * cSpriteManager::AddFrameSprite(std::string strSpriteKey, const CHAR * pSpriteFileName, float fStartX, float fStartY, int nMaxFrameX, int nMaxFrameY)
{
	cSprite* pSprite = this->FindSprite(strSpriteKey);

	if (pSprite) return pSprite;

	pSprite = new cSprite();
	pSprite->CreateFrameSprite(pSpriteFileName, fStartX, fStartY, nMaxFrameX, nMaxFrameY);

	m_mapSprites.insert(std::make_pair(strSpriteKey, pSprite));
	return pSprite;
}

cSprite * cSpriteManager::FindSprite(std::string strSpriteKey)
{
	mapSpriteIter mapFind = m_mapSprites.find(strSpriteKey);

	if (mapFind != m_mapSprites.end())
	{
		if (mapFind->second)
		{
			return mapFind->second;
		}
	}

	return NULL;
}

BOOL cSpriteManager::DestroySprite(std::string strSpriteKey)
{
	mapSpriteIter mapFind = m_mapSprites.find(strSpriteKey);

	if (mapFind != m_mapSprites.end())
	{
		if (mapFind->second)
		{
			D_SAFE_RELEASE(mapFind->second);
			D_SAFE_DELETE(mapFind->second);
			m_mapSprites.erase(mapFind);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL cSpriteManager::DestroyAll()
{
	mapSpriteIter mapFind = m_mapSprites.begin();

	for (mapFind; mapFind != m_mapSprites.end();)
	{
		if (mapFind->second)
		{
			D_SAFE_RELEASE(mapFind->second);
			D_SAFE_DELETE(mapFind->second);
			mapFind = m_mapSprites.erase(mapFind);
		}
		else mapFind++;
	}

	return TRUE;
}

void cSpriteManager::Render(std::string strSpriteKey, D3DXMATRIXA16* pMatWorld)
{
	cSprite* pSprite = this->FindSprite(strSpriteKey);

	if (pSprite) pSprite->Render(pMatWorld);
}

void cSpriteManager::Render(std::string strSpriteKey, int nSrcX, int nSrcY, int nSrcW, int nSrcH, D3DXMATRIXA16* pMatWorld)
{
	cSprite* pSprite = this->FindSprite(strSpriteKey);

	if (pSprite) pSprite->Render(nSrcX, nSrcY, nSrcW, nSrcH, pMatWorld);
}

void cSpriteManager::FrameRender(std::string strSpriteKey, D3DXMATRIXA16* pMatWorld)
{
	cSprite* pSprite = this->FindSprite(strSpriteKey);

	if (pSprite) pSprite->FrameRender(pMatWorld);
}

void cSpriteManager::FrameRender(std::string strSpriteKey, int nCurFrameX, int nCurFrameY, D3DXMATRIXA16* pMatWorld)
{
	cSprite* pSprite = this->FindSprite(strSpriteKey);

	if (pSprite) pSprite->FrameRender(nCurFrameX, nCurFrameY, pMatWorld);
}
