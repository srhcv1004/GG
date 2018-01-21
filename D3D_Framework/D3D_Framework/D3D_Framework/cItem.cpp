#include "stdafx.h"
#include "cItem.h"
#include "cSkinnedMesh.h"

// ======================================================================

cXItem::cXItem()
	: m_pXItem(NULL)
{
}

cXItem::~cXItem()
{
}

void cXItem::Setup(const CHAR* pFolderName, const CHAR* pFileName)
{
	m_pXItem = new cSkinnedMesh();
	m_pXItem->Setup(pFolderName, pFileName);
}

void cXItem::Release()
{
	cItem::Release();

	D_SAFE_RELEASE(m_pXItem);
	D_SAFE_DELETE(m_pXItem);
}

// ======================================================================



// ======================================================================

cBasicItem::cBasicItem()
{
}

cBasicItem::~cBasicItem()
{
}

void cBasicItem::Setup()
{
}

void cBasicItem::Release()
{
}

// ======================================================================