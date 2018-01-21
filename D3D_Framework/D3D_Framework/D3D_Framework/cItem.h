#pragma once

class cSkinnedMesh;

class cItem
{
public:
	cItem() {}
	virtual ~cItem() {}

	void Setup() {}
	virtual void Release() {}
	//virtual void OnDoubleClick() = 0;
};

// ======================================================================
class cXItem : public cItem
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

protected:
	cSkinnedMesh*											m_pXItem;

protected:
	E_PARTS													m_ePartsKind;

public:
	cXItem();
	virtual ~cXItem();

	void Setup(const CHAR* pFolderName, const CHAR* pFileName);
	virtual void Release();

	cSkinnedMesh* GetXItem() { return m_pXItem; }
};
// ======================================================================



// ======================================================================
class cBasicItem : public cItem
{
public:
	cBasicItem();
	virtual ~cBasicItem();

	void Setup();
	virtual void Release();
};
// ======================================================================