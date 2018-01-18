#pragma once
#include "cSingletonBase.h"

class cSprite;

class cSpriteManager : public cSingletonBase<cSpriteManager>
{
private:
	typedef std::map<std::string, cSprite*>					mapSprite;
	typedef std::map<std::string, cSprite*>::iterator		mapSpriteIter;

private:
	mapSprite												m_mapSprites;

private:
	BOOL DestroyAll();

public:
	cSpriteManager();
	virtual ~cSpriteManager();

	void Setup();
	void Release();

	cSprite* AddSprite(std::string strSpriteKey, const CHAR* pSpriteFileName);
	cSprite* AddSprite(std::string strSpriteKey, const CHAR* pSpriteFileName,
		float fStartX, float fStartY);

	cSprite* AddFrameSprite(std::string strSpriteKey, const CHAR* pSpriteFileName,
		int nMaxFrameX, int nMaxFrameY);
	cSprite* AddFrameSprite(std::string strSpriteKey, const CHAR* pSpriteFileName,
		float fStartX, float fStartY, int nMaxFrameX, int nMaxFrameY);

	cSprite* FindSprite(std::string strSpriteKey);

	BOOL DestroySprite(std::string strSpriteKey);

	void Render(std::string strSpriteKey, D3DXMATRIXA16* pMatWorld = NULL);
	void Render(std::string strSpriteKey, int nSrcX, int nSrcY, int nSrcW, int nSrcH, D3DXMATRIXA16* pMatWorld = NULL);

	void FrameRender(std::string strSpriteKey, D3DXMATRIXA16* pMatWorld = NULL);
	void FrameRender(std::string strSpriteKey, int nCurFrameX, int nCurFrameY, D3DXMATRIXA16* pMatWorld = NULL);
};

