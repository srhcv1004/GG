#include "stdafx.h"
#include "cTexMtlManager.h"
#include "cTexMtl.h"

cTexMtlManager::cTexMtlManager()
{
}


cTexMtlManager::~cTexMtlManager()
{
}

void cTexMtlManager::Setup()
{
}

void cTexMtlManager::Release()
{
	this->DestroyAll();
}

void cTexMtlManager::AddTexMtl(std::string strTexMtlKey, cTexMtl* pTexMtl)
{
	mapTexMtlIter mapFind = m_mapTexMtls.find(strTexMtlKey);

	if (mapFind == m_mapTexMtls.end())
	{
		m_mapTexMtls.insert(std::make_pair(strTexMtlKey, pTexMtl));
	}
}

cTexMtl * cTexMtlManager::FindTexMtl(std::string strTexMtlKey)
{
	mapTexMtlIter mapFind = m_mapTexMtls.find(strTexMtlKey);

	if (mapFind != m_mapTexMtls.end())
	{
		if (mapFind->second)
		{
			return mapFind->second;
		}
	}
	return NULL;
}

void cTexMtlManager::ReleaseAll()
{
	mapTexMtlIter mapFind = m_mapTexMtls.begin();

	for (mapFind; mapFind != m_mapTexMtls.end();)
	{
		if (mapFind->second)
		{
			mapFind = m_mapTexMtls.erase(mapFind);
		}
		else mapFind++;
	}
	m_mapTexMtls.clear();
}

void cTexMtlManager::DestroyAll()
{
	mapTexMtlIter mapFind = m_mapTexMtls.begin();
	
	for (mapFind; mapFind != m_mapTexMtls.end();)
	{
		if (mapFind->second)
		{
			D_SAFE_RELEASE(mapFind->second);
			D_SAFE_DELETE(mapFind->second);
			mapFind = m_mapTexMtls.erase(mapFind);
		}
		else mapFind++;
	}
}
