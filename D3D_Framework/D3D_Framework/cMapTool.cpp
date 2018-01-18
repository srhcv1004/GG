#include "stdafx.h"
#include "cMapTool.h"
#include "cGrid.h"
#include "cCamera.h"

cMapTool::cMapTool()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
{
}

cMapTool::~cMapTool()
{
}

void cMapTool::Setup()
{
	m_pCamera = new cCamera();
	m_pCamera->Setup();

	m_pGrid = new cLineGrid();
	m_pGrid->Setup();
}

void cMapTool::Release()
{
	if (m_pCamera)
		m_pCamera->Release();

	if (m_pGrid)
		m_pGrid->Release();
}

void cMapTool::Update()
{
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pGrid)
		m_pGrid->Update();
}

void cMapTool::Render()
{
	if (m_pGrid)
		m_pGrid->Render();
}

void cMapTool::Save()
{
}

void cMapTool::Load()
{
}
