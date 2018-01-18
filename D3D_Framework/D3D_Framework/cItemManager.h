#pragma once

class cItem;

class cItemManager
{
private:
	std::map<std::string, cItem*>							mapItem;
	std::map<std::string, cItem*>::iterator					mapItemIter;

public:
	cItemManager();
	~cItemManager();

	void Setup();
	void Release();

	void AddItem(cItem* pItem);
};

