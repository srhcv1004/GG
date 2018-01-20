#pragma once

class cAseNode;

class cAseObject
{
private:
	typedef std::map<std::string, cAseNode*>				mapAseObject;
	typedef std::map<std::string, cAseNode*>::iterator		mapAseObjectIter;

private:
	cAseNode* m_pAseRoot;

private:
	mapAseObject											m_mapAseCharacter;

private:
	float*													m_pFrame;

private:
	void ClearManager();

public:
	cAseObject();
	virtual ~cAseObject();

	virtual void Setup(const CHAR* pAseFolderName, const CHAR* pAseFileName);
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

