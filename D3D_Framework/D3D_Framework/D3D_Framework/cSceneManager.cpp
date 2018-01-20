#include "stdafx.h"
#include "cSceneManager.h"
#include "cGameNode.h"

cGameNode* cSceneManager::m_pCurScene = NULL;

cSceneManager::cSceneManager()
{
}

cSceneManager::~cSceneManager()
{
}

void cSceneManager::Setup()
{
	m_pCurScene = NULL;
}

void cSceneManager::Release()
{
	mapSceneIter mapFind = m_mapScenes.begin();

	for (mapFind; mapFind != m_mapScenes.end();)
	{
		if (mapFind->second)
		{
			D_SAFE_RELEASE(mapFind->second);
			D_SAFE_DELETE(mapFind->second);
			mapFind = m_mapScenes.erase(mapFind);
		}
		else mapFind++;
	}
}

void cSceneManager::Update()
{	
	if (m_pCurScene)
		m_pCurScene->Update();
}

void cSceneManager::Render()
{
	if (m_pCurScene)
		m_pCurScene->Render();
}

cGameNode * cSceneManager::AddScene(std::string strSceneKey, cGameNode * pScene)
{
	if (!pScene) return NULL;

	m_mapScenes.insert(std::make_pair(strSceneKey, pScene));

	return pScene;
}

void cSceneManager::ChangeScene(std::string strSceneKey)
{
	mapSceneIter mapFind = m_mapScenes.find(strSceneKey);

	if (mapFind == m_mapScenes.end()) return;
	if (mapFind->second == m_pCurScene) return;

	mapFind->second;
	mapFind->second->Setup();
	if (m_pCurScene)
	{
		m_pCurScene->Release();
	}
	m_pCurScene = mapFind->second;
}