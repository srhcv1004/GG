#include "stdafx.h"
#include "cAseObject.h"
#include "cAseNode.h"

cAseObject::cAseObject()
	: m_pAseRoot(NULL)
	, m_pFrame(NULL)
{
	m_pFrame = new float(0.F);
}

cAseObject::~cAseObject()
{
}

void cAseObject::Setup(const CHAR* pAseFolderName, const CHAR* pAseFileName)
{
	this->ClearManager();

	m_pAseRoot = D_ASELOADMANAGER->LoadAse(m_mapAseCharacter, pAseFolderName, pAseFileName);

	if (m_pAseRoot)
		m_pAseRoot->Setup();
}

void cAseObject::Release()
{
	mapAseObjectIter mapFind = m_mapAseCharacter.begin();

	for (mapFind; mapFind != m_mapAseCharacter.end();)
	{
		if (mapFind->second)
		{
			D_SAFE_RELEASE(mapFind->second);
			D_SAFE_DELETE(mapFind->second);
			mapFind = m_mapAseCharacter.erase(mapFind);
		}
		else mapFind++;
	}
}

void cAseObject::Update()
{
	(*m_pFrame) += D_TIMEMANAGER->GetElapsedTime() * 1000.F;

	if (m_pAseRoot)
		m_pAseRoot->Update(m_pFrame);
}

void cAseObject::Render()
{
	D_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	if (m_pAseRoot)
		m_pAseRoot->Render();
}

void cAseObject::ClearManager()
{
	D_ASELOADMANAGER->Release();
	D_ASELOADMANAGER->ReleaseSingleton();

	D_TEXMTLMANAGER->Release();
	D_TEXMTLMANAGER->ReleaseSingleton();
}
