#pragma once
#include "cSprite.h"

class cProgressBar
{
private:
	cSprite*												m_pFrontBar;
	cSprite*												m_pBackBar;

	float													m_fStartX;
	float													m_fStartY;
	float													m_fWidth;
	float													m_fHeight;

public:
	cProgressBar();
	~cProgressBar();

	void Setup(std::string strFrontBarKey, const CHAR* pFrontBarFileName,
			   std::string strBackBarKey,  const CHAR* pBackBarFileName,
			   float fStartX, float fStartY, int nWidth, int nHeight);
	void Release();
	void Update();
	void Render();

	void SetStartX(float fStartX) { m_fStartX = fStartX; }
	void SetStartY(float fStartY) { m_fStartY = fStartY; }

	void SetGuage(float fCurGuage, float fMaxGuage)
	{
		m_fWidth = (fCurGuage / fMaxGuage) * m_pBackBar->GetWidth();
	}
};