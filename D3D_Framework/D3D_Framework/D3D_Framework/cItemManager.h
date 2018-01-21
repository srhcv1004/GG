#pragma once
#include "cSingletonBase.h"
#include "cItem.h"

class cItemManager : public cSingletonBase<cItemManager>
{
public:
	enum E_PARTS
	{
		E_PARTS_HEAD,
		E_PARTS_BODY,
		E_PARTS_HAND,
		E_PARTS_LEG,
		E_PARTS_END = 4
	};

private:
	typedef std::map<DWORD, cItem*>							mapXItem;
	typedef std::map<DWORD, cItem*>::iterator				mapXItemIter;

private:
	mapXItem												m_mapXItem[E_PARTS_END];

private:
	void LoadXItem();
	void LoadXBody();
	void LoadXHand();
	void LoadXLeg();

public:
	cItemManager();
	~cItemManager();

	void Setup();
	void Release();

	cItem* FindItem(DWORD dwItemKey, cItemManager::E_PARTS eParts);
};

