#pragma once
#include "cSingletonBase.h"

class cGameNode;

class cSceneManager : public cSingletonBase<cSceneManager>
{
private:
	typedef std::map<std::string, cGameNode*>				mapScene;
	typedef std::map<std::string, cGameNode*>::iterator		mapSceneIter;

private:
	mapScene												m_mapScenes;

private:
	static cGameNode*										m_pCurScene;

public:
	cSceneManager();
	virtual ~cSceneManager();

	void Setup();
	void Release();
	void Update();
	void Render();

	cGameNode* AddScene(std::string strSceneKey, cGameNode* pScene);
	void ChangeScene(std::string strSceneKey);
};

