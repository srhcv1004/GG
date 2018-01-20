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
	void AddItem(cItem* pItem);
};

