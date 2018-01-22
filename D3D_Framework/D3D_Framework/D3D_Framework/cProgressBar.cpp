#include "stdafx.h"
#include "cProgressBar.h"

cProgressBar::cProgressBar()
	: m_pFrontBar(NULL)
	, m_pBackBar(NULL)
	, m_fStartX(0.F)
	, m_fStartY(0.F)
	, m_fWidth(0.F)
	, m_fHeight(0.F)
{
}

cProgressBar::~cProgressBar()
{
}

void cProgressBar::Setup(std::string strFrontBarKey, const CHAR* pFrontBarFileName,
						 std::string strBackBarKey,  const CHAR* pBackBarFileName, 
						 float fStartX, float fStartY, int fWidth, int fHeight)
{
	m_fStartX = fStartX;
	m_fStartY = fStartY;
	m_fWidth  = fWidth;
	m_fHeight = fHeight;

	m_pFrontBar = D_SPRITEMANAGER->AddSprite(strFrontBarKey, 
		pFrontBarFileName, 
		m_fStartX,
		m_fStartY);

	m_pBackBar = D_SPRITEMANAGER->AddSprite(strBackBarKey,
		pBackBarFileName,
		m_fStartX,
		m_fStartY);
}

void cProgressBar::Release()
{
}

void cProgressBar::Update()
{
}

void cProgressBar::Render()
{
	m_pBackBar->Render(0, 0,
		m_pBackBar->GetWidth(), m_pBackBar->GetHeight());

	m_pFrontBar->Render(0, 0,
		m_fWidth, m_fHeight);
}
