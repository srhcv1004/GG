#pragma once

class cSkinnedMesh;

class cItem
{
protected:
	cSkinnedMesh*											m_pXItem;

protected:
	float													m_fAbility;

public:
	cItem();
	~cItem();

	void Setup();
	void Update();
	void Render();
};

