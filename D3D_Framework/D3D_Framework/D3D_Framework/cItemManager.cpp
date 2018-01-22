#include "stdafx.h"
#include "cItemManager.h"

cItemManager::cItemManager()
{
}

cItemManager::~cItemManager()
{
}

void cItemManager::Setup()
{
	this->LoadXItem();
}

void cItemManager::Release()
{
	mapXItemIter mapFind;

	for (int i = 0; i < E_PARTS_END; i++)
	{
		for (mapFind = m_mapXItem[i].begin(); mapFind != m_mapXItem[i].end();)
		{
			if (mapFind->second)
			{
				D_SAFE_RELEASE(mapFind->second);
				D_SAFE_DELETE(mapFind->second);
				mapFind = m_mapXItem[i].erase(mapFind);
			}
			else mapFind++;
		}
	}
}

void cItemManager::LoadXItem()
{
	this->LoadXHead();
	this->LoadXBody();
	this->LoadXHand();
	this->LoadXLeg();
	this->LoadXHair();
}

void cItemManager::LoadXHead()
{
	FILE* pFile = NULL;
	errno_t errNo = fopen_s(&pFile, "XFile/XItem/Head/XHead.txt", "rt");

	DWORD dwItemKey = 0;
	DWORD dwItemCount = 0;
	CHAR szFolderName[256] = "";
	CHAR szFileName[256] = "";

	fscanf_s(pFile, "ItemCount = %d\n", &dwItemCount);
	for (DWORD i = 0; i < dwItemCount; i++)
	{
		fscanf_s(pFile, "[%d]\t %s\t %s\n", &dwItemKey, szFileName, 256, szFolderName, 256);

		cXItem* pItem = new cXItem();
		pItem->Setup(szFolderName, szFileName);

		m_mapXItem[E_PARTS_HEAD].insert(std::make_pair(dwItemKey, pItem));
	}

	fclose(pFile);
}

void cItemManager::LoadXBody()
{

	FILE* pFile = NULL;
	errno_t errNo = fopen_s(&pFile, "XFile/XItem/Body/XBody.txt", "rt");

	DWORD dwItemKey = 0;
	DWORD dwItemCount = 0;
	CHAR szFolderName[256] = "";
	CHAR szFileName[256] = "";

	fscanf_s(pFile, "ItemCount = %d\n", &dwItemCount);
	for (DWORD i = 0; i < dwItemCount; i++)
	{
		fscanf_s(pFile, "[%d]\t %s\t %s\n", &dwItemKey, szFileName, 256, szFolderName, 256);

		cXItem* pItem = new cXItem();
		pItem->Setup(szFolderName, szFileName);

		m_mapXItem[E_PARTS_BODY].insert(std::make_pair(dwItemKey, pItem));
	}

	fclose(pFile);
}

void cItemManager::LoadXHand()
{
	FILE* pFile = NULL;
	errno_t errNo = fopen_s(&pFile, "XFile/XItem/Hand/XHand.txt", "rt");

	DWORD dwItemKey = 0;
	DWORD dwItemCount = 0;
	CHAR szFolderName[256] = "";
	CHAR szFileName[256] = "";

	fscanf_s(pFile, "ItemCount = %d\n", &dwItemCount);
	for (DWORD i = 0; i < dwItemCount; i++)
	{
		fscanf_s(pFile, "[%d]\t %s\t %s\n", &dwItemKey, szFileName, 256, szFolderName, 256);

		cXItem* pItem = new cXItem();
		pItem->Setup(szFolderName, szFileName);

		m_mapXItem[E_PARTS_HAND].insert(std::make_pair(dwItemKey, pItem));
	}

	fclose(pFile);
}

void cItemManager::LoadXLeg()
{
	FILE* pFile = NULL;
	errno_t errNo = fopen_s(&pFile, "XFile/XItem/Leg/XLeg.txt", "rt");

	DWORD dwItemKey = 0;
	DWORD dwItemCount = 0;
	CHAR szFolderName[256] = "";
	CHAR szFileName[256] = "";

	fscanf_s(pFile, "ItemCount = %d\n", &dwItemCount);
	for (DWORD i = 0; i < dwItemCount; i++)
	{
		fscanf_s(pFile, "[%d]\t %s\t %s\n", &dwItemKey, szFileName, 256, szFolderName, 256);

		cXItem* pItem = new cXItem();
		pItem->Setup(szFolderName, szFileName);

		m_mapXItem[E_PARTS_LEG].insert(std::make_pair(dwItemKey, pItem));
	}

	fclose(pFile);
}

void cItemManager::LoadXHair()
{
	FILE* pFile = NULL;
	errno_t errNo = fopen_s(&pFile, "XFile/XItem/Hair/XHair.txt", "rt");

	DWORD dwItemKey = 0;
	DWORD dwItemCount = 0;
	CHAR szFolderName[256] = "";
	CHAR szFileName[256] = "";

	fscanf_s(pFile, "ItemCount = %d\n", &dwItemCount);
	for (DWORD i = 0; i < dwItemCount; i++)
	{
		fscanf_s(pFile, "[%d]\t %s\t %s\n", &dwItemKey, szFileName, 256, szFolderName, 256);

		cXItem* pItem = new cXItem();
		pItem->Setup(szFolderName, szFileName);

		m_mapXItem[E_PARTS_HAIR].insert(std::make_pair(dwItemKey, pItem));
	}

	fclose(pFile);
}

cItem* cItemManager::FindItem(DWORD dwItemKey, cItemManager::E_PARTS eParts)
{
	mapXItemIter mapFind = m_mapXItem[eParts].find(dwItemKey);

	if (mapFind == m_mapXItem[eParts].end()) return NULL;

	return mapFind->second;
}
